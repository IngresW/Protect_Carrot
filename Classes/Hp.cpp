#include "Hp.h"

Hp::~Hp() = default;

Hp* Hp::create(EntityAffected* pVictimEntity)
{
    auto pHp = new Hp();
    if (pHp && pHp->init(pVictimEntity)) pHp->autorelease();
    else CC_SAFE_DELETE(pHp);
    return pHp;
}

bool Hp::init(EntityAffected* pEntityAffected)
{
    bool bRet = false;

    do
    {
        CC_SAFE_RETAIN(pEntityAffected);
        _pEntityAffected = pEntityAffected;
        _iHpMax = _pEntityAffected->getIHp();

        auto pHpBg = Sprite::createWithSpriteFrameName("MonsterHP01.png");
        pHpBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        addChild(pHpBg);

        _pHp = ProgressTimer::create(Sprite::createWithSpriteFrameName("MonsterHP02.png"));
        _pHp->setType(ProgressTimer::Type::BAR);
        _pHp->setMidpoint(Vec2::ANCHOR_MIDDLE_RIGHT);
        _pHp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        _pHp->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);
        _pHp->setPercentage(0);
        _pHp->setPositionX(2);

        addChild(_pHp);
        bRet = true;
    } while (0);

    return bRet;
}

void Hp::setHp(const int& rIHp)
{
    _pHp->setPercentage(100 - _pEntityAffected->getIHp() * 1.0f / _iHpMax * 100);
}

const Size& Hp::getContentSize()const
{
    return _pHp->getContentSize();
}
