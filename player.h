#pragma once

#include "compositeentity.h"

class Coordinate;

class Coordinate;

class Player : public CompositeEntity {

public:
    Player(Coordinate* position, std::string name);
    virtual void jump() = 0;

    int getCurrentLive();
    void setCurrentLive(int life);

    // newly added at stage 3
    virtual double getYvelocity() = 0;
    virtual void setYvelocity(double change) = 0;
    virtual void setOffsetYCoordinate(int change) = 0;

private:
    int cur_life;
};

