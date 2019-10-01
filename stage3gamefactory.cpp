#include "stage3gamefactory.h"

#include "stage3game.h"
#include "stage3gamestatefactory.h"

GameDialog* Stage3GameFactory::createGame() {
    Stage3GameStateFactory* factory = new Stage3GameStateFactory();
    Stage3GameState* state = factory->createGameState();
    return new Stage3Game(state);
}

