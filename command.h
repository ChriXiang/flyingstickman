#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <sstream>
#include "player.h"
#include "background.h"
#include "entity.h"
#include "emptyentity.h"
#include "coordinate.h"
#include "obstacle.h"
#include "finishline.h"
#include "coin.h"


class Command{
public:
    Command();
    virtual int update(bool paused, int direction, int player_colliding, int level) = 0;

    void setPlayer(Player* player);
    Player* getPlayer();

    void setEntity(Entity* entity);
    Entity* getEntity();

    void setBackground(Background *background);
    Background* getBackground();

    void resetEntity(int level, bool new_level);

protected:
    Player* player;
    Background* background;
    Entity* root_entity;
private:
    void coinGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width);
    void createFinishline(EmptyEntity *root, double start_x, unsigned int world_height, unsigned int world_width);
    void createObstacles(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width);
};

#endif // COMMAND_H
