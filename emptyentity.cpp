#include "emptyentity.h"

EmptyEntity::EmptyEntity(Coordinate* position, std::string name)
    : CompositeEntity(position, name){}


void EmptyEntity::update(bool paused, double time_since_last_frame, int direction) {
    //printf("po: %d\n",paused);
    this->updateChildren(paused, time_since_last_frame, direction);
}

void EmptyEntity::render(QPainter &painter) {
    this->renderChildren(painter);
}

