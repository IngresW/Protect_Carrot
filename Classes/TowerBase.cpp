#include "TowerBase.h"
#include "CsvUtil.h"
#include "SoundUtil.h"
#include "EntityAffected.h"


bool TowerBase::init(const int& rId) 
{
    if (Entity::init(rId, TOWERCSVFILE)) 
    {
        initTower();
        return true;
    }

    return false;
}

void TowerBase::initTower() 
{
    if (_pTowerPanel) 
    {
        removeChild(_pTowerPanel, true);
        _pTowerPanel = nullptr;
    }

    loadTowerData();

    _pGradeMark = Sprite::create();
    _pGradeMark->setVisible(false);
    auto aniGradeMark = Animation::create();
    for (int i = 1; i <= 2; i++) 
    {
        aniGradeMark->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("showupgrade0%d.png", i)));
    }
    aniGradeMark->setDelayPerUnit(0.5);
    aniGradeMark->setLoops(-1);
    _pGradeMark->setZOrder(3);
    _pGradeMark->runAction(Animate::create(aniGradeMark));
    _pGradeMark->setPosition(0, 50);
    addChild(_pGradeMark);

    _pTowerPanel = Sprite::createWithSpriteFrameName(CsvUtil::getInstance()->getText(_iID, en_TowerBase, TOWERCSVFILE));
    _pTowerPanel->retain();
    _pTowerPanel->setZOrder(1);
    addChild(_pTowerPanel);
    getSprite()->setZOrder(2);
}

void TowerBase::loadTowerData() 
{
    auto pCSVUtil = CsvUtil::getInstance();
    _iBulletId = pCSVUtil->getInt(_iID, en_BulletId, TOWERNAME);
    _iAtkRange = pCSVUtil->getInt(_iID, en_Range, TOWERCSVFILE);
    _iAtkSpace = pCSVUtil->getDouble(_iID, en_Space, TOWERCSVFILE);
    _sUpgradeCost = pCSVUtil->getText(_iID, en_UpGradeCost, TOWERCSVFILE);
    _bIsRotation = pCSVUtil->getInt(_iID, en_IsRotation, TOWERCSVFILE);
    _iUpgradeCount = 0;
    _iCreateCost = pCSVUtil->getInt(_iID, en_CreateCost, TOWERCSVFILE);
    _bIsHaveAtkTarget = false;
}

void TowerBase::upGrade() 
{
    int upGradeMoney = std::stoi(_sUpgradeCost);
    upGradeMoney = -upGradeMoney;
    NotificationCenter::getInstance()->postNotification("moneyChange", (Ref*)(&upGradeMoney));

    auto upGradeCounts = this->getIUpgradeCount();
    _pGradeMark->removeFromParentAndCleanup(true);
    getSprite()->removeFromParentAndCleanup(true);
    Entity::initProperty(this->getIID() + 1, TOWERCSVFILE);

    initTower();
    this->_iUpgradeCount = upGradeCounts;
}

int TowerBase::getTowerUpGradeCost() 
{
    int upGradeMoney = std::stoi(_sUpgradeCost);
    return upGradeMoney;
}

void TowerBase::showGradeMark() 
{
    _pGradeMark->setVisible(true);
}

void TowerBase::hideGradeMark() 
{
    _pGradeMark->setVisible(false);
}

bool TowerBase::isInAtkRange(const Vec2& rPos) 
{
    auto distance = getPosition().distance(rPos);
    auto rangeSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("range_%d", _iAtkRange) + PHOTOPOSTFIX));
    return distance < rangeSprite->getContentSize().width / 2 + 30;
}

void TowerBase::setAtkTarget(EntityAffected* pEntityAffected) 
{
    CC_SAFE_RELEASE_NULL(_pAtkTarget);
    _pAtkTarget = pEntityAffected;
    CC_SAFE_RETAIN(_pAtkTarget);
}

void TowerBase::fireAction()
{
    std::string soundName = (_sName == "BStar") ? "PStar" : _sName;
    SoundUtil::getInstance()->playEffect(StringUtils::format("Music/Towers/%s.mp3", soundName.c_str()));

    auto pAnimation = Animation::create();
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();

    int animationFrameCount = this->getAnimationFrameCount();
    for (int i = 1; i <= animationFrameCount; i++)
    {
        std::string frameName = StringUtils::format("%s%d%s", _sModelName.c_str(), i, PHOTOPOSTFIX);
        pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(frameName));
    }

    std::string firstFrameName = StringUtils::format("%s1%s", _sModelName.c_str(), PHOTOPOSTFIX);
    pAnimation->addSpriteFrame(pSpriteFrameCache->getSpriteFrameByName(firstFrameName));

    pAnimation->setDelayPerUnit(0.05f);
    pAnimation->setLoops(1);

    auto pAnimate = Animate::create(pAnimation);

    getSprite()->stopAllActions();
    getSprite()->runAction(pAnimate);
}

int TowerBase::getTowerGradeCost()
{
    int upGradeMoney = std::stoi(_sUpgradeCost);
    return upGradeMoney;
}