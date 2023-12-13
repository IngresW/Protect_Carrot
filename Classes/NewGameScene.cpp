#include "NewGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* NewGameScene::createScene()
{
    return NewGameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
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

    // ������������
    auto background = cocos2d::Sprite::create("background.png");
    background->setPosition(cocos2d::Director::getInstance()->getVisibleSize() / 2);
    this->addChild(background);

    // �������ֱ���
    auto label = Label::createWithTTF("Create New Charactor", "fonts/Marker Felt.ttf", 24);
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

    // �������ذ�ť
    auto backButton = cocos2d::MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(NewGameScene::onBacktoMainClicked, this));
    backButton->setPosition(cocos2d::Director::getInstance()->getVisibleSize().width - 80, 80);

    // �����˵�
    auto menu = cocos2d::Menu::create(backButton, nullptr);
    menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(menu);

    return true;
}


// ��ť����¼�����һ���µĴ浵
void onCreateLoadClicked(cocos2d::Ref* sender)
{

}


void NewGameScene::onBacktoMainClicked(cocos2d::Ref* sender)
{
    // �����ذ�ť����¼�
    cocos2d::Director::getInstance()->popScene();
}