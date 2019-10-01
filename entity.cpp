#include "entity.h"

#include "coordinate.h"

Entity::Entity()
    : children(std::vector<Entity*>()),
      position(nullptr) {}

Entity::Entity(Coordinate* position, std::string name)
    : children(std::vector<Entity*>()),
      position(position),
      name(name) {}

Entity::~Entity() {
    delete position;
}

Coordinate* Entity::getPosition() {
    return position;
}

void Entity::setPosition(Coordinate* position) {
    this->position = position;
}

void Entity::clearChildren(){
    //used to count the number of coins
    int counter = 0;
    for (auto* obstacle : children) {
        if (obstacle->getName().substr(0,4) == "coin" || obstacle->getName().substr(0,7) == "powerup"){
            counter++;
            continue;
        }
        delete obstacle;
    }
    children.erase(children.begin() + counter,children.end());
}
