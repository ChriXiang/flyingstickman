#include "normalupdatecommand.h"

NormalUpdateCommand::NormalUpdateCommand()
    : Command()
{}

//void NormalUpdateCommand::createFinishline(EmptyEntity *root, double start_x, unsigned int world_height, unsigned int world_width){
//    std::string name = "finishline";
//    double offset = 10;
//    Coordinate* sl_pos = new Coordinate(start_x,(double)100, world_height, world_width);
//    FinishLine* sl = new FinishLine(sl_pos, 100, (double)100, -Config::config()->getStickman()->getVelocity(), QColor(Qt::green), name);
//    root->addChild(sl);
//}

//void NormalUpdateCommand::createObstacles(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width){
//    // Calculate when to loop the obstacles
//    double loop = world_width;
//    for (auto* obstacleConfig : obstacle_data) {
//        loop += obstacleConfig->offset_x;
//    }

//    double previous_x = world_width;
//    int count = 0;
//    for (auto* obstacleConfig : obstacle_data) {
//        previous_x = previous_x + obstacleConfig->offset_x;
//        std::stringstream name;
//        name << "obstacle_" << count;
//        Coordinate* obs_pos = new Coordinate(previous_x, obstacleConfig->position_y, world_height, world_width);
//        Obstacle* obs = new Obstacle(obs_pos, obstacleConfig->width, obstacleConfig->height,
//                -Config::config()->getStickman()->getVelocity(), loop,
//                QColor(obstacleConfig->colour_red, obstacleConfig->colour_green, obstacleConfig->colour_blue), name.str());
//        root->addChild(obs);
//        count++;
//    }
//    double gap = 50.0;
//    background->setFinishpoint(-(previous_x + gap));
//    //create finishline use the previous x offset
//    createFinishline(root, -background->getFinishpoint() + Config::config()->getWorldWidth() - 150.0,world_height,world_width);
//}

//void NormalUpdateCommand::resetEntity(int level){
//    getEntity()->clearChildren();
//    std::string name = getEntity()->getName();
//    ConfigStage3 config(*Config::config());
//    std::vector<ObstacleConfig*> obstacle_data;
//    obstacle_data = config.getLevelObstacleData(level);
//    createObstacles(dynamic_cast<EmptyEntity*>(getEntity()), obstacle_data, config.getWorldHeight(),config.getWorldWidth());
//}

int NormalUpdateCommand::update(bool paused, int direction, int player_colliding, int level){
    double deltaTimeMilliseconds = 32; // Comes from hard coded timer interval value in Stage1Game.

    if (player->getPosition()->getXCoordinate() >= root_entity->getChildren()[root_entity->getChildren().size()-1]->getPosition()->getXCoordinate()){
        if (level < 3){
            //new level
            player->getPosition()->setXCoordinateToZero(0);
            Config::config()->getStickman()->changeXPosition(Config::config()->getWorldWidth()/2);
            background->resetBackground();
            resetEntity(level + 1, true);
            //increment level
            return 1;
        }
        else{
            //you win!
            return 2;
        }

    }

    if (player_colliding == 1 && player->getCurrentLive() > 1){
        player->setCurrentLive(player->getCurrentLive() - 1);
        player->getPosition()->setXCoordinateToZero(0);
        player->getPosition()->setYCoordinateToZero(0);
        background->resetBackground();
        //restart level
        resetEntity(level, false);
    }
    else if (player_colliding == 1 && player->getCurrentLive() == 1){
        //gameover
    }
    else{
        //normal game
        root_entity->update(paused, deltaTimeMilliseconds, direction);
    }

    if (player != nullptr) {
        player->update(paused, deltaTimeMilliseconds, direction);
    }
    // printf("b: %f\n",background->getCoordinate().getXCoordinate());
    // nothing happen
    return 0;
}
