#include "NewGameScene.h"
#include <ui/UIEditBox/UIEditBox.h>


USING_NS_CC;

Scene* NewGameScene::createScene()
{
    return NewGameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool NewGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建新建角色界面背景和按钮
    auto background = cocos2d::Sprite::create("LoadScene/new_game_background.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    float x = visibleSize.width / 2 + origin.x + 50;
    float y = visibleSize.height / 2 + origin.y + 10;

    // 创建文本输入框
    auto characterNameInput = ui::EditBox::create(Size(200, 50), "LoadScene/input_box.png");
    characterNameInput->setPosition(Vec2(x, y));
    characterNameInput->setMaxLength(20);
    characterNameInput->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    characterNameInput->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    characterNameInput->setTag(1);
    this->addChild(characterNameInput);
    
    // 创建按钮
    auto createCharacterButton = MenuItemImage::create("LoadScene/create_character_button.png", "LoadScene/create_character_button.png",
        CC_CALLBACK_1(NewGameScene::onCreateCharacterButtonClicked, this));

    createCharacterButton->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 100));

    auto backButton = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(NewGameScene::onBackButtonClicked, this));

    backButton->setPosition(Vec2(origin.x + 40, visibleSize.height + origin.y - 40));

    // 创建菜单
    auto menu = Menu::create(createCharacterButton, backButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void NewGameScene::onCreateCharacterButtonClicked(cocos2d::Ref* sender)
{
    // 切换到关卡选择界面
    auto editbox1 = (ui::EditBox*)this->getChildByTag(1);
    character_Name = editbox1->getText();
    SaveGameManagement::createNewSlot(character_Name);
    
    Director::getInstance()->pushScene(LevelSelectionScene::createScene());
}

void NewGameScene::onBackButtonClicked(cocos2d::Ref* sender)
{
    // 返回主界面
    cocos2d::Director::getInstance()->popScene();
}

void NewGameScene::textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType type)
{
    auto textField = dynamic_cast<cocos2d::ui::TextField*>(sender);
    if (!textField) {
        return;
    }

    if (type == cocos2d::ui::TextField::EventType::DETACH_WITH_IME) {
        character_Name = textField->getString();
    }
}