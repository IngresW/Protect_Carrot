#include "LoadGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* LoadGameScene::createScene()
{
    return LoadGameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool LoadGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建文字标题
    auto label = Label::createWithTTF("Load Game", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // 创建背景精灵
    auto background = cocos2d::Sprite::create("background.png");
    background->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    this->addChild(background);

    // 创建返回按钮
    auto backButton = cocos2d::MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(LoadGameScene::onBackClicked, this));
    backButton->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width - 80, 80);

    // 创建加载按钮
    auto loadButton = cocos2d::MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(LoadGameScene::onLoadClicked, this));
    loadButton->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);

    // 创建菜单
    auto menu = cocos2d::Menu::create(backButton, loadButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void LoadGameScene::onBackClicked(cocos2d::Ref* sender)
{
    // 处理返回按钮点击事件
    cocos2d::Director::getInstance()->popScene();
}

void LoadGameScene::onLoadClicked(cocos2d::Ref* sender)
{
    // 处理加载按钮点击事件
    // 在这里添加加载存档的逻辑
}