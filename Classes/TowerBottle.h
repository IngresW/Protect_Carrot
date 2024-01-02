#ifndef TOWER__BOTTLE
#define TOWER__BOTTLE
#include "TowerBase.h"

class TowerFireBottle :public TowerBase {
protected:

	virtual bool init();

	void  chooseAtkTarget();

	void missAtkTarget();

	void fire(float dt);

	int const rId = 16;

	Sprite* _doActionSprite;

public:

	CREATE_FUNC(TowerFireBottle);

};
#endif