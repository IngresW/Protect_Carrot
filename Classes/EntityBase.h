#ifndef ENTITY__BASE
#define ENTITY__BASE

#include "PublicDefine.h"
class EntityAffected;

class Entity:public Node{
public:
    static unsigned long ID;
	virtual ~Entity();
	virtual bool init(const int&rID,const std::string &rSCsvFileName);
    virtual void bindSprite(Sprite* pSprite);
    virtual void doDead();
    virtual Rect getBoundingBox()const;
    unsigned int getmID()const;
    virtual const Size& getContentSize()const;
    virtual Sprite* getSprite();
protected:
	virtual void initProperty(const int& rID, const std::string& rSCsvFileName);
    virtual void deadAction(const std::string& rSDeadImageFile = "");

    CC_SYNTHESIZE_PASS_BY_REF(int, _iID, IID);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sName, SName);
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sModelName, SModelName);
    CC_SYNTHESIZE_PASS_BY_REF(int, _iValue, IValue);
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsDead, IsDead);
    CC_SYNTHESIZE_PASS_BY_REF(int, _IAnimationFrameCount, AnimationFrameCount);
    CC_SYNTHESIZE_PASS_BY_REF(int, _iLevel, ILevel);

private:
	Sprite* PSprite = nullptr;
    unsigned long _myID;
};

#endif 