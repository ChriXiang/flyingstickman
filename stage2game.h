#pragma once

#include "stage1game.h"
#include "gamestate.h"

class GameState;

class Stage2Game : public Stage1Game {
public:
    Stage2Game(GameState* state);
    virtual ~Stage2Game();

    void render(QPainter &painter);

protected:

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    GameState* state;
    bool player_colliding;
};
