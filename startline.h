#ifndef STARTLINE_H
#define STARTLINE_H

#include <QPainter>
#include <QColor>
#include "compositeentity.h"
#include "rectcollider.h"

class StartLine : public CompositeEntity{
public:
    StartLine(Coordinate* position, double width, double height, double velocity, QColor colour, std::string name);
    ~StartLine() override = default;

    virtual RectCollider* getCollider() override { return &collider; }

    virtual void update(bool paused, double, int direction = 0) override;
    virtual void render(QPainter &painter) override;

private:
    QColor colour;
    RectCollider collider;
    double width;
    double height;
    double velocity;

    bool is_moving;
    //double loop_after;
};

#endif // STARTLINE_H
