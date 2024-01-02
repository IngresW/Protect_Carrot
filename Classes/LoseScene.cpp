#include "LoseScene.h"

#include "ShopScene.h"

USING_NS_CC;

Scene* LoseScene::createScene()
{
    return LoseScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool LoseScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto background = Sprite::create("LoseScene.png");

    background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

    this->addChild(background);


    // 创建退出按钮
    auto backButton = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(LoseScene::onBackButtonClicked, this));

    backButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 200));

    // 创建菜单
    auto menu = Menu::create(backButton,nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void LoseScene::onBackButtonClicked(cocos2d::Ref* sender)
{
    // 返回选关界面
    cocos2d::Director::getInstance()->popScene();
}
