#include "LoadGameScene.h"
#include "LevelSelectionScene.h"
#include "MainMenuScene.h"

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

    SaveGameManagement::LoadSaveData();

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建文字标题
    auto label = Label::createWithTTF("Load Game", "fonts / Marker Felt.ttf", 24);
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

    // 创建读取存档界面背景和按钮
    auto background = Sprite::create("LoadScene/load_game_background.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);


    // 创建存档信息显示

    for (int i = 0; i < 3; i++)
    {
        std::string labelText = SaveGameManagement::DisplayForLoad(i);
        // 创建 Label 组件
        auto label = Label::createWithTTF(labelText, "fonts/arial.ttf", 30);
        label->setPosition(Vec2(visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y + 105 - i * 135));
        this->addChild(label);
    }


    // 创建按钮
    auto loadGameButton1 = MenuItemImage::create("LoadScene/choose.png", "LoadScene/choose.png",
        CC_CALLBACK_1(LoadGameScene::onLoadGameButton1Clicked, this));
    loadGameButton1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y + 135));

    auto loadGameButton2 = MenuItemImage::create("LoadScene/choose.png", "LoadScene/choose.png",
        CC_CALLBACK_1(LoadGameScene::onLoadGameButton2Clicked, this));
    loadGameButton2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y - 0));

    auto loadGameButton3 = MenuItemImage::create("LoadScene/choose.png", "LoadScene/choose.png",
        CC_CALLBACK_1(LoadGameScene::onLoadGameButton3Clicked, this));
    loadGameButton3->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y - 135));

    auto backButton = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(LoadGameScene::onBackButtonClicked, this));
    backButton->setPosition(Vec2(origin.x + 40, visibleSize.height + origin.y - 40));

    auto deleteButton1 = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(LoadGameScene::ondeleteButton1Clicked, this));
    deleteButton1->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y + 85));

    auto deleteButton2 = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(LoadGameScene::ondeleteButton2Clicked, this));
    deleteButton2->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y - 50));

    auto deleteButton3 = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(LoadGameScene::ondeleteButton3Clicked, this));
    deleteButton3->setPosition(Vec2(visibleSize.width / 2 + origin.x + 350, visibleSize.height / 2 + origin.y - 185));

    // 创建菜单
    auto menu = Menu::create(loadGameButton1, loadGameButton2, loadGameButton3, deleteButton1, deleteButton2, deleteButton3, backButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void LoadGameScene::onLoadGameButton1Clicked(Ref* sender)
{
    // 加载存档并切换到关卡选择界面
    SaveGameManagement::chooseSlot(0);
    Director::getInstance()->pushScene(LevelSelectionScene::createScene());
}

void LoadGameScene::onLoadGameButton2Clicked(Ref* sender)
{
    // 加载存档并切换到关卡选择界面
    SaveGameManagement::chooseSlot(1);
    Director::getInstance()->pushScene(LevelSelectionScene::createScene());
}

void LoadGameScene::onLoadGameButton3Clicked(Ref* sender)
{
    // 加载存档并切换到关卡选择界面
    SaveGameManagement::chooseSlot(2);
    Director::getInstance()->pushScene(LevelSelectionScene::createScene());
}
void LoadGameScene::onBackButtonClicked(Ref* sender)
{
    // 返回主界面
    cocos2d::Director::getInstance()->popScene();
}

void LoadGameScene::ondeleteButton1Clicked(Ref* sender)
{
    SaveGameManagement::deleteSlot(1);
}
void LoadGameScene::ondeleteButton2Clicked(Ref* sender)
{
    SaveGameManagement::deleteSlot(2);
}
void LoadGameScene::ondeleteButton3Clicked(Ref* sender)
{
    SaveGameManagement::deleteSlot(3);
}