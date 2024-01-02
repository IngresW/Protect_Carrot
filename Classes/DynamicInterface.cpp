#include "DynamicInterface.h"

DynamicInterface::~DynamicInterface()
{
    CC_SAFE_RELEASE_NULL(_Animation);
}

bool DynamicInterface::init(const int& rId, const std::string& rSCsvFileName)
{
    auto pCsvUtil = CsvUtil::getInstance();
    _Animation = Animation::create();
    _Animation->retain();
    _iAtk = pCsvUtil->getInt(rId, en_Atk, rSCsvFileName);
    _iSpeed = pCsvUtil->getInt(rId, en_Speed, rSCsvFileName);
    return true;
}

void DynamicInterface::createDynamicEntityAnimation(const std::vector<std::string>& animationFiles)
{
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    for (const auto& animationFile : animationFiles)
    {
        auto spriteFrame = spriteFrameCache->getSpriteFrameByName(animationFile);
        if (spriteFrame)
        {
            _Animation->addSpriteFrame(spriteFrame);
        }
        else
        {
            // 处理无效的精灵帧
            // 这里可以添加自定义的错误处理逻辑
        }
    }
    _Animation->setLoops(-1);
}