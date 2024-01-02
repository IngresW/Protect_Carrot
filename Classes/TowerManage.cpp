#include "TowerBase.h"
#include "TowerManage.h"

TowerManager* TowerManager::_instance = nullptr;

TowerManager* TowerManager::getInstance()
{
    if (!_instance)
    {
        _instance = new TowerManager();
        _instance->init();
    }
    return _instance;
}

void TowerManager::destroyInstance()
{
    CC_SAFE_DELETE(_instance);
}

TowerManager::TowerManager()
    : _pTowerVec(nullptr)
{
}

TowerManager::~TowerManager()
{
    CC_SAFE_DELETE(_pTowerVec);
}

bool TowerManager::init()
{
    _pTowerVec = new TowerVec();
    registerTowerDeadEvent();
    return true;
}

TowerManager::TowerVec& TowerManager::getTowerVec()
{
    return *_pTowerVec;
}

void TowerManager::addTower(TowerBase* pTower)
{
    if (_pTowerVec)
        _pTowerVec->pushBack(pTower);
    if (_funcAddTowerToLayer)
        _funcAddTowerToLayer(pTower);
}

void TowerManager::setFuncAddTowerLayer(const std::function<void(Entity*)>& funcAddEntityLayer)
{
    _funcAddTowerToLayer = funcAddEntityLayer;
}

void TowerManager::registerTowerDeadEvent()
{
    cocos2d::NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TowerManager::removeTowerFromManager), "TowerDead", nullptr);
}

void TowerManager::removeTowerFromManager(Ref* pTower)
{
    if (_pTowerVec && _pTowerVec->size() > 0)
    {
        _pTowerVec->eraseObject(reinterpret_cast<TowerBase*>(pTower));
    }
}

void TowerManager::clearManager()
{
    if (_pTowerVec)
    {
        _pTowerVec->clear();
    }
}

int TowerManager::getMoney()
{
    if (_funcCheckMoney)
    {
        return _funcCheckMoney();
    }
    return 0;
}

void TowerManager::setFuncCheckMoney(const std::function<int()>& funcCheckMoney)
{
    _funcCheckMoney = funcCheckMoney;
}