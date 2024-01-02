#include "TowerBase.h"
#include "Monster.h"
#include "Bullet.h"

bool TowerBase::init(const int& rId, const BasicInformation basicInformation, const TowerInformation towerInformation)
{
	Entity::init(rId, basicInformation);
	if (_pTowerSprite) removeChild(_pTowerSprite);
	CC_SAFE_RELEASE_NULL(_pTowerSprite);

	_iBulletId = towerInformation._BBullet;
	_iAtkRange = towerInformation._dAtkRange;
	_iCreateCost = towerInformation._iCreateCost;
	_iUpgradeCost = towerInformation._iUpgradeCost;
	_iValue= towerInformation._iValue;
	_iTowerId = towerInformation._towerId;
	_iGrade = 0;
	_bAtkTarget = false;

	_pTowerSprite = Sprite::create("tower.png");
	if (!_pTowerSprite) {
		return false;
	}
	addChild(_pTowerSprite);
	schedule(schedule_selector(TowerBase::checkAtkTarget), 0.1f);
	schedule(schedule_selector(TowerBase::fire), _iBulletId._iAtkSpeed);
	return 0;
}

void TowerBase::upGrade()
{
	int upGradeMoney = -_iUpgradeCost;
	//金钱减少操作

	auto upGradeCounts = this->_iGrade;
	_iAtkRange = _iAtkRange + (_iTowerId * 20 * _iValue );
	_iBulletId._iAtkSpeed = _iBulletId._iAtkSpeed * 0.85;
	_iBulletId._iAtk = _iBulletId._iAtk * 1.4;
	this->_iUpgradeCost = upGradeCounts;
}

bool TowerBase::isInAtkRange(const Vec2& rPos)
{
	auto distance = getPosition().distance(rPos);
	auto range = _iAtkRange + 30; // 添加30像素的额外范围，用于显示攻击范围图案

	// 创建并绘制攻击范围圆形
	auto drawNode = DrawNode::create();
	drawNode->drawSolidCircle(getPosition(), range, 0, 30, Color4F(1.0f, 0.0f, 0.0f, 0.3f)); // 使用红色半透明颜色绘制圆形
	addChild(drawNode);
	return distance < _iAtkRange;
}

int TowerBase::getTowerGradeCost() {
	return _iUpgradeCost;
}

void TowerBase::checkAtkTarget(float dt)
{
	// 过滤掉已死亡的怪物
	MonsterVec.erase(
		std::remove_if(MonsterVec.begin(), MonsterVec.end(), [](MonsterBase* monster) {
			return monster->_bIsDead;
			}),
		MonsterVec.end()
	);

	// 检查怪物是否在攻击范围内
	std::vector<MonsterBase*> targetsInRange;
	for (MonsterBase* monster : MonsterVec)
	{
		if (isInAtkRange(monster->getPosition()))
		{
			targetsInRange.push_back(monster);
		}
	}

	// 根据怪物与炮塔的距离进行排序（近到远）
	std::sort(targetsInRange.begin(), targetsInRange.end(), [this](MonsterBase* a, MonsterBase* b) {
		return getPosition().distance(a->getPosition()) < getPosition().distance(b->getPosition());
		});

	// 更新攻击目标
	if (!targetsInRange.empty())
	{
		_pAtkTarget = targetsInRange.front();
		_bAtkTarget = true;
	}
	else
	{
		_pAtkTarget = nullptr;
		_bAtkTarget = false;
	}
}

void TowerBase::fire(float dt) {
	if (!_pAtkTarget || _pAtkTarget->_bIsDead) return;

	auto createBulletCF = CallFunc::create([=]() 
		{
		if (!_pAtkTarget) return;
		Bullet::createBullet(_iBulletId, this, _pAtkTarget);
		});

	this->runAction(Sequence::create(DelayTime::create(0.15), createBulletCF, NULL));
}
