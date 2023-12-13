#include "LevelSelectionScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

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

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto background = cocos2d::Sprite::create("background.png");
    background->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    this->addChild(background);

    // 创建文字标题
    auto label = Label::createWithTTF("Select Level", "fonts/Marker Felt.ttf", 24);
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

    auto ChooseLevel1Button = MenuItemImage::create("CloseNormal.png",
        "CloseSelected.png", CC_CALLBACK_1(LevelSelectionScene::onChooseLevel1Clicked, this));

    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;

    ChooseLevel1Button->setPosition(Vec2(x, y));

    auto ChooseLevel2Button = MenuItemImage::create("CloseNormal.png",
        "CloseSelected.png", CC_CALLBACK_1(LevelSelectionScene::onChooseLevel2Clicked, this));

    x = origin.x + visibleSize.width / 2;
    y = origin.y + visibleSize.height / 2 -100;

    ChooseLevel2Button->setPosition(Vec2(x, y));

   
    // 创建菜单
    auto menu = cocos2d::Menu::create(ChooseLevel1Button, ChooseLevel2Button, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(menu);

    return true;
}


// 按钮点击事件创建一个新的存档
void LevelSelectionScene::onChooseLevel1Clicked(cocos2d::Ref* sender)
{


}


void LevelSelectionScene::onChooseLevel2Clicked(cocos2d::Ref* sender)
{


}
