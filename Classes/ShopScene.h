#ifndef _SHOP_SCENE_H__
#define _SHOP_SCENE_H__

#include "cocos2d.h"
#include "LevelSelectionScene.h"
#include "SaveGameManager.h"
#include "SimpleAudioEngine.h"
#include "cocos/ui/CocosGUI.h"

USING_NS_CC;

extern SaveData CurrentData;

class ShopScene: public cocos2d::Scene
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();

    // 按钮点击事件回调函数

    void onBackButtonClicked(cocos2d::Ref* sender);

    void onUpdateButtonClicked(cocos2d::Ref* sender);

    Label* LevelLabel;
    Label* CoinLabel;

    void updateLevel()
    {
        LevelLabel->setString(StringUtils::format("Level: %d", CurrentData.characterUnlockProgress));
        CoinLabel->setString(StringUtils::format("Coin: %d", CurrentData.coinCount));  
    }
    CREATE_FUNC(ShopScene);

};
#endif