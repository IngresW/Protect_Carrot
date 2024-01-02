#ifndef MONSTER__POOL
#define MONSTER__POOL
#include"PublicDefine.h"

class MonsterPool:public Node
{
public:
	bool MonsterPool::init();
	int getBatch();
	CREATE_FUNC(MonsterPool);
	int numPerBatch;//每波怪物的数量
	
protected:
	int monsterCount;//在场怪物数量
	const int initTimeDelay = 8;//常规延时
	int timeDelay;//生成怪物延时
	bool delay;//是否延时生成
	int batch;//第几波怪
	int FileBatch;//读取几波怪
	int MonsterOccurred;//已生成过的怪物
	int Id;//生成的怪物编号
	Animation* MonsterAnimation;
	void onEnter();
	void MonsterUpdate(float t);
	void MonsterPoolController();
};




#endif