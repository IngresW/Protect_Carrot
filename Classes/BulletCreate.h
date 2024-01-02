#ifndef Bullet__Create
#define Bullet__Create

#include "PublicDefine.h"

class EntityAffected;
class Entity;

class BulletCreate:public Ref
{
public:
    CREATE_INSTANCE_FUNC(BulletCreate);
    DESTROY_INSTANCE_FUNC();

    struct BulletInfo
    {
        int bulletId;
        TowerBase* tower;
        EntityAffected* rEntityAffected;
    };

    BulletBase* createBullet(const BulletInfo& bulletInfo);

    void setFuncAddBulletLayer(const std::function<void(Entity*)>& rFuncAddBulletLayer);

    void checkBulletIsDead();

    void clearManager();

    virtual void addBullet(BulletBase* pBullet);

protected:
    virtual bool init();


private:
    BulletCreate();
    virtual ~BulletCreate();
    BulletCreate(const BulletCreate&) = delete;
    BulletCreate& operator=(const BulletCreate&) = delete;

    Vector<BulletBase*> *_bulletVec = nullptr;
    std::function<void(Entity*)> _funcAddBulletLayer;
};

#endif // !Bullet__Create
