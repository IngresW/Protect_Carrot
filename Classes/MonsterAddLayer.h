#ifndef MONSTER__ADD__LAYER
#define MONSTER__ADD__LAYER
#include"EntityAddLayer.h"
class Monster;

class MonsterAddLayer:public EntityAddLayer
{
public:

    CREATE_FUNC(MonsterAddLayer);

protected:

    virtual bool init();

    virtual void registerMonsterDeadEvent();

    virtual void monsterDead(Ref* pData);

    virtual void onExit()override;

};

#endif // !MONSTER__ADD__LAYER
