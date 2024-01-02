#ifndef ENTITY__AFFECTED
#define ENTITY__AFFECTED

#include "EntityBase.h"
class Hp;

class EntityAffected: public Entity
{
public:
	virtual ~EntityAffected();
	virtual void beHurt(const AtkProperty tBeHurtValue);
	virtual void hpSlotVisible(const bool& rBIsVisible);

protected:
	virtual bool init(const int& rIId, const std::string& rSCsvFileName);
	virtual void checkAtkTarget(float dt); 
	virtual void closeHpSlot(float dt);
	virtual void deadAction(const std::string& rSDeadImageFile = "");
	virtual void createHpSlotSprite();


	CC_SYNTHESIZE_PASS_BY_REF(int, _iHp, IHp);
	CC_SYNTHESIZE_PASS_BY_REF(int, _iState, IState);
	CC_SYNTHESIZE_PASS_BY_REF(float, _fSlowDuration, FSlowDuration);
	CC_SYNTHESIZE_PASS_BY_REF(float, _fStopDuration, fStopDuration);
	CC_SYNTHESIZE_PASS_BY_REF(float, _fPoisonDuration, fPoisonDuration);
	CC_SYNTHESIZE_PASS_BY_REF(float, _iBulletStateType, IBulletStateType);
	const int _iHpCloseTime = 3;

private:

    bool _bHpSlotExsit = false;
    Hp* _pHp = nullptr;
    Sprite* _pLockAtkTarget = nullptr;
    Animate* _pLockFlagAnimate = nullptr;
    bool _bIsAtkTarget = false;
    Vec2 _Pos;
    Size _Size;
};

#endif