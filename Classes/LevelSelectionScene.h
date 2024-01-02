#ifndef _LEVEL_SELECTION_SCENE_H__
#define _LEVEL_SELECTION_SCENE_H__

#include "cocos2d.h"
#include "SaveGameManager.h"
#include "LevelScene.h"
#include "ShopScene.h"
#include "Level_2.h"

class LevelSelectionScene : public cocos2d::Scene
{
public:
    friend class ShopScene;
    friend class LevelScene;
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 按钮点击事件回调函数
    void onChooseLevel1Clicked(cocos2d::Ref* sender);
    void onChooseLevel2Clicked(cocos2d::Ref* sender);

    void onBackButtonClicked(cocos2d::Ref* sender);
    void onShopButtonClicked(cocos2d::Ref* sender);


    //void updataBlood()
    //{
    //    CurrentData.characterUnlockProgress++;
    //    CurrentData.coinCount -= 10;
    //}

    //int getLevel()
    //{
    //    return CurrentData.characterUnlockProgress;
    //}

    CREATE_FUNC(LevelSelectionScene);
};

#endif // _LEVEL_SELECTION_SCENE_H__
