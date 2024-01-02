#include "BulletCreate.h"
#include "Bullet.h"
#include "EntityAffected.h"
#include "TowerBase.h"


BulletCreate* BulletCreate::_gInstance;

BulletCreate::BulletCreate() = default;

BulletCreate::~BulletCreate() = default;

bool BulletCreate::init()
{
    return true;
}

BulletBase* BulletCreate::createBullet(const BulletInfo& bulletInfo)
{
    auto cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Themes/Towers/TBottle-hd.plist", "Themes/Towers/TBottle-hd.png");
    cache->addSpriteFramesWithFile("Themes/Towers/TFan-hd.plist", "Themes/Towers/TFan-hd.png");
    cache->addSpriteFramesWithFile("Themes/Towers/TShit-hd.plist", "Themes/Towers/TShit-hd.png");

    auto pBullet = BulletBase::create(bulletInfo.bulletId, bulletInfo.rEntityAffected);
    pBullet->setRotation(90 - 180 * (bulletInfo.rEntityAffected->getPosition() - bulletInfo.tower->getPosition()).getAngle() / M_PI);
    if (pBullet->getIBulletType() == en_GunBullet) {
        pBullet->setPosition(bulletInfo.tower->getPosition() + Vec2(36 * sin(pBullet->getRotation() * M_PI / 180), 36 * cos(pBullet->getRotation() * M_PI / 180)));
    }
    else {
        pBullet->setPosition(bulletInfo.tower->getPosition());
    }

    pBullet->doMove();

    _bulletVec->pushBack(pBullet);
    _funcAddBulletLayer(pBullet);

    return pBullet;
}

void BulletCreate::addBullet(BulletBase* pBullet)
{
    if (_bulletVec) _bulletVec->pushBack(pBullet);
    _funcAddBulletLayer(pBullet);
}

void BulletCreate::setFuncAddBulletLayer(const std::function<void(Entity*)>& rFuncAddBulletLayer)
{
    _funcAddBulletLayer = rFuncAddBulletLayer;
}

void BulletCreate::checkBulletIsDead()
{
    for (auto iterBullet = _bulletVec->begin(); iterBullet != _bulletVec->end();)
    {
        if ((*iterBullet)->getIsDead())
        {
            (*iterBullet)->removeFromParent();
            iterBullet = _bulletVec->erase(iterBullet);
        }
        else
        {
            ++iterBullet;
        }
    }
}

void BulletCreate::clearManager()
{
    _bulletVec->clear();
}