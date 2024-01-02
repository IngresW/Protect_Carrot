#include"EntityBase.h"

Entity::~Entity() = default;

bool Entity::init(const int& rId, const BasicInformation basicInformation)
{
    _iId = rId;
    _sFileName = basicInformation._sFileName;
    _bIsDead = false;
    bindSprite(Sprite::createWithSpriteFrameName(_sFileName));
    return true;
}

void Entity::bindSprite(Sprite* pSprite)
{
    if (_sprite)
    {
        _sprite->stopAllActions();
        removeChild(_sprite, true);  // 使用cleanup参数移除子节点，同时释放精灵的内存
        CC_SAFE_RELEASE_NULL(_sprite);
    }
    _sprite = pSprite;
    if (_sprite)
    {
        CC_SAFE_RETAIN(_sprite);
        addChild(_sprite);
    }
}

void Entity::doDead()
{
    _bIsDead = true;
    _sprite->stopAllActions();
}

void Entity::deadAction(const std::string& deadImageFile)
{
    if (!deadImageFile.empty())
    {
        SpriteFrame* deadSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(deadImageFile);
        if (deadSpriteFrame)
        {
            _sprite->setSpriteFrame(deadSpriteFrame);
        }
    }
    // 直接移除精灵
    removeChild(_sprite, true);
}

Rect Entity::getBoundingBox() const
{
    Vec2 tPos = getPosition();
    Size tSize = _sprite->getContentSize();
    return Rect(tPos.x - tSize.width / 2, tPos.y - tSize.height / 2, tSize.width, tSize.height);
}

const Size& Entity::getContentSize() const
{
    return _sprite->getContentSize();
}

Sprite* Entity::getSprite()
{
    return _sprite;
}
