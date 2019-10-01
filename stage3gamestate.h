#ifndef STAGE3GAMESTATE_H
#define STAGE3GAMESTATE_H

#include <iostream>
#include <sstream>
#include <map>

#include "gamestate.h"
#include "config.h"
#include "windialog.h"
#include "lossdialog.h"
#include "tinyplayer.h"
#include "largeplayer.h"
#include "giantplayer.h"
#include "stickmanplayer.h"

#include "obstacle.h"
#include "finishline.h"
#include "coin.h"
#include "entity.h"
#include "emptyentity.h"
#include "powerup.h"

class Stage3GameState : public GameState {
public:
    Stage3GameState();
    ~Stage3GameState();

    virtual void update(bool paused, int direction = 1) override;

    int getLevel();
    void setLevel(int change);

    int getScore();
    void setScore(int change);

    Player* getNormalPlayer();
    Player* getTinyPlayer();
    Player* getLargePlayer();
    Player* getGiantPlayer();
    Player* getCurrentPlayer();

    void resetEntity(int level, bool new_level);

    Stickman* getStickman();
    void setStickman(Stickman* stickman);


private:
    void winDialog(int score);
    void lossDialog(int score);

    int level;
    int score;

    Player* normal_player;
    Player* tiny_player;
    Player* large_player;
    Player* giant_player;

    Stickman* stickman;

    Player* current_player;

    void createPowerUp(EmptyEntity *root, double x_position, std::string name, unsigned int world_height, unsigned int world_width);
    void powerUpGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width);
    void coinGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width);
    void createFinishline(EmptyEntity *root, double start_x, unsigned int world_height, unsigned int world_width);
    void createObstacles(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width);
};

#endif // STAGE3GAMESTATE_H
