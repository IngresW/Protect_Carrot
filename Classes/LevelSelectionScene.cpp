#include "LevelSelectionScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;


SaveData CurrentData = SaveData();

Scene* LevelSelectionScene::createScene()
{
    return LevelSelectionScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool LevelSelectionScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    CurrentData = SaveGameManagement::saveSlots[SaveGameManagement::choosedSlot];

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto background = cocos2d::Sprite::create("LevelScene/LevelSelection.png");

    float backgroundImageWidth = background->getContentSize().width;
    background->setAnchorPoint(cocos2d::Vec2(0, 0));  // 设置锚点为左下角
    background->setPosition(cocos2d::Vec2(0, 0));    // 设置位置为初始屏幕左下角

    //background->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    this->addChild(background);


    auto ChooseLevel1Button = MenuItemImage::create("LevelScene/Level.png",
        "LevelScene/Level.png", CC_CALLBACK_1(LevelSelectionScene::onChooseLevel1Clicked, this));

    float x = origin.x + visibleSize.width / 2 - 80;
    float y = origin.y + visibleSize.height / 2 + 80;

    ChooseLevel1Button->setPosition(Vec2(x, y));

    auto ChooseLevel2Button = MenuItemImage::create("LevelScene/Level.png",
        "LevelScene/Level.png", CC_CALLBACK_1(LevelSelectionScene::onChooseLevel2Clicked, this));

    x = origin.x + visibleSize.width / 2 + 50;
    y = origin.y + visibleSize.height / 2 - 50;

    ChooseLevel2Button->setPosition(Vec2(x, y));

    auto backButton = MenuItemImage::create("LevelScene/home.png", "LevelScene/home.png", CC_CALLBACK_1(LevelSelectionScene::onBackButtonClicked, this));
    backButton->setPosition(Vec2(origin.x + 40, visibleSize.height + origin.y - 40));

    auto shopButton = MenuItemImage::create("LevelScene/shop.png", "LevelScene/shop.png", CC_CALLBACK_1(LevelSelectionScene::onShopButtonClicked, this));
    shopButton->setPosition(Vec2(origin.x + 110, visibleSize.height + origin.y - 40));

    // 创建菜单
    auto menu = cocos2d::Menu::create(ChooseLevel1Button, ChooseLevel2Button, backButton, shopButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void LevelSelectionScene::onChooseLevel1Clicked(cocos2d::Ref* sender)
{
    Director::getInstance()->pushScene(LevelScene::createScene());
}


void LevelSelectionScene::onChooseLevel2Clicked(cocos2d::Ref* sender)
{
    Director::getInstance()->pushScene(Level_2::createScene());
}

void LevelSelectionScene::onShopButtonClicked(Ref* sender)
{
    Director::getInstance()->pushScene(ShopScene::createScene());
}

void LevelSelectionScene::onBackButtonClicked(Ref* sender)
{
    SaveGameManagement::saveSlot(CurrentData);
    SaveGameManagement::SaveSaveData();

    // 返回主界面
    cocos2d::Director::getInstance()->popScene();
    cocos2d::Director::getInstance()->popScene();
}