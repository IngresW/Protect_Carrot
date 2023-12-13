#ifndef _NEWGAME_SCENE_H
#define _NEWGAME_SCENE_H

#include "cocos2d.h"
class NewGameScene:public  cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 按钮点击事件创建一个新的存档函数
    void onCreateLoadClicked(cocos2d::Ref* sender);

    //返回到主菜单界面
    void onBacktoMainClicked(cocos2d::Ref* sender);

    CREATE_FUNC(NewGameScene);
};


#endif

