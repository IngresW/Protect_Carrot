#ifndef Dynamic__InterFace
#define Dynamic__InterFace

#include "PublicDefine.h"

class DynamicInterface
{
public:

    virtual ~DynamicInterface();

protected:

    virtual void createDynamicEntityAnimation(const std::vector<std::string>& rAnimationFiles);

    virtual bool init(const int& rId, const std::string& rSCsvFileName);
    /**
     *  move and move Action
     */
    virtual void setAction(const float& rDt) = 0;
    /**
     *  Dynamic Entity speed
     */
    CC_SYNTHESIZE_PASS_BY_REF(unsigned int, _iSpeed, ISpeed);
    /**
     *  Bullet' Atk
     */
    CC_SYNTHESIZE_PASS_BY_REF(int, _iAtk, IAtk);

protected:

    Animation* _Animation = nullptr;

};

#endif