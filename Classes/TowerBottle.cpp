#include "TowerBottle.h"

TowerBottle* TowerBottle::createTower(const int& rId, const BasicInformation& basicInformation, const TowerInformation& towerInformation)
{
    TowerBottle* pTower = new TowerBottle();
    if (pTower && pTower->init(rId, basicInformation, towerInformation))
    {
        pTower->autorelease();
        return pTower;
    }
    else
    {
        delete pTower;
        return nullptr;
    }
}

bool TowerBottle::init(const int& rId, const BasicInformation& basicInformation, const TowerInformation& towerInformation)
{
    if (!TowerBase::init(rId, basicInformation, towerInformation))
    {
        return false;
    }

    // 设置炮塔的外观
    _pTowerSprite->setTexture("bottle.png");

    return true;
}

void TowerBottle::upGrade()
{
    TowerBase::upGrade();

    // 根据需要进行炮塔升级的额外操作
    // 可以根据需要进行具体实现
}
