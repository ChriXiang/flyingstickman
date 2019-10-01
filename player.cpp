#include "player.h"

// the state of state design pattern
Player::Player(Coordinate* position, std::string name)
    : CompositeEntity(position, name) {}

int Player::getCurrentLive(){
    return cur_life;
}
void Player::setCurrentLive(int life){
    cur_life = life;
}

