#ifndef _NEWGAME_SCENE_H
#define _NEWGAME_SCENE_H

#include "cocos2d.h"
class NewGameScene:public  cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // ��ť����¼�����һ���µĴ浵����
    void onCreateLoadClicked(cocos2d::Ref* sender);

    //���ص����˵�����
    void onBacktoMainClicked(cocos2d::Ref* sender);

    CREATE_FUNC(NewGameScene);
};


#endif

