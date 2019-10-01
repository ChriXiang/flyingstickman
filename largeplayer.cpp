#include "largeplayer.h"

#include "coordinate.h"

// one of the 4 concrete state subclass
LargePlayer::LargePlayer(Coordinate* position, std::string name)
    : Player(position, name),
      offset_position(new Coordinate(0, 0, position->getFrameHeight(), position->getFrameWidth())),
      physics_body(PhysicsBody(offset_position)),
      collider(RectCollider(new Coordinate(0, 0, position->getFrameHeight(), position->getFrameWidth()),
                            new Coordinate(0, 0, position->getFrameHeight(), position->getFrameWidth()))),
      jump_height(250),
      gravity(-9.8*200),
      jump_count(0),
      frame_number(1),
      counter(0) {
    physics_body.setYAcceleration(gravity);
    // tiny mode enable double speed
}

LargePlayer::~LargePlayer() {
    delete offset_position;
}

void LargePlayer::jump() {
    if (jump_count < max_jump_count) {
        jump_count += 1;
        physics_body.setYVelocity(std::sqrt(-2*gravity*jump_height));
    }
}

double LargePlayer::getYvelocity(){
    return physics_body.getYVelocity();
}

void LargePlayer::setOffsetYCoordinate(int change){
    offset_position->setYCoordinateToZero(change);
}

void LargePlayer::setYvelocity(double change){
    physics_body.setYVelocity(change);
}

void LargePlayer::landed() {
    jump_count = 0;
    physics_body.setYVelocity(0);
}

void LargePlayer::checkGroundCollision() {
    if (offset_position->getYCoordinate() <= 0) {
        offset_position->setYCoordinateToZero(0);
        landed();
    }
}

void LargePlayer::onCollision(Entity* /*other*/) {
    //nothing happen for large mode
}

void LargePlayer::update(bool paused, double time_since_last_frame, int direction) {
    // Physics updates
    physics_body.apply(time_since_last_frame/1000.0);

    checkGroundCollision();

    // Keep position coordinate and collider coordinates in sync with the Config
    this->getPosition()->setXCoordinateToZero(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5) + offset_position->getXCoordinate());
    this->getPosition()->setYCoordinateToZero(Config::config()->getStickman()->getHeight()+ offset_position->getYCoordinate());
    this->collider.getV1()->setXCoordinateToZero(this->getPosition()->getXCoordinate());
    this->collider.getV1()->setYCoordinateToZero(this->getPosition()->getYCoordinate());
    this->collider.getV2()->setXCoordinateToZero(this->getPosition()->getXCoordinate() + Config::config()->getStickman()->getWidth());
    this->collider.getV2()->setYCoordinateToZero(this->getPosition()->getYCoordinate() - Config::config()->getStickman()->getHeight());


    //Used to slow down the animation
    if (counter == 2 && direction != 0) {
        frame_number++;
        counter = 0;
    }

    //Once the frame is the last, reset
    if (frame_number % 10 == 0 && direction != 0) {
        frame_number -= 9;
    }

    //Only increment the counter if its not paused
    if (!paused && direction != 0) {
        counter++;
    }

    //Used to change direction
    if (direction == 1 && frame_number > 10){
        frame_number -= 10;
    }
    else if (direction == -1 && frame_number < 10){
        frame_number += 10;
    }
}

void LargePlayer::render(QPainter &painter) {
    QPixmap sprite = Config::config()->getStickman()->getPixmap(frame_number);
    painter.drawPixmap(this->getPosition()->getQtRenderingXCoordinate(),
                       this->getPosition()->getQtRenderingYCoordinate(),
                       Config::config()->getStickman()->getWidth(),
                       Config::config()->getStickman()->getHeight(),
                       sprite);
}
