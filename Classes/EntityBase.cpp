#include "EntityBase.h"

unsigned long Entity::ID = 0;
Entity::~Entity() = default;

bool Entity::init(const int& rID, const std::string& rSCsvFileName)
{
    initProperty(rID, rSCsvFileName);
    ++ID;
    _myID = ID;
    return true;
}

void Entity::initProperty(const int& rID, const std::string& rSCsvFileName)
{
    auto pCsvUtil = CsvUtil::getInstance();

    _iID = rID;
    auto pData = pCsvUtil->getRowData(rID, rSCsvFileName);
    _sName = pData.at(en_Name);
    _sModelName = pData.at(en_ModelName);
    _iValue = atoi(pData.at(en_Value).c_str());
    _IAnimationFrameCount = pCsvUtil->getInt(rID, en_AnimationCount, rSCsvFileName);
    _iLevel = pCsvUtil->getInt(_iID, en_Level, rSCsvFileName);
    _bIsDead = false;
    std::string sSpriteName = "";
    if (_IAnimationFrameCount)
        sSpriteName = _sModelName + "1" + PHOTOPOSTFIX;
    else
        sSpriteName = _sModelName + PHOTOPOSTFIX;

    bindSprite(Sprite::createWithSpriteFrameName(sSpriteName));
}

void Entity::bindSprite(cocos2d::Sprite* pSprite)
{
    if (PSprite == pSprite)
    {
        return; // 如果传入的精灵与当前绑定的精灵相同，无需进行任何操作
    }
    if (PSprite)
    {
        PSprite->stopAllActions();
        removeChild(PSprite, true);  // 使用cleanup参数移除子节点，同时释放精灵的内存
        CC_SAFE_RELEASE_NULL(PSprite);
    }

    PSprite = pSprite;

    if (PSprite)
    {
        CC_SAFE_RETAIN(PSprite);
        addChild(PSprite);
    }
}

void Entity::doDead()
{
    setIsDead(true);
    PSprite->stopAllActions();
}

void Entity::deadAction(const std::string& rSDeadImageFile)
{

    auto sDeadImageFile = rSDeadImageFile;
    auto pAnimation = Animation::create();
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();

    if (sDeadImageFile.empty())
    {
        if (1 == _iLevel) sDeadImageFile = "air0";
        else if (2 == _iLevel) sDeadImageFile = "air1";
        else if (3 == _iLevel) sDeadImageFile = "air2";
        for (int index = 1; index <= _IAnimationFrameCount; ++index)
            pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(sDeadImageFile + StringUtils::format("%d", index) + PHOTOPOSTFIX));

    }
    else
    {
        for (int i = 1; i <= 2; i++)
            pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(sDeadImageFile + StringUtils::format("%02d", i) + PHOTOPOSTFIX));
    }

    pAnimation->setLoops(1);
    pAnimation->setDelayPerUnit(0.1f);
    PSprite->runAction(Sequence::create(Animate::create(pAnimation), CallFunc::create([this]() {this->removeFromParent(); }), NULL));
}

Rect Entity::getBoundingBox()const
{
    auto &tPos = getPosition();
    auto &tSize = PSprite->getContentSize();
    return Rect(tPos.x - tSize.width / 2, tPos.y - tSize.height / 2, tSize.width, tSize.height);
}

unsigned int Entity::getmID()const
{
    return _myID;
}

const Size& Entity::getContentSize()const
{
    return PSprite->getContentSize();
}

Sprite* Entity::getSprite()
{
    return PSprite;
}