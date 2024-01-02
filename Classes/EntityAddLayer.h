#ifndef ENTITY__ADD__LAYER
#define ENTITY__ADD__LAYER
#include "PublicDefine.h"

class Entity;

class EntityAddLayer :public Layer
{
public:
	virtual void addEntity(Entity* pEntity);
};



#endif // !ENTITY__ADD__LAYER
