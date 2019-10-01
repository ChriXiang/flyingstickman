#pragma once

#include "entity.h"

#include <string>

class CompositeEntity : public Entity {
public:
    CompositeEntity(Coordinate* position, std::string name);
    ~CompositeEntity() = default;

    void addChild(Entity* e);
    void removeChild(Entity* e);
    Entity* getChild(Entity* e);

    //void setVelocity(int new_velocity);

    void renderChildren(QPainter &painter);
    void updateChildren(bool paused, double deltaTimeMilliseconds, int direction = 1);

};
