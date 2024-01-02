#ifndef MONSTER__POOL
#define MONSTER__POOL
#include"PublicDefine.h"

class MonsterPool:public Node
{
public:
	bool MonsterPool::init();
	int getBatch();
	CREATE_FUNC(MonsterPool);
	int numPerBatch;//ÿ�����������
	
protected:
	int monsterCount;//�ڳ���������
	const int initTimeDelay = 8;//������ʱ
	int timeDelay;//���ɹ�����ʱ
	bool delay;//�Ƿ���ʱ����
	int batch;//�ڼ�����
	int FileBatch;//��ȡ������
	int MonsterOccurred;//�����ɹ��Ĺ���
	int Id;//���ɵĹ�����
	Animation* MonsterAnimation;
	void onEnter();
	void MonsterUpdate(float t);
	void MonsterPoolController();
};




#endif