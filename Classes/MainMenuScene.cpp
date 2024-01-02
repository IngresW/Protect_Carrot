#include "MainMenuScene.h"
#include "NewGameScene.h"
#include "LoadGameScene.h"
#include "LevelSelectionScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

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

    // ������������
    auto background = Sprite::create("MainMenu/MainmenuScene.png");

    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    this->addChild(background);

    auto title = Sprite::create("MainMenu/Title.png");

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2 + 200;

    title->setPosition(Vec2(x, y));

    this->addChild(title);

    // �����½���Ϸ��ť
    auto newGameButton = MenuItemImage::create("MainMenu/NewGameNormal.png",
                                               "MainMenu/NewGameSelected.png", 
                                                CC_CALLBACK_1(MainMenuScene::onNewGameClicked, this));

    x = origin.x + visibleSize.width / 2;
    y = origin.y + visibleSize.height / 2 - 10;

    newGameButton->setPosition(Vec2(x,y));

    // ������ȡ�浵��ť
    auto loadGameButton = MenuItemImage::create("MainMenu/LoadGameNormal.png",
                                                "MainMenu/LoadGameSelected.png",
                                                 CC_CALLBACK_1(MainMenuScene::onLoadGameClicked, this));

    y = origin.y + visibleSize.height / 2 - 110;

    loadGameButton->setPosition(Vec2(x, y));

    // �����˳���Ϸ��ť
    auto quitButton = MenuItemImage::create("MainMenu/QuitNormal.png",
                                            "MainMenu/QuitSelected.png",        
                                            CC_CALLBACK_1(MainMenuScene::onQuitClicked, this));

    y = origin.y + visibleSize.height / 2 - 210;

    quitButton->setPosition(Vec2(x, y));

    // �����˵�
    auto menu = Menu::create(newGameButton, loadGameButton, quitButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void MainMenuScene::onNewGameClicked(cocos2d::Ref* sender)
{
    // �����½���Ϸ����
    auto newGameScene = NewGameScene::createScene();

    // �л����½���Ϸ����
    cocos2d::Director::getInstance()->pushScene(newGameScene);
}

void MainMenuScene::onLoadGameClicked(cocos2d::Ref* sender)
{
    // �����½���Ϸ����
    auto loadGameScene = LoadGameScene::createScene();

    // �л����½���Ϸ����
    cocos2d::Director::getInstance()->pushScene(loadGameScene);
}

void MainMenuScene::onQuitClicked(cocos2d::Ref* sender)
{
    // �����˳���Ϸ��ť����¼�
    Director::getInstance()->end();
}

