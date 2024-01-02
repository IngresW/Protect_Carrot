#include "TowerAddLayer.h"
#include "TowerManage.h"
#include "TowerBase.h"

bool TowerAddLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto cache = SpriteFrameCache::getInstance();

    for (const auto& iterSource : TOWERS)
    {
        cache->addSpriteFramesWithFile(iterSource + PLISTPOSTFIX, iterSource + PHOTOPOSTFIX);
    }

    schedule(schedule_selector(TowerAddLayer::checkTowerGrade));

    return true;
}

void TowerAddLayer::checkTowerGrade(float dt)
{
    const auto& towerVec = TowerManager::getInstance()->getTowerVec();
    const int money = TowerManager::getInstance()->getMoney();

    for (const auto& item : towerVec)
    {
        if (item->getIUpgradeCount() <= 1)
        {
            if (item->getTowerGradeCost() <= money)
            {
                item->showGradeMark();
            }
            else
            {
                item->hideGradeMark();
            }
        }
    }
}