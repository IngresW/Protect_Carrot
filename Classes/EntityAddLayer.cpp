#include "EntityAddLayer.h"
#include "EntityBase.h"

void EntityAddLayer::addEntity(Entity* pEntity)
{
	addChild(pEntity);
}