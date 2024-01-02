#ifndef _LEVEL_SCENE_2_H
#define _LEVEL_SCENE_2_H

#include "cocos2d.h"
#include "LevelSelectionScene.h"
#include "SaveGameManager.h"
#include "SimpleAudioEngine.h"
#include "cocos/ui/CocosGUI.h"
#include "LoseScene.h"
#include <string>

USING_NS_CC;

extern SaveData CurrentData;



class Level_2 : public cocos2d::Scene
{
public:
    struct PathNode
    {
        int i, j;
        char dir;
    };


    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(Level_2);

    void onBackButtonClicked(cocos2d::Ref* sender);

    Vec2 ij_to_xy(int i, int j)
    {
        float x = 40 + j * 85;
        float y = 240 + (4 - i) * 80;

        return Vec2(x, y);
    }

    void pauseButtonClicked(cocos2d::Ref* sender);
    void resumeButtonClicked(cocos2d::Ref* sender);

    void updateGoldCount(int gold)
    {
        // 更新金币数量
        goldCount += gold;

        // 更新金币标签文本
        goldLabel->setString(StringUtils::format("Gold: %d", goldCount));
    }

    void goToFailScene();


    std::vector<PathNode> levelPath;
private:

    MenuItemImage* pauseButton;
    MenuItemImage* resumeButton;
    Label* goldLabel;

    int goldCount = 450;
    bool if_speed_up = 0;
    bool if_pause = 0;
    int carrot_hp = 5 + CurrentData.characterUnlockProgress * 5;


};

#endif

