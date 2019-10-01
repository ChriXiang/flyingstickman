#ifndef GIANTPLAYER_H
#define GIANTPLAYER_H

#include <vector>
#include <cmath>
#include "player.h"
#include "stickman.h"
#include "config.h"
#include "physicsbody.h"
#include "obstacle.h"
#include "gamestate.h"

class GiantPlayer : public Player {

public:
    GiantPlayer(Coordinate* position, std::string name);
    ~GiantPlayer() override;

    virtual void jump() override;
    void checkGroundCollision();
    void landed();
    Obstacle* checkCollisions(std::vector<Obstacle*> obstacles);

    virtual RectCollider* getCollider() override { return &collider; }

    virtual void onCollision(Entity* other) override;
    virtual void update(bool paused, double time_since_last_frame, int direction = 0) override;
    virtual void render(QPainter &painter) override;

    virtual double getYvelocity() override;
    virtual void setYvelocity(double change) override;
    virtual void setOffsetYCoordinate(int change) override;

private:
    // Coordinate for managing jumping and other movement independently to config positions.
    Coordinate* offset_position;
    PhysicsBody physics_body;
    RectCollider collider;

    double jump_height;
    double gravity;
    int jump_count;
    const int max_jump_count = 1;
    // giant mode can only jump once
    int frame_number;
    int counter;

    int cur_life;
};

#endif // GIANTPLAYER_H
