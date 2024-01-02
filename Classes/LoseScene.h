#ifndef _LOSE_SCENE
#define _LOSE_SCENE

#include "cocos2d.h"
#include "SaveGameManager.h"
#include "SimpleAudioEngine.h"
#include "cocos/ui/CocosGUI.h"

USING_NS_CC;

class LoseScene:public cocos2d::Scene
{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();

    void onBackButtonClicked(cocos2d::Ref* sender);
    CREATE_FUNC(LoseScene);
};


#endif