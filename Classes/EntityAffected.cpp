#include "EntityAffected.h"
#include "Hp.h"

EntityAffected::~EntityAffected() = default;

bool EntityAffected::init(const int& rId, const BasicInformation& basicInformation,const AffectedInformation& affectedInformation)
{
	Entity::init(rId, basicInformation);
	_iHp = affectedInformation._iHp;
    _iSpeed = 0;
	_Pos = getPosition();
	_Size = getContentSize();
	return 0;
}

void EntityAffected::beHurt(const int towerATK)
{
	if (this->_bIsDead)
		return;
	auto IHp = _iHp - towerATK;
    if (IHp > 0)
    {
        unschedule(schedule_selector(EntityAffected::closeHp));
        if (!_bHpSlotExsit)
        {
            openHp(!_bHpSlotExsit);
            _bHpSlotExsit = true;
        }
        _pHp->setVisible(true);
        schedule(schedule_selector(EntityAffected::closeHp), _iHpCloseTime);
        _iHp = IHp;
        _pHp->setHp(_iHp);
    }
    else if (IHp <= 0)
    {
        doDead();
    }
}

void EntityAffected::closeHp(float dt)
{
    _pHp->setVisible(false);
}

void EntityAffected::openHp(const bool& IsVisible)
{
    if (IsVisible) createHpSprite();
    else _pHp->setVisible(IsVisible);
}

void EntityAffected::deadAction(const std::string& rSDeadImageFile)
{
    if (_pHp) _pHp->removeFromParent();
    Entity::deadAction();
}

void EntityAffected::createHpSprite()
{
    _pHp = Hp::create(this);
    _pHp->retain();
    auto tPos = getPosition();
    auto tSpriteSize = getContentSize();
    auto tSlotSize = _pHp->getContentSize();
    _pHp->setPosition(Vec2(-tSlotSize.width / 2 - 3, tSpriteSize.height / 2 - 12));
    addChild(_pHp);
}


