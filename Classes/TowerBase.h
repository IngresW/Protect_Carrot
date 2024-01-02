#ifndef Tower__Base
#define Tower__Base
#include "EntityBase.h"


class EntityAffected;

class TowerBase :public Entity
{
public:
    virtual int getTowerUpGradeCost();
    virtual void showGradeMark();
    virtual void hideGradeMark();
    virtual bool isInAtkRange(const Vec2& rPOS);
    virtual void setAtkTarget(EntityAffected* pEntityAffected);
    virtual int getTowerGradeCost();

protected:
    virtual bool init(const int& rId);
    virtual void initTower();
    virtual void upGrade();
    virtual void loadTowerData();
    virtual void fireAction();
    

    CC_SYNTHESIZE_PASS_BY_REF(int, _iBulletId, IBulletId);
    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtkRange, IAtkRange);
    CC_SYNTHESIZE_PASS_BY_REF(double, _iAtkSpace, IAtkSpace);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sUpgradeCost, SUpgradeCose);
    CC_SYNTHESIZE_PASS_BY_REF(int, _iUpgradeCount, IUpgradeCount);
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsRotation, BIsRotation);
    CC_SYNTHESIZE_PASS_BY_REF(int, _iCreateCost, ICreateCost);
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsHaveAtkTarget, IsHaveAtkTarget);

    Sprite* _pGradeMark = nullptr;
    Sprite* _pTowerPanel = nullptr;
    EntityAffected* _pAtkTarget = nullptr;
};

#endif