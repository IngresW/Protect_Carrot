#ifndef MONSTER__BASE
#define MONSTER__BASE
#include "EntityAffected.h"

class MonsterBase : public EntityAffected
{
public:
    static MonsterBase* create(const int& rIId, const std::vector<std::string>& basicInformation, const std::vector<std::string>& affectedInformation);

    void setMaxSpeed(const float& rSpeed);

protected:
    virtual void deadAction(const std::string& rSDeadImageFile = "") override;
    virtual bool init(const int& rId, const std::vector<std::string>& basicInformation, const std::vector<std::string>& affectedInformation);
    virtual void move();

private:
    float _fMaxSpeed;
    Sprite* monster;
};



#endif // !MONSTER__BASE
