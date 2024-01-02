#ifndef Tower__Base
#define Tower__Base
#include "EntityBase.h"


class EntityAffected;

class TowerBase :public Entity
{
public:
    virtual bool init(const int& rId, const BasicInformation basicInformation, const TowerInformation towerInformation);
    virtual bool isInAtkRange(const Vec2& rPOS);
    virtual void checkAtkTarget(float dt);
    virtual void fire(float dt);
    virtual int getTowerGradeCost();

    BulletInformation _iBulletId;
    double _iAtkRange;
    int _iCreateCost;
    int _iUpgradeCost;
    int _iValue;
    int _iGrade;
    int _iTowerId;
    
    bool _bAtkTarget;

protected:
    virtual void upGrade();


    Sprite* _pTowerSprite = nullptr;
    EntityAffected* _pAtkTarget = nullptr;
    std::vector<MonsterBase*> MonsterVec;
};

#endif
