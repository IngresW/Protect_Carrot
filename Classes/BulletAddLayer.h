#ifndef BULLET__ADD__LAYER
#define BUULET__ADD__LAYER
#include "EntityAddLayer.h"
class BulletAddLayer :public EntityAddLayer
{
public:

    CREATE_FUNC(BulletAddLayer);

protected:

    virtual bool init();

    virtual void update(float dt);
};

#endif