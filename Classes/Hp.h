#ifndef HP
#define HP
#include "PublicDefine.h"
#include "EntityAffected.h"
class EntityAffected;

class Hp:public Node
{
public:
	virtual ~Hp();
	static Hp* create(EntityAffected* pEntityAffected);
	virtual void setHp(const int& rIHp);
	virtual const Size& getContentSize()const;

	ProgressTimer* _pHp = nullptr;
	int _iHpMax = 0;

protected:

	virtual bool init(EntityAffected* pEntityAffected);


private:
	EntityAffected* _pEntityAffected = nullptr;

};



#endif