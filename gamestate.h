#pragma once

// Responsible for storing the game state of the current game, independently of rendering.

#include <string>
#include <vector>
#include "coin.h"

class Background;
class Entity;
class Player;

class GameState {

public:
    GameState();
    virtual ~GameState();

    Entity* getRootEntity();
    void setRootEntity(Entity* root);

    Entity* findEntityByName(const std::string& name);
    std::vector<Entity*> findEntitiesByNameContains(const std::string& string);

    Background* getBackground();
    void setBackground(Background* bg);

    Player* getPlayer();
    void setPlayer(Player* player);

    virtual void update(bool paused, int direction = 1);
    virtual int getPlayerColliding() {return player_colliding; }

    Entity* findEntityByNameRecursive(const std::string& name, Entity* root);
    void findEntitiesByNameContainsRecursive(const std::string& string, Entity* root, std::vector<Entity*>& list);

    int checkCollisions();

protected:
    Player* player;
    Background* background;
    Entity* root_entity;
    int player_colliding;
};

