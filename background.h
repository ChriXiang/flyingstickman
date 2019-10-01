#pragma once

#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QDialog>
#include <QMediaPlayer>

#include "coordinate.h"

class Background {

public:

    Background(Coordinate main_coordinate);
    ~Background() = default;

    //Render the background depending on if it is in a paused state or not
    void render(QPainter &painter, bool paused, int direction = 1);
    void resetBackground();

    //Getter functions
    Coordinate getCoordinate() { return main_coordinate; }
    QPixmap getFirst() { return first; }
    QPixmap getSecond() { return second; }
    QPixmap getThird() { return third; }

    // newly added at stage 3, for setting the end point of the level
    double getFinishpoint();
    void setFinishpoint(double change);

private:
    Coordinate main_coordinate;

    Coordinate first_coordinate;
    Coordinate second_coordinate;
    Coordinate third_coordinate;

    double finish_point;

    QPixmap first;
    QPixmap second;
    QPixmap third;
};



