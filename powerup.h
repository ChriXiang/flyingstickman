#ifndef POWERUP_H
#define POWERUP_H


#include "compositeentity.h"
#include "rectcollider.h"


class PowerUp : public CompositeEntity {

public:
    PowerUp(Coordinate* position, double width, double height, double velocity, std::string sprite_path, std::string name);
    virtual ~PowerUp() override = default;

    virtual RectCollider* getCollider() override { return &collider; }

    virtual void update(bool paused, double time_since_last_frame, int direction = 0) override;
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
    double yvelocity;
    double dist_travelled;
    bool is_moving;

    QString sprite_path;

    bool taken;
};

#endif // POWERUP_H
