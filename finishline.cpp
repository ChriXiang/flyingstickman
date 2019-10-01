#include "finishline.h"

#include "coordinate.h"

FinishLine::FinishLine(Coordinate* position, double width, double height, double velocity, QColor colour, std::string name)
    : CompositeEntity(position, name),
      colour(colour),
      width(width),
      height(height),
      velocity(velocity),
      is_moving(true){
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

void FinishLine::update(bool paused, double /*time_since_last_frame*/, int direction) {
    if (!paused) {
        is_moving = true;
        // Keep collider in sync with position
        this->getPosition()->changeInXCoordinate(direction * velocity);
    }else {
        is_moving = false;
    }
}

void FinishLine::render(QPainter &painter) {
    QPixmap sprite(QString(":/img/flag.png"));
    painter.drawPixmap(this->getPosition()->getQtRenderingXCoordinate(),
                       this->getPosition()->getQtRenderingYCoordinate(),
                       100,
                       100,
                       sprite);
}
void FinishLine::setVelocity(int new_velocity){
    velocity = new_velocity;
}
