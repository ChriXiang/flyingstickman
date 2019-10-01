#ifndef SMALLPOWERUP_H
#define SMALLPOWERUP_H

#include "powerup.h"


class SmallPowerUp : public PowerUp{
public:
    SmallPowerUp(Coordinate* position, double width, double height, double velocity,std::string name);
    ~SmallPowerUp() override = default;
};

#endif // SMALLPOWERUP_H
