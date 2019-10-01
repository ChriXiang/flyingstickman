#ifndef FINISHLINE_H
#define FINISHLINE_H

#include <QPainter>
#include <QColor>
#include "compositeentity.h"
#include "rectcollider.h"

class FinishLine : public CompositeEntity{
public:
    FinishLine(Coordinate* position, double width, double height, double velocity, QColor colour, std::string name);
    ~FinishLine() override = default;

    virtual void update(bool paused, double, int direction = 0) override;
    virtual void render(QPainter &painter) override;

    void setVelocity(int new_velocity);

private:
    QColor colour;
    double width;
    double height;
    double velocity;

    bool is_moving;
};

#endif // FINISHLINE_H
