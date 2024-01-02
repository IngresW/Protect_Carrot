#ifndef PUBLIC__DEFINE
#define PUBLIC__DEFINE

#include "cocos2d.h"
using namespace cocos2d;

struct PathNode
{
    int i, j;
    char dir;
};


class EntityAffected;
class TowerBase;
class BulletBase;
class MonsterBase;

enum CsvPublicProperty
{
    en_Name = 1,
    en_ModelName,
    en_Value,
    en_AnimationCount,
    en_Level
};

enum CsvTowerProperty {
    en_Range = 6,
    en_Space,
    en_BulletId,
    en_UpGradeCost,
    en_TowerBase,
    en_IsRotation,
    en_CreateCost
};

enum AtkState
{
    en_Normal = 1,
    en_Slow = en_Normal << 1,
    en_Stop = en_Normal << 2,
    en_Poison = en_Normal << 3,
};

enum CsvAffectedProperty
{
    en_Hp = 6,
    en_Speed,
    en_Atk,
};

struct AtkProperty
{
    int _enAtkState = 0;
    int _iDuration = 0;
    int _iAtk = 0;
    int _iButtltType = 0;
};

enum BulletType
{
    en_NormalBullet = 1,
    en_NoDisspper,
    en_GunBullet,
    en_StarBullet
};

enum CsvBulletProperty
{
    en_AtkState = 6,
    en_Duration = 9,
    en_BulletType,
    en_DeadActCount
};

enum MonsterType
{
    en_Land_Pink = 1,
    en_Land_Star,
    en_Land_Nima,
    en_Land_Boss_Star
};

#define CREATE_INSTANCE_FUNC(__CLASS__) \
private:\
    static __CLASS__ *_gInstance;\
public:\
static __CLASS__* getInstance()\
{\
    if(!_gInstance)\
    {\
        _gInstance = new __CLASS__();\
        if(_gInstance && _gInstance->init())\
        {\
            _gInstance->autorelease();\
            _gInstance->retain();\
        }\
        else\
        {\
            CC_SAFE_DELETE(_gInstance);\
        }\
    }\
    return _gInstance;\
}

#define DESTROY_INSTANCE_FUNC()\
static void destroyInstance()\
{\
    CC_SAFE_RELEASE_NULL(_gInstance);\
}

#define NOTIFY cocos2d::NotificationCenter::getInstance()

#endif
