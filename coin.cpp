#include "coin.h"

#include "coordinate.h"


// collid coin, score + 1
Coin::Coin(Coordinate* position, double width, double height, double velocity, std::string name)
    : CompositeEntity(position, name),
      collider(RectCollider(new Coordinate(position->getXCoordinate() - width/2.0, position->getYCoordinate() - height/2.0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width/2.0, position->getYCoordinate() + height/2.0, position->getFrameHeight(), position->getFrameWidth()))),
      velocity(velocity),
      dist_travelled(0),
      is_moving(true),
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

bool Coin::getTaken(){
    return taken;
}
void Coin::setTaken(bool change){
    taken = change;
}
double Coin::getDistance(){
    return dist_travelled;
}
void Coin::setDistance(double change){
    dist_travelled = change;
}

void Coin::update(bool paused, double /*time_since_last_frame*/, int direction) {

    if (!paused) {
        is_moving = true;

        // Keep collider in sync with position
        this->getPosition()->changeInXCoordinate(direction * velocity);
        collider.getV1()->setXCoordinateToZero(getPosition()->getXCoordinate() - width/2.0);
        collider.getV1()->setYCoordinateToZero(getPosition()->getYCoordinate() - height/2.0);
        collider.getV2()->setXCoordinateToZero(getPosition()->getXCoordinate() + width/2.0);
        collider.getV2()->setYCoordinateToZero(getPosition()->getYCoordinate() + height/2.0);

        //updateChildren(true, time_since_last_frame);

        dist_travelled += direction*velocity;
    } else {
        is_moving = false;
    }
}

void Coin::setVelocity(int new_velocity){
    velocity = new_velocity;
}

void Coin::render(QPainter &painter) {
    if (!getTaken()){
        QPixmap sprite(QString(":/img/coin.png"));
        painter.drawPixmap(this->getPosition()->getQtRenderingXCoordinate(),
                           this->getPosition()->getQtRenderingYCoordinate(),
                           30,
                           30,
                           sprite);
    }
}

