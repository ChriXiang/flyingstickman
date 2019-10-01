#include "command.h"

Command::Command(){}

void Command::setPlayer(Player* player){
    this->player = player;
}
Player* Command::getPlayer(){
    return this->player;
}

void Command::setEntity(Entity* entity){
    root_entity = entity;
}
Entity* Command::getEntity(){
    return root_entity;
}

void Command::setBackground(Background* background){
    this->background = background;
}
Background* Command::getBackground(){
    return background;
}

void Command::coinGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width){
    double previous_x = world_width;
    double previous_w = 0.0;
    double coin_size = 30.0;
    double gap = 40.0;
    int count = 0;
    // the boundary before and after every obstacle
    double boundary = 20.0;

    for (auto* obstacleConfig : obstacle_data){

        for (double i = boundary + previous_w/2.0; i + coin_size <= obstacleConfig->offset_x - obstacleConfig->width/2.0; i += (gap + coin_size)){
            //if (i + coin_size > obstacleConfig->offset_x - boundary) break;
            std::stringstream name;
            name << "coin_" << count;
            //printf("c: %f\n", previous_x + i);
            Coordinate* coin_pos = new Coordinate(previous_x + i, coin_size + boundary, world_height, world_width);
            Coin* coin = new Coin(coin_pos, coin_size, coin_size,
                    -Config::config()->getStickman()->getVelocity(), name.str());
            root->addChild(coin);
            count++;
        }
        //puts("====");
        if (gap + coin_size >= obstacleConfig->width - boundary){
            std::stringstream name;
            name << "coin_" << count;
            Coordinate* coin_pos = new Coordinate(previous_x + obstacleConfig->offset_x - obstacleConfig->width/2.0, coin_size + boundary + obstacleConfig->position_y + obstacleConfig->height/2.0, world_height, world_width);
            Coin* coin = new Coin(coin_pos, coin_size, coin_size,
                    -Config::config()->getStickman()->getVelocity(), name.str());
            root->addChild(coin);
            count++;
        }
        for(double i = boundary; i < obstacleConfig->width - boundary; i += (gap + coin_size)){
            if (i + coin_size > obstacleConfig->offset_x - boundary) continue;
            std::stringstream name;
            name << "coin_" << count;
            Coordinate* coin_pos = new Coordinate(previous_x + obstacleConfig->offset_x - obstacleConfig->width/2.0 + i, coin_size + boundary + obstacleConfig->position_y + obstacleConfig->height/2.0, world_height, world_width);
            Coin* coin = new Coin(coin_pos, coin_size, coin_size,
                    -Config::config()->getStickman()->getVelocity(), name.str());
            root->addChild(coin);
            count++;
        }
        previous_x = previous_x + obstacleConfig->offset_x;
        previous_w = obstacleConfig->width;
    }

}

void Command::createFinishline(EmptyEntity *root, double start_x, unsigned int world_height, unsigned int world_width){
    std::string name = "finishline";
    Coordinate* sl_pos = new Coordinate(start_x,(double)100, world_height, world_width);
    FinishLine* sl = new FinishLine(sl_pos, 100, (double)100, -Config::config()->getStickman()->getVelocity(), QColor(Qt::green), name);
    root->addChild(sl);
}

void Command::createObstacles(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width){
    // Calculate when to loop the obstacles
    double loop = world_width;
    for (auto* obstacleConfig : obstacle_data) {
        loop += obstacleConfig->offset_x;
    }

    double previous_x = world_width;
    int count = 0;
    for (auto* obstacleConfig : obstacle_data) {
        previous_x = previous_x + obstacleConfig->offset_x;
        std::stringstream name;
        name << "obstacle_" << count;
        Coordinate* obs_pos = new Coordinate(previous_x, obstacleConfig->position_y, world_height, world_width);
        Obstacle* obs = new Obstacle(obs_pos, obstacleConfig->width, obstacleConfig->height,
                -Config::config()->getStickman()->getVelocity(), loop,
                QColor(obstacleConfig->colour_red, obstacleConfig->colour_green, obstacleConfig->colour_blue), name.str());
        root->addChild(obs);
        count++;
    }
    double gap = 50.0;
    background->setFinishpoint(-(previous_x + gap));
    //create finishline use the previous x offset
    createFinishline(root, -background->getFinishpoint() + Config::config()->getWorldWidth() - 150.0,world_height,world_width);
}

void Command::resetEntity(int level, bool new_level){
    // remove obstacles and finish line
    getEntity()->clearChildren();
    std::string name = getEntity()->getName();
    ConfigStage3 config(*Config::config());
    std::vector<ObstacleConfig*> obstacle_data;
    obstacle_data = config.getLevelObstacleData(level);
    if (new_level){
        // remove all coins
        for (auto* c : getEntity()->getChildren()){
            delete c;
        }
        getEntity()->getChildren().clear();
        coinGenerator(dynamic_cast<EmptyEntity*>(getEntity()), obstacle_data, config.getWorldHeight(),config.getWorldWidth());
    }
    else{
        // reset coins positions
        for (auto* c : getEntity()->getChildren()){
            //printf("%f\n",dynamic_cast<Coin*>(c)->getDistance());
            dynamic_cast<Coin*>(c)->getPosition()->changeInXCoordinate(-dynamic_cast<Coin*>(c)->getDistance());
            dynamic_cast<Coin*>(c)->setDistance(0.0);
        }
    }
    createObstacles(dynamic_cast<EmptyEntity*>(getEntity()), obstacle_data, config.getWorldHeight(),config.getWorldWidth());
}


