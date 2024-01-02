#include"Monster.h"
#include"MonsterCreate.h"
#include"MonsterManager.h"
#include"SoundUtil.h"
#include"PublicDefine.h"


LevelScene levelScene;

MonsterBase* MonsterBase::create(const int& rID)
{
	auto pMonster = new MonsterBase();
	if (pMonster && pMonster->init(rID))
	{
		pMonster->autorelease();
		return pMonster;
	}
	CC_SAFE_DELETE(pMonster);
	return nullptr;
}

void MonsterBase::createAnimation()
{
	std::vector<std::string> AnimationFiles;
	for (int i = 1; i <= _IAnimationFrameCount; i++)
	{
		AnimationFiles.push_back(_sModelName + StringUtils::format("%d.png",i));
	}
	createDynamicEntityAnimation(AnimationFiles);
}

void MonsterBase::setAction(const float& rDt)
{
	_Animation->setDelayPerUnit(rDt);
	getSprite()->runAction(Animate::create(_Animation));
}

bool MonsterBase::init(const int& rID)
{
	if (!EntityAffected::init(rID, MONSTERCSVFILE) || !DynamicInterface::init(rID, MONSTERCSVFILE))
	{
		return false;
	}
	_currentNodeIndex = 0;
	_currentPosition = levelScene.ij_to_xy(levelScene.levelPath[_currentNodeIndex].i, levelScene.levelPath[_currentNodeIndex].j);
	_bLeft = true;
	createAnimation();
	setAction(0.15f);
	MonsterManager::getInstance()->addMonster(this);
	scheduleUpdate();

	return true;
}

void MonsterBase::deadAction(const std::string& rSDeadFile)
{
	sound();
	NOTIFY->postNotification("MonsterDead", this);
	getSprite()->removeAllChildrenWithCleanup(true);
	EntityAffected::deadAction();
}

void MonsterBase::sound()
{
	const int fFigure = rand() % 3 + 1;
	SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Land11%d.mp3", fFigure));
}

void MonsterBase::setSpeed(const int& Speed)
{
	setISpeed(Speed);
}

void MonsterBase::update(float dt)
{

	// 判断是否到达终点
	if (_currentNodeIndex >= levelScene.levelPath.size() - 1)
	{
		// 到达终点，停止移动
		unscheduleUpdate();
		return;
	}

	// 获取下一个节点的位置
	Vec2 nextPosition = levelScene.ij_to_xy(levelScene.levelPath[_currentNodeIndex + 1].i, levelScene.levelPath[_currentNodeIndex + 1].j);

	// 计算移动方向和距离
	Vec2 direction = (nextPosition - _currentPosition).getNormalized();
	float distance = getISpeed() * dt;

	// 计算新的位置
	Vec2 newPosition = _currentPosition + direction * distance;

	// 判断是否到达下一个节点
	if ((nextPosition - _currentPosition).length() <= distance)
	{
		// 到达下一个节点，更新当前位置和节点索引
		_currentPosition = nextPosition;
		_currentNodeIndex++;
	}
	else
	{
		// 还未到达下一个节点，更新当前位置
		_currentPosition = newPosition;
	}

	// 设置Monster的位置
	setPosition(_currentPosition);
}