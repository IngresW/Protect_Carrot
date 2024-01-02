#ifndef ENTITY__BASE
#define ENTITY__BASE

#include "PublicDefine.h"

class Entity : public Node {
public:
    virtual ~Entity();
    virtual bool init(const int& rId, const BasicInformation& basicInformation);
    virtual void bindSprite(Sprite* pSprite);
    virtual void doDead();
    virtual Rect getBoundingBox() const;
    virtual const Size& getContentSize() const;
    virtual Sprite* getSprite();
    int _iId;                // 实体ID
    std::string _sFileName;  // 精灵文件名
    bool _bIsDead;           // 是否已死亡
protected:
    virtual void deadAction(const std::string& deadImageFile = "");

    

private:
    Sprite* _sprite = nullptr;  // 精灵对象
};




#endif
