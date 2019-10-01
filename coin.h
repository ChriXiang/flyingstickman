#ifndef COIN_H
#define COIN_H

#include "compositeentity.h"
#include "rectcollider.h"


class Coin : public CompositeEntity {

public:
    Coin(Coordinate* position, double width, double height, double velocity,std::string name);
    ~Coin() override = default;

    virtual RectCollider* getCollider() override { return &collider; }

    virtual void update(bool paused, double, int direction = 0) override;
    virtual void render(QPainter &painter) override;

    bool getTaken();
    void setTaken(bool change);

    double getDistance();
    void setDistance(double change);

    bool isMoving() {return is_moving; }

    void setVelocity(int new_velocity);

private:

    RectCollider collider;
    double width;
    double height;
    double velocity;
    double dist_travelled;
    bool is_moving;

    bool taken;
};

#endif // COIN_H
