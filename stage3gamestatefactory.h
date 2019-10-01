#ifndef STAGE3GAMESTATEFACTORY_H
#define STAGE3GAMESTATEFACTORY_H

#include <vector>
#include <sstream>

#include "gamestatefactory.h"
#include "stage3game.h"
#include "stickmanplayer.h"
#include "obstacle.h"
#include "gamestate.h"
#include "stage3gamestate.h"
#include "configstage3.h"
#include "emptyentity.h"
#include "normalupdatecommand.h"
#include "hugeupdatecommand.h"
#include "startline.h"
#include "finishline.h"
#include "coin.h"
#include "powerup.h"

class Stage3GameStateFactory : public GameStateFactory {
public:
    Stage3GameStateFactory() = default;
    ~Stage3GameStateFactory() = default;
    virtual Stage3GameState *createGameState() override;
private:
    void createPowerUp(EmptyEntity *root, double x_position, std::string name, unsigned int world_height, unsigned int world_width);
    void powerUpGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width);
    void coinGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width);
    void createFinishline(EmptyEntity *root, double start_x, unsigned int world_height, unsigned int world_width);
    void createObstacles(EmptyEntity* root, std::vector<ObstacleConfig*> obstacle_data, Background* bg, unsigned int world_height, unsigned int world_width);
};

#endif // STAGE3GAMESTATEFACTORY_H
