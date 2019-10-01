#include "powerup.h"

#include "coordinate.h"

PowerUp::PowerUp(Coordinate* position, double width, double height, double velocity, std::string sprite_path, std::string name)
    : CompositeEntity(position, name),
      collider(RectCollider(new Coordinate(position->getXCoordinate() - width/2.0, position->getYCoordinate() - height/2.0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width/2.0, position->getYCoordinate() + height/2.0, position->getFrameHeight(), position->getFrameWidth()))),
      velocity(velocity),
      yvelocity(2),
      dist_travelled(0),
      is_moving(true),
      sprite_path(QString::fromStdString(sprite_path)),
      taken(false){

    if (width > 0) {
        this->width = width;
    } else {
        this->width = 1;
    }

    if (height > 0) {
        this->height = height;
    } else {
        this->height = 1;
    }
}

bool PowerUp::getTaken(){
    return taken;
}
void PowerUp::setTaken(bool change){
    taken = change;
}
double PowerUp::getDistance(){
    return dist_travelled;
}
void PowerUp::setDistance(double change){
    dist_travelled = change;
}

void PowerUp::update(bool paused, double /*time_since_last_frame*/, int direction) {

    if (!paused) {
        is_moving = true;

        // Keep collider in sync with position
        this->getPosition()->changeInXCoordinate(direction * velocity);
        if (this->getPosition()->getYCoordinate() > 30.0){
            this->getPosition()->changeInYCoordinate(-yvelocity);
        }
        collider.getV1()->setXCoordinateToZero(getPosition()->getXCoordinate() - width/2.0);
        collider.getV1()->setYCoordinateToZero(getPosition()->getYCoordinate() - height/2.0);
        collider.getV2()->setXCoordinateToZero(getPosition()->getXCoordinate() + width/2.0);
        collider.getV2()->setYCoordinateToZero(getPosition()->getYCoordinate() + height/2.0);

        dist_travelled += direction*velocity;
    } else {
        is_moving = false;
    }
}

void PowerUp::setVelocity(int new_velocity){
    velocity = new_velocity;
}

void PowerUp::render(QPainter &painter) {
    if (!getTaken()){
        QPixmap sprite(sprite_path);
        painter.drawPixmap(this->getPosition()->getQtRenderingXCoordinate(),
                           this->getPosition()->getQtRenderingYCoordinate(),
                           30,
                           30,
                           sprite);
    }
}
