#include "EntityAffected.h"
#include "Hp.h"
#include"TowerBase.h"
#include "SoundUtil.h"
#include "TowerManage.h"

EntityAffected::~EntityAffected() = default;

bool EntityAffected::init(const int& rIId, const std::string& rSCsvFileName)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Entity::init(rIId, rSCsvFileName));
        _iHp = CsvUtil::getInstance()->getInt(_iID, en_Hp, rSCsvFileName);
        _iState = en_Normal;
        _fSlowDuration = 0;
        _fStopDuration = 0;
        _fPoisonDuration = 0;
        _Pos = getPosition();
        _Size = getContentSize();
        this->schedule(schedule_selector(EntityAffected::checkAtkTarget));
        bRet = true;
    } while (0);

    return bRet;
}

void EntityAffected::beHurt(const AtkProperty tBeHurtValue)
{
    if (this->getIsDead())
        return;
    _iState |= tBeHurtValue._enAtkState;
    _iBulletStateType = tBeHurtValue._iButtltType;
    switch (tBeHurtValue._enAtkState)
    {
    case en_Slow: _fSlowDuration = tBeHurtValue._iDuration; break;
    case en_Stop: _fStopDuration = tBeHurtValue._iDuration; break;
    case en_Poison: _fPoisonDuration = tBeHurtValue._iDuration; break;
    default:
        break;
    }
    auto tIHp = getIHp() - tBeHurtValue._iAtk;
    if (tIHp > 0)
    {
        unschedule(schedule_selector(EntityAffected::closeHpSlot));
        if (!_bHpSlotExsit)
        {
            hpSlotVisible(!_bHpSlotExsit);
            _bHpSlotExsit = true;
        }
        _pHp->setVisible(true);
        schedule(schedule_selector(EntityAffected::closeHpSlot), _iHpCloseTime);
        setIHp(tIHp);
        _pHp->setHp(getIHp());
    }
    else if (tIHp <= 0)
    {
        doDead();
    }
}

void EntityAffected::closeHpSlot(float dt)
{
    _pHp->setVisible(false);
}

void EntityAffected::hpSlotVisible(const bool& rBIsVisible)
{
    if (rBIsVisible) createHpSlotSprite();
    else _pHp->setVisible(rBIsVisible);
}

void EntityAffected::deadAction(const std::string& rSDeadImageFile)
{
    auto tValue = std::make_tuple(getPosition(), _iValue);
    NOTIFY->postNotification("monsterDeadMoney", reinterpret_cast<Ref*>(&tValue));
    if (_pHp) _pHp->removeFromParent();
    if (_pLockAtkTarget) _pLockAtkTarget->removeFromParent();
    Entity::deadAction();
}

void EntityAffected::createHpSlotSprite()
{
    _pHp = Hp::create(this);
    _pHp->retain();
    auto tPos = getPosition();
    auto tSpriteSize = getContentSize();
    auto tSlotSize = _pHp->getContentSize();
    _pHp->setPosition(Vec2(-tSlotSize.width / 2 - 3, tSpriteSize.height / 2 - 12));
    addChild(_pHp);
}

void EntityAffected::checkAtkTarget(float dt) {
    auto tTowerVec = TowerManager::getInstance()->getTowerVec();
    if (_bIsAtkTarget) {
        for (auto& towerItem : tTowerVec)
        {
            if (towerItem->isInAtkRange(this->getPosition())) {
                towerItem->setAtkTarget(this);
                towerItem->setIsHaveAtkTarget(true);
            }
        }
    }
}

