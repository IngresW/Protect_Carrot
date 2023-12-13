#ifndef _LEVEL_SELECTION_SCENE_H__
#define _LEVEL_SELECTION_SCENE_H__

#include "cocos2d.h"

/*
* 这个类需要实现的功能包括：
* 选择关卡1或2...
* 在选择关卡后弹出关卡预览地图，以及开始作战的按钮（预览界面由场景栈来实现）
* 
* 可以跳转至商店界面
* 
* 在已完成的关卡上有明显的提示
* 在当前进度上有萝卜任务表示

*/
class LevelSelectionScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 按钮点击事件回调函数
    void onChooseLevel1Clicked(cocos2d::Ref* sender);
    void onChooseLevel2Clicked(cocos2d::Ref* sender);

    CREATE_FUNC(LevelSelectionScene);
};

#endif // _LEVEL_SELECTION_SCENE_H__
