#ifndef HP
#define HP
#include "PublicDefine.h"
#include "EntityAffected.h"
class EntityAffected;

class Hp : public Node 
{
public:
    static Hp* create(EntityAffected* pEntityAffected);

    void setHp(const int& rIHp);
    const Size& getContentSize() const;

private:
    explicit Hp(EntityAffected* pEntityAffected);
    ~Hp() override;

    bool init();

    ProgressTimer* _Hp = nullptr;
    int _iHpMax = 0;
    EntityAffected* _EntityAffected = nullptr;
};
#endif
