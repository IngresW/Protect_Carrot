#ifndef ENTITY__AFFECTED
#define ENTITY__AFFECTED

#include "EntityBase.h"
#include "Hp.h"

class EntityAffected :public Entity
{
public:
	virtual ~EntityAffected();
	virtual void beHurt(const int towerATK);
	virtual void openHp(const bool& rBIsVisible);
	int _iHp;
	int _iSpeed;

protected:
	virtual bool init(const int& rId, const BasicInformation& basicInformation, const AffectedInformation& affectedInformation);
	virtual void closeHp(float dt);
	virtual void deadAction(const std::string& deadImageFile = "");
	virtual void createHpSprite();
	const int _iHpCloseTime = 3;

private:
	bool _bHpSlotExsit = false;
	Hp* _pHp = nullptr;
	bool _bIsAtkTarget = false;
	Vec2 _Pos;
	Size _Size;
};



#endif
