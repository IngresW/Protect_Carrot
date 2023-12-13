#ifndef _LOAD_GAME_SCENE_H__
#define _LOAD_GAME_SCENE_H__

#include "cocos2d.h"

class LoadGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // ��ť����¼��ص�����
    void onBackClicked(cocos2d::Ref* sender);
    void onLoadClicked(cocos2d::Ref* sender);

    CREATE_FUNC(LoadGameScene);
};

#endif // __LOAD_GAME_SCENE_H__
