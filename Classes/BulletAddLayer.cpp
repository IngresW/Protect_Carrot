#include "BulletAddLayer.h"
#include "BulletCreate.h"

bool BulletAddLayer::init() 
{
    if (!EntityAddLayer::init()) {
        return false;
    }

    scheduleUpdate();

    return true;
}

void BulletAddLayer::update(float dt)
{
    BulletCreate::getInstance()->checkBulletIsDead();
}