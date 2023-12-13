#include "MainMenuScene.h"
#include "NewGameScene.h"
#include "LoadGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}
// Print useful error message instead of segfaulting when files are not there.

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto background = Sprite::create("MainMenu/MainmenuScene.png");

    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    this->addChild(background);

    auto title = Sprite::create("MainMenu/Title.png");

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2 + 80;

    title->setPosition(Vec2(x, y));

    this->addChild(title);

    // 创建新建游戏按钮
    auto newGameButton = MenuItemImage::create("MainMenu/NewGameNormal.png",
                                               "MainMenu/NewGameSelected.png", 
                                                CC_CALLBACK_1(MainMenuScene::onNewGameClicked, this));

    x = origin.x + visibleSize.width / 2;
    y = origin.y + visibleSize.height / 2 - 10;

    newGameButton->setPosition(Vec2(x,y));

    // 创建读取存档按钮
    auto loadGameButton = MenuItemImage::create("MainMenu/LoadGameNormal.png",
                                                "MainMenu/LoadGameSelected.png",
                                                 CC_CALLBACK_1(MainMenuScene::onLoadGameClicked, this));

    y = origin.y + visibleSize.height / 2 - 60;

    loadGameButton->setPosition(Vec2(x, y));

    // 创建退出游戏按钮
    auto quitButton = MenuItemImage::create("MainMenu/QuitNormal.png",
                                            "MainMenu/QuitSelected.png",        
                                            CC_CALLBACK_1(MainMenuScene::onQuitClicked, this));

    y = origin.y + visibleSize.height / 2 - 110;

    quitButton->setPosition(Vec2(x, y));

    // 创建菜单
    auto menu = Menu::create(newGameButton, loadGameButton, quitButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void MainMenuScene::onNewGameClicked(cocos2d::Ref* sender)
{
    // 处理新建游戏按钮点击事件
    // 创建新建游戏场景
    auto newGameScene = NewGameScene::createScene();

    // 切换到新建游戏场景
    cocos2d::Director::getInstance()->pushScene(newGameScene);
    //Director::getInstance()->end();
}

void MainMenuScene::onLoadGameClicked(cocos2d::Ref* sender)
{
    // 处理读取存档按钮点击事件
    // 创建读取存档场景
    auto loadGameScene = LoadGameScene::createScene();

    // 切换到读取存档场景
    cocos2d::Director::getInstance()->pushScene(loadGameScene);
}

void MainMenuScene::onQuitClicked(cocos2d::Ref* sender)
{
    // 处理退出游戏按钮点击事件
    Director::getInstance()->end();
}