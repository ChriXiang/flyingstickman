#pragma once

#include <vector>
#include <QPainter>

#include "configstage3.h"


class Coordinate;
class RectCollider;

class Entity {

public:
    Entity();
    Entity(Coordinate* position, std::string name);
    virtual ~Entity();

    Coordinate* getPosition();
    void setPosition(Coordinate* position);

    std::string getName() {return name;}
    std::vector<Entity*>& getChildren() { return children; }

    // Override this if your entity has a collider.
    virtual RectCollider* getCollider() { return nullptr; }
    virtual void onCollision(Entity* /*other */) {}

    virtual void update(bool paused, double time_since_last_frame, int direction = 1) = 0;

    virtual void render(QPainter &painter) = 0;

    void clearChildren();

protected:
    std::vector<Entity*> children;

private:
    Coordinate* position;
    std::string name;
};

