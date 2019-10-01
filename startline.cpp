#include "startline.h"

#include "coordinate.h"

StartLine::StartLine(Coordinate* position, double width, double height, double velocity, QColor colour, std::string name)
    : CompositeEntity(position, name),
      colour(colour),
      collider(RectCollider(new Coordinate(position->getXCoordinate() - width/2.0, (double)0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(position->getXCoordinate() + width/2.0, position->getYCoordinate(), position->getFrameHeight(), position->getFrameWidth()))),  
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

void StartLine::update(bool paused, double /*time_since_last_frame*/, int direction) {
    if (!paused || (paused && direction == 1)) {
        is_moving = true;

        // Keep collider in sync with position
        this->getPosition()->changeInXCoordinate(direction * velocity);
        collider.getV1()->setXCoordinateToZero(getPosition()->getXCoordinate() - width/2.0);
        collider.getV2()->setXCoordinateToZero(getPosition()->getXCoordinate() + width/2.0);
    }else {
        is_moving = false;
    }
}

void StartLine::render(QPainter &painter) {
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    QBrush brush(colour);
    painter.setBrush(brush);

    if (getPosition() != nullptr) {
        double x = this->getPosition()->getQtRenderingXCoordinate();
        double y = this->getPosition()->getQtRenderingYCoordinate();
        painter.drawRect(x, y, width, height);
    }

    //renderChildren(painter);
}
