#include "stage3gamestate.h"

#include "background.h"


Stage3GameState::Stage3GameState()
    : GameState(),
      score(0)
{
    // create 4 instances of concrete state
    normal_player = new StickmanPlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5),
                                                                                             0 + Config::config()->getStickman()->getHeight(),
                                                                                             Config::config()->getWorldHeight(),
                                                                                             Config::config()->getWorldWidth()),
                                                                              "stickman_normal");
    tiny_player = new TinyPlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5),
                                                                                             0 + Config::config()->getStickman()->getHeight(),
                                                                                             Config::config()->getWorldHeight(),
                                                                                             Config::config()->getWorldWidth()),
                                                                              "stickman_tiny");
    large_player = new LargePlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5),
                                                                                             0 + Config::config()->getStickman()->getHeight(),
                                                                                             Config::config()->getWorldHeight(),
                                                                                             Config::config()->getWorldWidth()),
                                                                              "stickman_large");
    giant_player = new GiantPlayer(new Coordinate(Config::config()->getStickman()->getXPosition() - (Config::config()->getStickman()->getWidth()*0.5),
                                                                                             0 + Config::config()->getStickman()->getHeight(),
                                                                                             Config::config()->getWorldHeight(),
                                                                                             Config::config()->getWorldWidth()),
                                                                              "stickman_giant");
    // set state to be one of the concrete state
    setPlayer(normal_player);

}

Stage3GameState::~Stage3GameState(){
    delete normal_player;
    delete tiny_player;
    delete large_player;
    delete giant_player;
}

int Stage3GameState::getLevel(){
    return level;
}
void Stage3GameState::setLevel(int change){
    level = change;
}

int Stage3GameState::getScore(){
    return score;
}
void Stage3GameState::setScore(int change){
    score = change;
}

Player* Stage3GameState::getNormalPlayer(){
    return normal_player;
}
Player* Stage3GameState::getTinyPlayer(){
    return tiny_player;
}
Player* Stage3GameState::getLargePlayer(){
    return large_player;
}
Player* Stage3GameState::getGiantPlayer(){
    return giant_player;
}
Player* Stage3GameState::getCurrentPlayer(){
    return current_player;
}
Stickman* Stage3GameState::getStickman(){
    return stickman;
}
void Stage3GameState::setStickman(Stickman* stickman){
    this->stickman = stickman;
}

void Stage3GameState::update(bool paused, int direction){

    // set up maps to enable directly player change
    std::vector<std::string> stickman_status = {"stickman_tiny","stickman_normal","stickman_large","stickman_giant"};
    std::map<std::string, Player*> stickman_map = {{"stickman_tiny",tiny_player},{"stickman_normal",normal_player},{"stickman_large",large_player},{"stickman_giant",giant_player}};
    std::map<std::string, std::string> size_map = {{"stickman_tiny","tiny"},{"stickman_normal","normal"},{"stickman_large","large"},{"stickman_giant","giant"}};
    double deltaTimeMilliseconds = 32; // Comes from hard coded timer interval value in Stage1Game.

    // check collision, get collision type
    player_colliding = checkCollisions();

    // coin
    if (player_colliding == 2){
        setScore(getScore() + 1);
    }
    //small powerup
    else if (player_colliding == 3){
        if (std::find(stickman_status.begin(),stickman_status.end(),getPlayer()->getName()) != stickman_status.begin()){
            int previous_y = getPlayer()->getPosition()->getYCoordinate();
            double previous_v = getPlayer()->getYvelocity();
            setPlayer(stickman_map[*(std::find(stickman_status.begin(),stickman_status.end(),getPlayer()->getName()) - 1)]);
            if (previous_v != 0.0){
                getPlayer()->getPosition()->setYCoordinateToZero(previous_y);
                getPlayer()->setOffsetYCoordinate(previous_y);
                getPlayer()->setYvelocity(previous_v);
            }
            Config::config()->getStickman()->changeSize(size_map[*(std::find(stickman_status.begin(),stickman_status.end(),getPlayer()->getName()))]);
            Config::config()->getStickman()->updateStickman();
            if (getPlayer()->getName() == "stickman_tiny"){
                std::vector<Entity*>::iterator it;
                for (it = getRootEntity()->getChildren().begin(); it != getRootEntity()->getChildren().end(); it++) {
                    if ((*it)->getName().substr(0,4) == "coin"){
                        dynamic_cast<Coin*>(*it)->setVelocity(-Config::config()->getStickman()->getVelocity() * 2);
                    }
                    else if ((*it)->getName().substr(0,8) == "obstacle"){
                        dynamic_cast<Obstacle*>(*it)->setVelocity(-Config::config()->getStickman()->getVelocity() * 2);
                    }
                    else if ((*it)->getName() == "finishline"){
                        dynamic_cast<FinishLine*>(*it)->setVelocity(-Config::config()->getStickman()->getVelocity() * 2);
                    }
                    else if ((*it)->getName().substr(0,7) == "powerup" ){
                        dynamic_cast<PowerUp*>(*it)->setVelocity(-Config::config()->getStickman()->getVelocity() * 2);
                    }
                }
                Config::config()->getStickman()->changeVelocity(Config::config()->getStickman()->getVelocity() * 2);
            }
        }
    }
    //big powerup
    else if (player_colliding == 4){
        if (std::find(stickman_status.begin(),stickman_status.end(),getPlayer()->getName()) != stickman_status.end() - 1){
            if (getPlayer()->getName() == "stickman_tiny"){
                std::vector<Entity*>::iterator it;
                for (it = getRootEntity()->getChildren().begin(); it != getRootEntity()->getChildren().end(); it++) {
                    if ((*it)->getName().substr(0,4) == "coin"){
                        dynamic_cast<Coin*>(*it)->setVelocity(-Config::config()->getStickman()->getVelocity() / 2);
                    }
                    else if ((*it)->getName().substr(0,8) == "obstacle"){
                        dynamic_cast<Obstacle*>(*it)->setVelocity(-Config::config()->getStickman()->getVelocity() / 2);
                    }
                    else if ((*it)->getName() == "finishline"){
                        dynamic_cast<FinishLine*>(*it)->setVelocity(-Config::config()->getStickman()->getVelocity() / 2);
                    }
                    else if ((*it)->getName().substr(0,7) == "powerup"){
                        dynamic_cast<PowerUp*>(*it)->setVelocity(-Config::config()->getStickman()->getVelocity() / 2);
                    }
                }
                Config::config()->getStickman()->changeVelocity(Config::config()->getStickman()->getVelocity() / 2);
            }

            int previous_y = getPlayer()->getPosition()->getYCoordinate();
            double previous_v = getPlayer()->getYvelocity();
            setPlayer(stickman_map[*(std::find(stickman_status.begin(),stickman_status.end(),getPlayer()->getName()) + 1)]);
            if (previous_v != 0.0){
                getPlayer()->getPosition()->setYCoordinateToZero(previous_y);
                getPlayer()->setOffsetYCoordinate(previous_y);
                getPlayer()->setYvelocity(previous_v);
            }
            Config::config()->getStickman()->changeSize(size_map[*(std::find(stickman_status.begin(),stickman_status.end(),getPlayer()->getName()))]);
            Config::config()->getStickman()->updateStickman();
        }
    }
    // special power up
    else if (player_colliding == 5){
        Config::config()->getStickman()->setCurrentLive(Config::config()->getStickman()->getCurrentLive() + 1);
    }

    // check if level up or win
    int increament_level = 0;

    // by checking player's position vs finishline's position
    if (getPlayer()->getPosition()->getXCoordinate() >= getRootEntity()->getChildren()[getRootEntity()->getChildren().size()-1]->getPosition()->getXCoordinate()){
        //new level
        if (level < 3){
            getPlayer()->getPosition()->setXCoordinateToZero(0);
            Config::config()->getStickman()->changeXPosition(Config::config()->getWorldWidth()/2);
            getBackground()->resetBackground();
            // load next level entity
            resetEntity(level + 1, true);
            //increment level
            increament_level = 1;
        }
        // You win!
        else{
            increament_level = 2;
        }
    }

    // collid on obstacles
    if (player_colliding == 1 && getStickman()->getCurrentLive() > 1){
        // life - 1
        getStickman()->setCurrentLive(getStickman()->getCurrentLive() - 1);
        // restart level
        getPlayer()->getPosition()->setXCoordinateToZero(0);
        getPlayer()->getPosition()->setYCoordinateToZero(0);
        getBackground()->resetBackground();
        //reset all level entities
        resetEntity(level, false);
    }
    else if (player_colliding == 1 && getStickman()->getCurrentLive() == 1){
        //gameover
        lossDialog(score);
    }
    else{
        //no collision, normal update
        getRootEntity()->update(paused, deltaTimeMilliseconds, direction);
    }

    // update all player together
    // keep synchronizing all players
    getNormalPlayer()->update(paused, deltaTimeMilliseconds, direction);
    getTinyPlayer()->update(paused, deltaTimeMilliseconds, direction);
    getLargePlayer()->update(paused, deltaTimeMilliseconds, direction);
    getGiantPlayer()->update(paused, deltaTimeMilliseconds, direction);

    if (increament_level == 1){
        //level change
        setLevel(level + 1);
    }
    else if (increament_level == 2){
        //win game
        winDialog(score);
    }
}

void Stage3GameState::winDialog(int score){
    WinDialog win_dialog(score);
    win_dialog.setModal(true);
    win_dialog.setWindowTitle("Win Screen");
    win_dialog.exec();
}

void Stage3GameState::lossDialog(int score){
    LossDialog loss_dialog(score);
    loss_dialog.setModal(true);
    loss_dialog.setWindowTitle("Loss Screen");
    loss_dialog.exec();
}

void Stage3GameState::coinGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width){
    double previous_x = world_width;
    double previous_w = 0.0;
    double coin_size = 30.0;
    double gap = 40.0;
    int count = 0;
    // the boundary before and after every obstacle
    double boundary = 20.0;

    for (auto* obstacleConfig : obstacle_data){
        // spawn coin on the ground, between obstacles
        for (double i = boundary + previous_w/2.0; i + coin_size <= obstacleConfig->offset_x - obstacleConfig->width/2.0; i += (gap + coin_size)){
            std::stringstream name;
            name << "coin_" << count;
            Coordinate* coin_pos = new Coordinate(previous_x + i, coin_size + boundary, world_height, world_width);
            Coin* coin = new Coin(coin_pos, coin_size, coin_size,
                    -Config::config()->getStickman()->getVelocity(), name.str());
            root->addChild(coin);
            count++;
        }

        // spawn coin on the obstacle, if obstalce's width is small
        if (gap + coin_size >= obstacleConfig->width - boundary){
            std::stringstream name;
            name << "coin_" << count;
            Coordinate* coin_pos = new Coordinate(previous_x + obstacleConfig->offset_x - obstacleConfig->width/2.0, coin_size + boundary + obstacleConfig->position_y + obstacleConfig->height/2.0, world_height, world_width);
            Coin* coin = new Coin(coin_pos, coin_size, coin_size,
                    -Config::config()->getStickman()->getVelocity(), name.str());
            root->addChild(coin);
            count++;
        }

        // spawn coin on the obstacle
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

void Stage3GameState::createFinishline(EmptyEntity *root, double start_x, unsigned int world_height, unsigned int world_width){
    // actually create the finish line
    std::string name = "finishline";
    Coordinate* sl_pos = new Coordinate(start_x,(double)100, world_height, world_width);
    FinishLine* sl = new FinishLine(sl_pos, 100, (double)100, -Config::config()->getStickman()->getVelocity(), QColor(Qt::green), name);
    root->addChild(sl);
}

void Stage3GameState::createObstacles(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width){
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
    // create finishline use the previous x offset
    // finish line is at the last position of children vector
    createFinishline(root, -background->getFinishpoint() + Config::config()->getWorldWidth() - 150.0,world_height,world_width);
}

void Stage3GameState::resetEntity(int level, bool new_level){
    // remove obstacles and finish line
    getRootEntity()->clearChildren();
    std::string name = getRootEntity()->getName();
    ConfigStage3 config(*Config::config());
    std::vector<ObstacleConfig*> obstacle_data;
    obstacle_data = config.getLevelObstacleData(level);
    if (new_level){
        // remove all coins and powerups
        for (auto* c : getRootEntity()->getChildren()){
            delete c;
        }
        getRootEntity()->getChildren().clear();
        coinGenerator(dynamic_cast<EmptyEntity*>(getRootEntity()), obstacle_data, config.getWorldHeight(),config.getWorldWidth());
        powerUpGenerator(dynamic_cast<EmptyEntity*>(getRootEntity()), obstacle_data, config.getWorldHeight(),config.getWorldWidth());
    }
    else{
        // reset coins, powerups positions
        for (auto* c : getRootEntity()->getChildren()){
            if (c->getName().substr(0,4) == "coin"){
                dynamic_cast<Coin*>(c)->getPosition()->changeInXCoordinate(-dynamic_cast<Coin*>(c)->getDistance());
                dynamic_cast<Coin*>(c)->setDistance(0.0);
            }
            else if (c->getName().substr(0,7) == "powerup"){
                dynamic_cast<PowerUp*>(c)->getPosition()->changeInXCoordinate(-dynamic_cast<PowerUp*>(c)->getDistance());
                dynamic_cast<PowerUp*>(c)->setDistance(0.0);
            }

        }
    }
    // create new obstacles and finishline
    createObstacles(dynamic_cast<EmptyEntity*>(getRootEntity()), obstacle_data, config.getWorldHeight(),config.getWorldWidth());
}

void Stage3GameState::createPowerUp(EmptyEntity *root, double x_position, std::string type, unsigned int world_height, unsigned int world_width){
    // actually create power up
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

void Stage3GameState::powerUpGenerator(EmptyEntity *root, std::vector<ObstacleConfig *> obstacle_data, unsigned int world_height, unsigned int world_width){
    // 2 big powerups, 2 small powerups and 1 special power up
    srand(time(NULL));
    // for 4 normal powerups, randomly find an interval
    int drop_position1 = rand() % obstacle_data.size();
    int drop_position2 = rand() % obstacle_data.size();
    int drop_position3 = rand() % obstacle_data.size();
    int drop_position4 = rand() % obstacle_data.size();
    // for special powerup
    int drop_position5 = -1;
    PowerUp* special_powerup = nullptr;
    // 1/2 chance to pawn a special power up
    if (rand() % 2 == 0) drop_position5 = rand() % obstacle_data.size();

    double previous_x = world_width;
    double previous_w = 0.0;
    double size = 30.0;
    // the boundary before and after every obstacle
    double boundary = 20.0;

    int idx = 0;

    for (auto* obstacleConfig : obstacle_data){
        // spawn corresponing powerup at randonly chosen x coordinate
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

