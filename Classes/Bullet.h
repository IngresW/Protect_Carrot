#ifndef Bullet__
#define Bullet__

#include "EntityBase.h"
#include "DynamicInterface.h"

class BulletBase :public Entity,public DynamicInterface
{
public:
    std::set<int>& getIdMap();

    virtual void doMove();

    static BulletBase* create(const int& rIId, EntityAffected* rEntityAffected);

    virtual AtkProperty getAtkPro();

    virtual void deadAction(const std::string& rSDeadImageFile = "");
    virtual void setAction(const float& rDt);

protected:

    virtual bool init(const int& rId, EntityAffected* rEntityAffected);
    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkState, IAtkState);

    CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletType, IBulletType);

    CC_SYNTHESIZE_PASS_BY_REF(int, _iDeadActCount, IDeadActCount);
    EntityAffected* _pAtkTarget = nullptr;
    std::set<int>* _IdMap = nullptr;
};

#endif 
