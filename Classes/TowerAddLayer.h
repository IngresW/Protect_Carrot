#ifndef TOWER__ADD__LAYER
#define TOWER__ADD__LAYER
#include"EntityAddLayer.h"

class TowerAddLayer :public EntityAddLayer
{
public:

    CREATE_FUNC(TowerAddLayer);

protected:
    virtual void checkTowerGrade(float dt);
    virtual bool init();
};
#endif // !TOWER__ADD__LAYER
