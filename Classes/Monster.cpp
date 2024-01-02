#include "Monster.h"
#include "LevelScene.h"

MonsterBase* MonsterBase::create(const int& rIId, const std::vector<std::string>& basicInformation, const std::vector<std::string>& affectedInformation)
{
    MonsterBase* pMonster = new MonsterBase();
    if (pMonster && pMonster->init(rIId,basicInformation,affectedInformation))
    {
        pMonster->autorelease();
        return pMonster;
    }
    else
    {
        delete pMonster;
        return nullptr;
    }
}

void MonsterBase::setMaxSpeed(const float& rSpeed)
{
    _fMaxSpeed = rSpeed;
}

void MonsterBase::deadAction(const std::string& rSDeadImageFile)
{
    EntityAffected::deadAction(rSDeadImageFile);
}



bool MonsterBase::init(const int& rId, const std::vector<std::string>& basicInformation, const std::vector<std::string>& affectedInformation)
{
    if (!EntityAffected::init(rId,basicInformation,affectedInformation))
    {
        return false;
    }

    monster = Sprite::create("LevelScene/Monsters01.png");
    monster->setPosition(ij_to_xy(0, 1));
    this->addChild(monster, 1);
    move();

    return true;
}


void MonsterBase::move()
{
    if (levelPath.empty())
    {
        // 怪物到达终点，执行消失逻辑
        monster->removeFromParent();
        return;
    }

    // 获取下一个路径节点
    PathNode nextNode = levelPath.front();
    levelPath.erase(levelPath.begin());

    // 根据路径节点设置怪物精灵的移动动作
    float duration = 0.45f; // 移动每格路径的时间
    Vec2 targetPos = ij_to_xy(nextNode.i, nextNode.j);
    MoveTo* moveAction = MoveTo::create(duration, targetPos);
    CallFunc* callback = CallFunc::create(CC_CALLBACK_0(MonsterBase::move, this));
    Sequence* sequence = Sequence::create(moveAction, callback, nullptr);

    // 执行移动动作
    monster->runAction(sequence);
}
