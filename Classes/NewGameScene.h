#ifndef _NEWGAME_SCENE_H
#define _NEWGAME_SCENE_H

#include "cocos2d.h"
#include "LevelSelectionScene.h"
#include "SaveGameManager.h"
#include "SimpleAudioEngine.h"
#include "cocos/ui/CocosGUI.h"

class NewGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 按钮回调函数
    void onCreateCharacterButtonClicked(cocos2d::Ref* sender);
    void onBackButtonClicked(cocos2d::Ref* sender);

    void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(NewGameScene);

    SaveGameManagement saveGameManagement;
    std::string character_Name;
};

#endif

