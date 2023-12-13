#ifndef _LEVEL_SELECTION_SCENE_H__
#define _LEVEL_SELECTION_SCENE_H__

#include "cocos2d.h"

/*
* �������Ҫʵ�ֵĹ��ܰ�����
* ѡ��ؿ�1��2...
* ��ѡ��ؿ��󵯳��ؿ�Ԥ����ͼ���Լ���ʼ��ս�İ�ť��Ԥ�������ɳ���ջ��ʵ�֣�
* 
* ������ת���̵����
* 
* ������ɵĹؿ��������Ե���ʾ
* �ڵ�ǰ���������ܲ������ʾ

*/
class LevelSelectionScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // ��ť����¼��ص�����
    void onChooseLevel1Clicked(cocos2d::Ref* sender);
    void onChooseLevel2Clicked(cocos2d::Ref* sender);

    CREATE_FUNC(LevelSelectionScene);
};

#endif // _LEVEL_SELECTION_SCENE_H__
