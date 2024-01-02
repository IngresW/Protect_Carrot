#include "ShopScene.h"

USING_NS_CC;

Scene* ShopScene::createScene()
{
    return ShopScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool ShopScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto background = Sprite::create("ShopScene.png");

    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    this->addChild(background);

    auto updateButton = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(ShopScene::onUpdateButtonClicked, this));

    updateButton->setPosition(Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y - 200));

    int i = CurrentData.characterUnlockProgress;
    LevelLabel = Label::createWithTTF("Level: " + std::to_string(i), "fonts/arial.ttf", 30);
    LevelLabel->setAnchorPoint(Vec2(1, 1));
    LevelLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y + 40));
    this->addChild(LevelLabel);

    CoinLabel = Label::createWithTTF("Coin: " + std::to_string(CurrentData.coinCount), "fonts/arial.ttf", 30);
    CoinLabel->setAnchorPoint(Vec2(1, 1));
    CoinLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y));
    this->addChild(CoinLabel);

    // 创建退出按钮
    auto backButton = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(ShopScene::onBackButtonClicked, this));

    backButton->setPosition(Vec2(origin.x + 40, visibleSize.height + origin.y - 40));

    // 创建菜单
    auto menu = Menu::create(backButton, updateButton,nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void ShopScene::onBackButtonClicked(cocos2d::Ref* sender)
{
    // 返回选关界面
    cocos2d::Director::getInstance()->popScene();
}

void ShopScene::onUpdateButtonClicked(cocos2d::Ref* sender)
{
    if (CurrentData.coinCount >= 10)
    {
        CurrentData.characterUnlockProgress++;
        CurrentData.coinCount -= 10;
    }
    updateLevel();
}
