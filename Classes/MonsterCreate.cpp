#include "Monster.h"
#include"MonsterCreate.h"

MonsterBase* MonsterCreate::createMonster(const MonsterType& rMonsterType)
{
	MonsterBase* Monster = nullptr;

	int Monsterid;
	switch (rMonsterType)
	{
	case en_Land_Star:
		Monsterid = 1;
		break;
	case en_Land_Pink:
		Monsterid = 2;
		break;
	case en_Land_Nima:
		Monsterid = 3;
		break;
	default:
		break;
	}
	Monster = MonsterBase::create(Monsterid);
	return Monster;
}