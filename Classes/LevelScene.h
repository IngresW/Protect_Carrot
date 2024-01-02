#ifndef _LEVEL_SCENE_H
#define _LEVEL_SCENE_H

#include "cocos2d.h"
#include "LevelSelectionScene.h"
#include "SaveGameManager.h"
#include "SimpleAudioEngine.h"
#include "cocos/ui/CocosGUI.h"
#include "LoseScene.h"
#include "MonsterPool.h"
#include "PublicDefine.h"
#include "MyMonster.h"
#include <string>

USING_NS_CC;

extern SaveData CurrentData;

class LevelScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init() override;

    CREATE_FUNC(LevelScene);

    void onBackButtonClicked(cocos2d::Ref* sender);

    Vec2 ij_to_xy(int i, int j)
    {
        float x = 40 + j * 85;
        float y = 240 + (4 - i) * 80;

        return Vec2(x, y);
    }
    Vec2 xy_to_ij(Vec2 vec)
    {
        int j = (vec.x - 40) / 85.0;
        int i = 4 - ((vec.y - 240) / 80.0);
        return Vec2(i, j);
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

    void build(Vec2 position, int tower_available[]);

    const std::string monsterIdl;

    void updateMonster(float dt);
    void updateWave(float dt);

    void Move();
private:

    MenuItemImage* pauseButton;
    MenuItemImage* resumeButton;
    Label* goldLabel;
    std::vector<PathNode> path;
    Sprite* monster;

    int goldCount = 450;
    bool if_speed_up = 0;
    bool if_pause = 0;
    int carrot_hp = 5 + CurrentData.characterUnlockProgress * 5;
    
    int wave = 0, order = 0;
    /******************地图初始化************************/
    const char level_1_map[5][12] = {
     {0,-1,0,0,0,0,0,0,0,0,2,0},
      {0,1,0,0,0,0,0,0,0,0,1,0},
      {0,1,0,0,1,1,1,1,0,0,1,0},
      {0,1,1,1,1,0,0,1,1,1,1,0},
      {0,0,0,0,0,0,0,0,0,0,0,0},
    };
    
    Sprite* grid[5][12];
    Label* hp_label;

    int Monster_Wave[5][5] = {
        {1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},
        {1,1,1,1,1},{1,1,1,1,1},
    };


};



/*
倒计时：释放波次，上一波结束释放下一波
怪物池：生成怪物，添加路径
点击安装炮塔：点击显示炮塔半径和升级/销毁
金币
萝卜
结算画面
*/
#endif

