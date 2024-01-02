#include "Hp.h"

Hp::Hp(EntityAffected* pEntityAffected)
    : _EntityAffected(pEntityAffected),
    _iHpMax(_EntityAffected->_iHp)
{
}

Hp::~Hp() = default;

Hp* Hp::create(EntityAffected* pEntityAffected)
{
    auto pHp = new Hp(pEntityAffected);
    if (pHp && pHp->init()) {
        pHp->autorelease();
    }
    else {
        CC_SAFE_DELETE(pHp);
    }
    return pHp;
}

bool Hp::init()
{
    if (!Node::init()) {
        return false;
    }

    // 创建底部血量背景图片
    auto pHpBg = Sprite::createWithSpriteFrameName("fight_blood_bg.png");
    pHpBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(pHpBg);

    // 创建血量显示容器
    auto clippingNode = ClippingNode::create();
    clippingNode->setAlphaThreshold(0.5f); // 设置透明度阈值
    clippingNode->setInverted(false); // 设置剪裁区域可见
    addChild(clippingNode);

    // 创建血量显示图片
    auto hpSprite = Sprite::createWithSpriteFrameName("fight_blood_top.png");
    hpSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    clippingNode->addChild(hpSprite);

    // 设置血量显示图片为剪裁节点的子节点
    clippingNode->setStencil(hpSprite);

    _Hp = ProgressTimer::create(hpSprite);
    _Hp->setType(ProgressTimer::Type::BAR);
    _Hp->setMidpoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _Hp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _Hp->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT);
    _Hp->setPercentage(100);
    _Hp->setPositionX(2);
    addChild(_Hp);
}

void Hp::setHp(const int& rIHp)
{
    int newHp = std::max(0, std::min(rIHp, _iHpMax));
    _Hp->setPercentage(100 - newHp * 1.0f / _iHpMax * 100);
}

const Size& Hp::getContentSize() const
{
    return _Hp->getContentSize();
}
