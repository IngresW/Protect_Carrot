#include "LevelScene.h"

USING_NS_CC;

std::vector <MyMonster*> m;  //���ڴ�Ź���

struct pos
{
    int i, j;
};

Scene* LevelScene::createScene()
{
    return LevelScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool LevelScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    m.clear();

    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����½���ɫ���汳���Ͱ�ť
    auto background = cocos2d::Sprite::create("LevelScene/map.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    auto Path = cocos2d::Sprite::create("LevelScene/BG-1.png");
    Path->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 40));
    this->addChild(Path);


    auto start_point = Sprite::create("LevelScene/startPoint.png");
    start_point->setPosition(ij_to_xy(0, 1));

    this->addChild(start_point);

    auto carrot = Sprite::create("LevelScene/carrot.png");
    carrot->setPosition(ij_to_xy(0, 10));

    this->addChild(carrot);


    hp_label = Label::createWithTTF(std::to_string(carrot_hp), "fonts/arial.ttf", 20);
    hp_label->setAnchorPoint(Vec2(0, 0.5));
    hp_label->setPosition(Vec2(ij_to_xy(0, 10).x, ij_to_xy(0, 10).y + 60));

    this->addChild(hp_label);
    

    float x = visibleSize.width / 2 + origin.x;
    float y = visibleSize.height / 2 + origin.y;


    auto backButton = MenuItemImage::create("LoadScene/back_button_normal.png", "LoadScene/back_button_selected.png",
        CC_CALLBACK_1(LevelScene::onBackButtonClicked, this));

    backButton->setPosition(Vec2(origin.x + 40, visibleSize.height + origin.y - 40));

    pauseButton = MenuItemImage::create("LevelScene/pauseButton.png", "LevelScene/pauseButton.png",
        CC_CALLBACK_1(LevelScene::pauseButtonClicked, this));

    pauseButton->setPosition(Vec2(origin.x + 100, visibleSize.height + origin.y - 40));

    resumeButton = MenuItemImage::create("LevelScene/resumeButton.png", "LevelScene/resumeButton.png",
        CC_CALLBACK_1(LevelScene::resumeButtonClicked, this));

    resumeButton->setPosition(Vec2(origin.x + 100, visibleSize.height + origin.y - 40));
    resumeButton->setVisible(false);

    goldLabel = Label::createWithTTF("Gold: " + std::to_string(goldCount), "fonts/arial.ttf", 20);
    goldLabel->setAnchorPoint(Vec2(1, 1));
    goldLabel->setPosition(Vec2(visibleSize.width + origin.x - 100, visibleSize.height + origin.y - 40));
    this->addChild(goldLabel);

    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 12; j++) {
            grid[i][j] = Sprite::create("LevelScene/select.png");
            grid[i][j]->setPosition(ij_to_xy(i, j));
            grid[i][j]->setTag(i * 100 + j);
            grid[i][j]->setVisible(false);
            this->addChild(grid[i][j]);
        }
    }

    // �����˵�
    auto menu = Menu::create(backButton, pauseButton, resumeButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);


    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](Touch* touch, Event* event) {
        if (touch->getLocation().y < visibleSize.height) {
            Vec2 vec = touch->getLocation();
            Vec2 position = xy_to_ij(vec);
            return true;
        }
        return false;
        };

    listener->onTouchEnded = [=](Touch* touch, Event* event) {
        if (touch->getLocation().y < visibleSize.height) {
            Vec2 vec = touch->getLocation();
            Vec2 position = xy_to_ij(vec);

            int row = position.x;
            int col = position.y;

            if (level_1_map[row][col] != 2 && level_1_map[row][col] != 1 && level_1_map[row][col] != -1) {
                Node* node = this->getChildByTag(100 * row + col);
                //Sprite* grid = static_cast<Sprite*>(node);
                if (level_1_map[row][col] == 0) {
                    grid[row][col]->setVisible(true);
                    //build(position, tower);
                }
                else if (level_1_map[row][col] == 3) {
                    //tower_operations(position);
                }
            }
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate();

    Sprite* mon = Sprite::create("Monster/Monsters01.png");
    MyMonster* Monster = static_cast<Monster_Hand*>(mon);
    Monster->setPosition(ij_to_xy(0, 1));


    this->addChild(Monster, 1);

    //Move();
    //ÿ2�����һֻ���� 
    //schedule(CC_SCHEDULE_SELECTOR(LevelScene::updateMonster), 2.0f);

    //10��ˢ�²���
    //schedule(CC_SCHEDULE_SELECTOR(LevelScene::updateWave), 10.0f);


    return true;
}

void LevelScene::onBackButtonClicked(cocos2d::Ref* sender)
{
    // ����ѡ�ؽ���
    cocos2d::Director::getInstance()->popScene();
}

void LevelScene::pauseButtonClicked(cocos2d::Ref* sender)
{
    Director::getInstance()->pause();
    if_pause = 1;
    pauseButton->setVisible(false);
    resumeButton->setVisible(true);
}

void LevelScene::resumeButtonClicked(cocos2d::Ref* sender)
{
    Director::getInstance()->resume();
    if_pause = 0;
    // �л���ť�ɼ���
    pauseButton->setVisible(true);
    resumeButton->setVisible(false);
}

// ��ת��ʧ�ܽ���ķ���
void LevelScene::goToFailScene()
{
    // �������л���ʧ�ܳ���
    auto scene = LoseScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void LevelScene::build(Vec2 position, int tower_available[]) {

    auto touch_layer = Layer::create();
    this->addChild(touch_layer);
    int row = position.x;
    int col = position.y;

    grid[row][col]->setVisible(true);
    //��̨����
    auto sprite_1 = Sprite::create();
    auto sprite_2 = Sprite::create();
    auto sprite_3 = Sprite::create();

   
}

void LevelScene::updateMonster(float dt)
{
    //MonsterPool my_pool;

    //Sprite* mon = my_pool.Create_Monster(Monster_Wave[wave][order]);
    //Monster_Hand* Monster = static_cast<Monster_Hand*>(mon);

    Sprite* mon = Sprite::create("Monster/Monsters01.png");
    MyMonster* Monster = static_cast<Monster_Hand*>(mon);
    Monster->setPosition(ij_to_xy(0, 1));


    this->addChild(Monster,1);
    //Monster->monster_hp = 10;
    //Monster->moveSpeed = 1;
    //Monster->value = 30;
    //Monster->alive = 1;

    Monster->init_path();
    Monster->Move();

    ////��������ֵѪ��
    //auto HpBarBG = Sprite::create("Monster/fight_blood_bg.png");
    //HpBarBG->setPosition(Vec2(getContentSize().width / 2 + 55, getContentSize().height / 2 + 90));
    //HpBarBG->setScale(0.8);
    //addChild(HpBarBG);

    //ProgressTimer* BloodBar = ProgressTimer::create(Sprite::create("Monster/fight_blood_top.png"));
    //BloodBar->setType(ProgressTimer::Type::BAR);
    //BloodBar->setMidpoint(Vec2(0, 0.5));
    //BloodBar->setBarChangeRate(Vec2(1, 0));
    //BloodBar->setScale(0.8);
    //BloodBar->setPosition(Vec2(HpBarBG->getPosition()));
    //BloodBar->setPercentage(100.0f);
    //addChild(BloodBar, 2);

    m.push_back(Monster);

    order = (order + 1) % 5;

    //�����е����һ�������һֻ�����ʱ��,ֹͣ����
    if (wave == 5 && order == 5 - 1) {
        unschedule(CC_SCHEDULE_SELECTOR(LevelScene::updateMonster));
    }
}

void LevelScene::updateWave(float dt)
{

    //������һ
    wave++;
    //if (wave <= 4) {
    //    auto node = getChildByName("WavesLabel");

    //    Label* Wave_Label = static_cast<Label*>(node);

    //    Wave_Label->setString(std::to_string(wave / 10 % 10) + "    " + std::to_string(wave % 10));

    //}
    //else { 

    //}
    //�����е����һ��ʱ��ֹͣ����
    if (wave == 5) {
        unschedule(CC_SCHEDULE_SELECTOR(LevelScene::updateWave));
    }

}

void LevelScene::Move()
{
    path.push_back({ 0,1,'s' });
    path.push_back({ 1,1,'s' });
    path.push_back({ 2,1,'s' });
    path.push_back({ 3,1,'s' });
    path.push_back({ 3,2,'e' });
    path.push_back({ 3,3,'e' });
    path.push_back({ 3,4,'n' });
    path.push_back({ 2,4,'e' });
    path.push_back({ 2,5,'e' });
    path.push_back({ 2,6,'e' });
    path.push_back({ 2,7,'s' });
    path.push_back({ 3,7,'e' });
    path.push_back({ 3,8,'e' });
    path.push_back({ 3,9,'e' });
    path.push_back({ 3,10,'n' });
    path.push_back({ 2,10,'n' });
    path.push_back({ 1,10,'n' });
    path.push_back({ 0,10,'o' });

    if (path.empty())
    {
        // ���ﵽ���յ㣬ִ����ʧ�߼�
        monster->removeFromParent();
        return;
    }

    // ��ȡ��һ��·���ڵ�
    PathNode nextNode = path.front();
    path.erase(path.begin());

    // ����·���ڵ����ù��ﾫ����ƶ�����
    float duration = 0.45f; // �ƶ�ÿ��·����ʱ��
    Vec2 targetPos = ij_to_xy(nextNode.i, nextNode.j);
    MoveTo* moveAction = MoveTo::create(duration, targetPos);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(LevelScene::Move, this));
    Sequence* sequence = Sequence::create(moveAction, callback, nullptr);

    // ִ���ƶ�����
    monster->runAction(sequence);
}