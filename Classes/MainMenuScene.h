#ifndef _MAIN_MENU_SCENE_H__
#define _MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // ��ť����¼��ص�����
    void onNewGameClicked(cocos2d::Ref* sender);

    void onLoadGameClicked(cocos2d::Ref* sender);

    void onQuitClicked(cocos2d::Ref* sender);

    CREATE_FUNC(MainMenuScene);
};

#endif