#ifndef MONSTER__
#define MONSTER__

#include "EntityAffected.h"
#include "DynamicInterface.h"
#include "LevelScene.h"

class MonsterBase :public EntityAffected, public DynamicInterface
{
public:
	static MonsterBase* create(const int& rID);
	void setSpeed(const int& Speed);
	void update(float dt);

protected:
	virtual void deadAction(const std::string& rSDeadImageFile = "")override;
	virtual void setAction(const float& rDt);
	virtual bool init(const int& rID);
	virtual void createAnimation();
	virtual void sound();
	CC_SYNTHESIZE_PASS_BY_REF(bool, _bLeft, Left);
	Vec2 _currentPosition; // 当前位置
	int _currentNodeIndex; // 当前节点索引
};


#endif
