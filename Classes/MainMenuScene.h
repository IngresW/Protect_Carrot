#ifndef _MAIN_MENU_SCENE_H__
#define _MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "SaveGameManager.h"

using namespace tinyxml2;

class MainMenuScene : public cocos2d::Scene
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();

    // ��ť����¼��ص�����
    void onNewGameClicked(cocos2d::Ref* sender);

    void onLoadGameClicked(cocos2d::Ref* sender);

    void onQuitClicked(cocos2d::Ref* sender);


    CREATE_FUNC(MainMenuScene);
};

#endif