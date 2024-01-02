#include "Level_2.h"

USING_NS_CC;

struct pos
{
    int i, j;
};

Scene* Level_2::createScene()
{
    return Level_2::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Level_2::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建新建角色界面背景和按钮
    auto background = cocos2d::Sprite::create("LevelScene/map.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    auto Path = cocos2d::Sprite::create("LevelScene/BG-2.png");
    Path->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 40));
    this->addChild(Path);

    /******************地图初始化************************/
    const char level_2_map[6][12] = {
     {0,0,0,0,-1,1,1,1,1,1,0,0},
      {0,0,0,0,0,0,0,0,0,1,0,0},
      {0,0,1,1,1,1,1,1,1,1,0,0},
      {0,0,1,0,0,0,0,0,0,0,0,0},
      {0,0,1,1,1,1,1,2,0,0,0,0},
      {0,0,0,0,0,0,0,0,0,0,0,0}
    };

    auto start_point = Sprite::create("LevelScene/startPoint.png");
    start_point->setPosition(ij_to_xy(0, 4));

    this->addChild(start_point);

    auto carrot = Sprite::create("LevelScene/carrot.png");
    carrot->setPosition(ij_to_xy(4, 7));

    this->addChild(carrot);

    levelPath.push_back({ 0,4,'e' });
    levelPath.push_back({ 0,5,'e' });
    levelPath.push_back({ 0,6,'e' });
    levelPath.push_back({ 0,7,'e' });
    levelPath.push_back({ 0,8,'e' });
    levelPath.push_back({ 0,9,'s' });
    levelPath.push_back({ 1,9,'s' });
    levelPath.push_back({ 2,9,'w' });
    levelPath.push_back({ 2,8,'w' });
    levelPath.push_back({ 2,7,'w' });
    levelPath.push_back({ 2,6,'w' });
    levelPath.push_back({ 2,5,'w' });
    levelPath.push_back({ 2,4,'w' });
    levelPath.push_back({ 2,3,'w' });
    levelPath.push_back({ 2,2,'s' });
    levelPath.push_back({ 3,2,'s' });
    levelPath.push_back({ 4,2,'e' });
    levelPath.push_back({ 4,3,'e' });
    levelPath.push_back({ 4,4,'e' });
    levelPath.push_back({ 4,5,'e' });
    levelPath.push_back({ 4,6,'e' });
    levelPath.push_back({ 4,7,'o' });

    float x = visibleSize.width / 2 + origin.x;
    float y = visibleSize.height / 2 + origin.y;


    auto backButton = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(Level_2::onBackButtonClicked, this));

    backButton->setPosition(Vec2(origin.x + 40, visibleSize.height + origin.y - 40));

    pauseButton = MenuItemImage::create("LevelScene/pauseButton.png", "LevelScene/pauseButton.png",
        CC_CALLBACK_1(Level_2::pauseButtonClicked, this));

    pauseButton->setPosition(Vec2(origin.x + 100, visibleSize.height + origin.y - 40));

    resumeButton = MenuItemImage::create("LevelScene/resumeButton.png", "LevelScene/resumeButton.png",
        CC_CALLBACK_1(Level_2::resumeButtonClicked, this));

    resumeButton->setPosition(Vec2(origin.x + 100, visibleSize.height + origin.y - 40));
    resumeButton->setVisible(false);

    goldLabel = Label::createWithTTF("Gold: " + std::to_string(goldCount), "fonts/arial.ttf", 20);
    goldLabel->setAnchorPoint(Vec2(1, 1));
    goldLabel->setPosition(Vec2(visibleSize.width + origin.x - 100, visibleSize.height + origin.y - 40));
    this->addChild(goldLabel);


    // 创建菜单
    auto menu = Menu::create(backButton, pauseButton, resumeButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);


    return true;
}

void Level_2::onBackButtonClicked(cocos2d::Ref* sender)
{
    // 返回选关界面
    cocos2d::Director::getInstance()->popScene();
}

void Level_2::pauseButtonClicked(cocos2d::Ref* sender)
{
    Director::getInstance()->pause();

    pauseButton->setVisible(false);
    resumeButton->setVisible(true);
}

void Level_2::resumeButtonClicked(cocos2d::Ref* sender)
{
    Director::getInstance()->resume();

    // 切换按钮可见性
    pauseButton->setVisible(true);
    resumeButton->setVisible(false);
}

// 跳转到失败界面的方法
void Level_2::goToFailScene()
{
    // 创建并切换到失败场景
    auto scene = LoseScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
