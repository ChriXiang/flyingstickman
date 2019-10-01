#include "stage3gamestatefactory.h"

#include <stdlib.h>
#include <time.h>

void Stage3GameStateFactory::createPowerUp(EmptyEntity *root, double x_position, std::string type, unsigned int world_height, unsigned int world_width){
    Coordinate* pos = new Coordinate(x_position, world_height, world_height, world_width);
    if (type == "powerup_small"){
        PowerUp* powerup = new PowerUp(pos, 30.0, 30.0,
                -Config::config()->getStickman()->getVelocity(), ":/img/pu1.png",type);
        root->addChild(powerup);
    }
    else if (type == "powerup_big"){
        PowerUp* powerup = new PowerUp(pos, 30.0, 30.0,
                -Config::config()->getStickman()->getVelocity(), ":/img/pu2.png",type);
        root->addChild(powerup);
    }
}

void Stage3GameStateFactory::powerUpGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width){
    // 2 big powerups, 2 small powerups and 1 special power up
    srand(time(NULL));
    int drop_position1 = rand() % obstacle_data.size();
    int drop_position2 = rand() % obstacle_data.size();
    int drop_position3 = rand() % obstacle_data.size();
    int drop_position4 = rand() % obstacle_data.size();
    // for special powerup
    int drop_position5 = -1;
    PowerUp* special_powerup = nullptr;
    if (rand() % 2 == 0) drop_position5 = rand() % obstacle_data.size();

    double previous_x = world_width;
    double previous_w = 0.0;
    double size = 30.0;
    // the boundary before and after every obstacle
    double boundary = 20.0;

    int idx = 0;

    for (auto* obstacleConfig : obstacle_data){

        if (idx == drop_position1){
            int rand_position = rand() % (int)(obstacleConfig->offset_x - boundary - size - obstacleConfig->width/2.0 - previous_w/2.0);
            createPowerUp(root,previous_x + previous_w/2.0 + rand_position, "powerup_small",world_height,world_width);
        }
        if (idx == drop_position2){
            int rand_position = rand() % (int)(obstacleConfig->offset_x - boundary - size - obstacleConfig->width/2.0 - previous_w/2.0);
            createPowerUp(root,previous_x + previous_w/2.0 + rand_position, "powerup_small",world_height,world_width);
        }
        if (idx == drop_position3){
            int rand_position = rand() % (int)(obstacleConfig->offset_x - boundary - size - obstacleConfig->width/2.0 - previous_w/2.0);
            createPowerUp(root,previous_x + previous_w/2.0 + rand_position, "powerup_big",world_height,world_width);
        }
        if (idx == drop_position4){
            int rand_position = rand() % (int)(obstacleConfig->offset_x - boundary - size - obstacleConfig->width/2.0 - previous_w/2.0);
            createPowerUp(root,previous_x + previous_w/2.0 + rand_position, "powerup_big",world_height,world_width);
        }
        if (idx == drop_position5){
            // for speciall power up
            int rand_position = rand() % (int)(obstacleConfig->offset_x - boundary - size - obstacleConfig->width/2.0 - previous_w/2.0);
            Coordinate* pos = new Coordinate(previous_x + previous_w/2.0 + rand_position, world_height, world_height, world_width);
            special_powerup = new PowerUp(pos, 30.0, 30.0,
                             -Config::config()->getStickman()->getVelocity(), ":/img/heart.png","powerup_special");
            root->addChild(special_powerup);
        }

        previous_x = previous_x + obstacleConfig->offset_x;
        previous_w = obstacleConfig->width;
        idx++;
    }
}

void Stage3GameStateFactory::coinGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width){
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


void Stage3GameStateFactory::createFinishline(EmptyEntity *root, double start_x, unsigned int world_height, unsigned int world_width){
    std::string name = "finishline";
    Coordinate* sl_pos = new Coordinate(start_x,(double)100, world_height, world_width);
    FinishLine* sl = new FinishLine(sl_pos, 100, (double)100, -Config::config()->getStickman()->getVelocity(), QColor(Qt::green), name);
    root->addChild(sl);
}

void Stage3GameStateFactory::createObstacles(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, Background* bg, unsigned int world_height, unsigned int world_width){
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
        //printf("%f\n",obs->getPosition()->getXCoordinate());
    }
    double gap = 50.0;
    bg->setFinishpoint(-(previous_x + gap));
    //create finishline use the previous x offset
    createFinishline(root, -bg->getFinishpoint() + Config::config()->getWorldWidth() - 150.0,world_height,world_width);
}

Stage3GameState* Stage3GameStateFactory::createGameState(){
    Stage3GameState* state = new Stage3GameState();

    unsigned int world_height = Config::config()->getWorldHeight();
    unsigned int world_width = Config::config()->getWorldWidth();

    // Create background and player
    Background* background = new Background(Coordinate(0, world_height, world_height, world_width));

    Coordinate* pos = new Coordinate(0, 0, world_height, world_width);
    EmptyEntity* root = new EmptyEntity(pos, "root");

    ConfigStage3 config(*Config::config());

    // set life
    Config::config()->getStickman()->setCurrentLive(config.getLive());

    // Load obstacle data from file
    std::vector<ObstacleConfig*> obstacle_data = config.getLevelObstacleData(1);

    // Create obstacles
    coinGenerator(root,obstacle_data,world_height, world_width);
    powerUpGenerator(root,obstacle_data,world_height, world_width);
    createObstacles(root, obstacle_data, background, world_height, world_width);

    // Create entity tree
    state->setRootEntity(root);
    state->setBackground(background);
    state->setLevel(1);
    state->setStickman(Config::config()->getStickman());

    return state;

}
