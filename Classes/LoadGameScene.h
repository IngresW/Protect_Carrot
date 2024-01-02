#ifndef _LOAD_GAME_SCENE_H__
#define _LOAD_GAME_SCENE_H__

#include "cocos2d.h"
#include "SaveGameManager.h"
#include "SimpleAudioEngine.h"

extern SaveData CurrentData;

class LoadGameScene : public cocos2d::Scene
{
private:
    SaveGameManagement saveGameManagement;
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    

    // 按钮点击事件回调函数 
    void onLoadGameButton1Clicked(cocos2d::Ref* sender);
    void onLoadGameButton2Clicked(cocos2d::Ref* sender);
    void onLoadGameButton3Clicked(cocos2d::Ref* sender);

    void ondeleteButton1Clicked(cocos2d::Ref* sender);
    void ondeleteButton2Clicked(cocos2d::Ref* sender);
    void ondeleteButton3Clicked(cocos2d::Ref* sender);

    void onBackButtonClicked(cocos2d::Ref* sender);

    
    CREATE_FUNC(LoadGameScene);
};

#endif // __LOAD_GAME_SCENE_H__
