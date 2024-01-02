#include "MonsterAddLayer.h"

bool MonsterAddLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto pStart = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("start01.png"));
    //这里要根据地图添加初始
    addChild(pStart);

    registerMonsterDeadEvent();

    return true;
}


void MonsterAddLayer::registerMonsterDeadEvent()
{
    cocos2d::NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(MonsterAddLayer::monsterDead), "monsterDeadMoney", nullptr);
}

void MonsterAddLayer::monsterDead(Ref* pData)
{
    auto tValue = *reinterpret_cast<std::tuple<Vec2, int>*>(pData);
    auto tMoney = std::get<1>(tValue);

    auto pMoney = Sprite::createWithSpriteFrameName(StringUtils::format("money%d.png", tMoney));
    pMoney->setPosition(std::get<0>(tValue));
    addChild(pMoney);

    pMoney->runAction(Sequence::create(
        MoveBy::create(0.6f, Vec2(0, 100)),
        DelayTime::create(0.4f),
        FadeOut::create(0.4f),
        CallFunc::create([=]() { pMoney->removeFromParent(); }),
        nullptr
    ));
}

void MonsterAddLayer::onExit()
{
    Layer::onExit();
    cocos2d::NotificationCenter::getInstance()->removeAllObservers(this);
}