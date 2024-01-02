#include "MonsterPool.h"
#include "MonsterManager.h"
#include "MonsterCreate.h"
#include "Monster.h"
#include "SoundUtil.h"

bool MonsterPool::init()
{
	numPerBatch = 10;
	delay = initTimeDelay;
	monsterCount = 0;
	MonsterOccurred = 0;
	delay = true;
	Id = 0;
	batch = 0;
	MonsterAnimation = Animation::create();
	MonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm01.png"));
	MonsterAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mcm02.png"));
	MonsterAnimation->setDelayPerUnit(0.15);
	MonsterAnimation->setLoops(1);
	MonsterAnimation->retain();
	FileBatch = 15;
	//填一下这里初始化的位置//

	return true;
}

void MonsterPool::MonsterUpdate(float t)
{
	if (monsterCount == 10 * FileBatch)
	{
		//最后一波
		this->unschedule(schedule_selector(MonsterPool::MonsterUpdate));
	}
	batch = monsterCount / 10 + 1;
	MonsterPoolController();
	monsterCount++;
	MonsterOccurred++;
	if (monsterCount == 10)
	{
		timeDelay = 0;
		monsterCount = 0;
	}
}
void MonsterPool::MonsterPoolController()
{
	SoundUtil::getInstance()->playEffect(BUILDMONSTER);
	if (Id == 10)Id = 0;
	int number = 10 - (batch - 1) * 2;
	MonsterBase* pMonster;
	if (batch == FileBatch && Id == 5)
	{
		pMonster = MonsterCreate::createMonster(en_Land_Boss_Star);
	}
	else
	{
		if (Id < number)
		{
			pMonster = MonsterCreate::createMonster(MonsterType(1 + int(batch / 5)));
		}
		else
		{
			pMonster = MonsterCreate::createMonster(MonsterType(4 + int(batch / 5)));
		}
	}
	pMonster->setIHp(pMonster->getIHp() + (batch - 1) / 5 * pMonster->getIHp());
	pMonster->setSpeed(pMonster->getISpeed() + int(batch / 5) * 10);
	pMonster->getSprite()->runAction(Animate::create(MonsterAnimation));
	number++;
}


void MonsterPool::onEnter()
{
	Node::onEnter();
	schedule(schedule_selector(MonsterPool::MonsterUpdate), 1.5, INT_MAX, 3);
}

int MonsterPool::getBatch()
{
	return batch;
}
