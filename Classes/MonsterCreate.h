#ifndef MONSTER__CREATE
#define MONSTER__CREATE

#include "PublicDefine.h"

class MonsterCreate
{
public:
	static MonsterBase* createMonster(const MonsterType& rMonsterType);

};

#endif