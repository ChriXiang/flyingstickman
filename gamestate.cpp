#include "gamestate.h"

#include "background.h"
#include "entity.h"
#include "player.h"
#include "rectcollider.h"
#include "obstacle.h"
#include "powerup.h"

GameState::GameState()
    : player(nullptr),
      background(nullptr),
      root_entity(nullptr),
      player_colliding(false) {}

GameState::~GameState()
{
    if (Config::config()->getStage() != 3){
        delete player;
    }
    delete background;
    delete root_entity;
}

Entity* GameState::getRootEntity() {
    return root_entity;
}

Entity* GameState::findEntityByName(const std::string& name) {
    return findEntityByNameRecursive(name, root_entity);
}

Entity* GameState::findEntityByNameRecursive(const std::string& name, Entity* root) {
    if (root->getName() == name) {
        return root;
    }
    Entity* found = nullptr;
    for (auto* child : root_entity->getChildren()) {
        found = findEntityByNameRecursive(name, child);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

std::vector<Entity*> GameState::findEntitiesByNameContains(const std::string& string) {
    std::vector<Entity*> list;

    findEntitiesByNameContainsRecursive(string, root_entity, list);
    return list;
}

void GameState::findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list) {
    if (root->getName().find(string) != std::string::npos) {
        list.push_back(root);
    }

    for (auto* child : root->getChildren()) {
        findEntitiesByNameContainsRecursive(string, child, list);
    }
}

void GameState::setRootEntity(Entity* root) {
    root_entity = root;
}

Background* GameState::getBackground() {
    return background;
}

Player* GameState::getPlayer() {
    return player;
}

void GameState::setBackground(Background* bg) {
    background = bg;
}

void GameState::setPlayer(Player* player) {
    this->player = player;
}

int GameState::checkCollisions() {
    int player_collided = 0;
    for (auto* entity : findEntitiesByNameContains("")) {
        // Check collisions with player
        if (entity->getName() == "finishline") continue;
        //if (entity->getName().substr(0,4) == "coin") continue;
        RectCollider* p_col = getPlayer()->getCollider();

        RectCollider* o_col = entity->getCollider();
        if (p_col != nullptr && o_col != nullptr) {
            if (p_col->checkCollision(*o_col)) {


                if (entity->getName().substr(0,4) == "coin"){
                    if (!dynamic_cast<Coin*>(entity)->getTaken()){
                        dynamic_cast<Coin*>(entity)->setTaken(true);
                        player_collided = 2;
                        break;
                    }
                }
                else if (entity->getName() == "powerup_small"){
                    if (!dynamic_cast<PowerUp*>(entity)->getTaken()){
                        dynamic_cast<PowerUp*>(entity)->setTaken(true);
                        player_collided = 3;
                        break;
                    }
                }
                else if (entity->getName() == "powerup_big"){
                    if (!dynamic_cast<PowerUp*>(entity)->getTaken()){
                        dynamic_cast<PowerUp*>(entity)->setTaken(true);
                        player_collided = 4;
                        break;
                    }
                }
                else if (entity->getName() == "powerup_special"){
                    if (!dynamic_cast<PowerUp*>(entity)->getTaken()){
                        dynamic_cast<PowerUp*>(entity)->setTaken(true);
                        player_collided = 5;
                        break;
                    }
                }
                else{
                    //obstacle
                    if (dynamic_cast<Obstacle*>(entity)->getEnable()){
                        getPlayer()->onCollision(entity);
                        entity->onCollision(getPlayer());
                        if (getPlayer()->getName() != "stickman_giant"){
                            player_collided = 1;
                            break;
                        }
                    }


                }
            }
        }
    }
    /*
     * 0: normal game
     * 1: collision
     * 2: coin
     * 3: small powerup
     * 4: big powerup
     * 5: special powerup
     */
    return player_collided;
}

void GameState::update(bool paused, int direction) {
    player_colliding = checkCollisions();
    double deltaTimeMilliseconds = 32; // Comes from hard coded timer interval value in Stage1Game.
    getRootEntity()->update(paused || (player_colliding > 0), deltaTimeMilliseconds, direction);
    if (getPlayer() != nullptr) {
        getPlayer()->update(paused, deltaTimeMilliseconds, direction);
    }
}
