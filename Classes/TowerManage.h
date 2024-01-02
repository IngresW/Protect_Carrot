#ifndef MONEY__MANAGE
#define MONEY__MANAGE

#include "PublicDefine.h"

class Entity;

class TowerManager : public cocos2d::Ref
{
public:
    using TowerVec = cocos2d::Vector<TowerBase*>;

    static TowerManager* getInstance();
    static void destroyInstance();
    virtual bool init();

    TowerVec& getTowerVec();
    void setFuncAddTowerLayer(const std::function<void(Entity*)>& funcAddEntityLayer);
    void clearManager();
    void setFuncCheckMoney(const std::function<int()>& funcCheckMoney);
    int getMoney();

protected:
    friend class TowerBase;
    void addTower(TowerBase* pTower);
    void registerTowerDeadEvent();
    void removeTowerFromManager(Ref* pSender);

    TowerManager();
    virtual ~TowerManager();
    TowerManager(const TowerManager&) = delete;
    TowerManager& operator=(const TowerManager&) = delete;

private:
    static TowerManager* _instance;
    TowerVec* _pTowerVec;
    std::function<void(Entity*)> _funcAddTowerToLayer;
    std::function<int()> _funcCheckMoney;
};

#endif