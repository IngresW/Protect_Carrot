#ifndef TOWER__BOTTLE
#define TOWER__BOTTLE
#include "TowerBase.h"


class TowerBottle : public TowerBase
{
public:
    static TowerBottle* createTower(const int& rId, const BasicInformation& basicInformation, const TowerInformation& towerInformation);
    virtual bool init(const int& rId, const BasicInformation& basicInformation, const TowerInformation& towerInformation) ;

protected:
    virtual void upGrade() override;
};

#endif // !TOWER__BOTTLE
