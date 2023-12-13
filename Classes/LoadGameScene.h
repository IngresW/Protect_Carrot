#ifndef _LOAD_GAME_SCENE_H__
#define _LOAD_GAME_SCENE_H__

#include "cocos2d.h"

class LoadGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 按钮点击事件回调函数
    void onBackClicked(cocos2d::Ref* sender);
    void onLoadClicked(cocos2d::Ref* sender);

    CREATE_FUNC(LoadGameScene);
};

#endif // __LOAD_GAME_SCENE_H__
