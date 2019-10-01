#ifndef STAGE3GAME_H
#define STAGE3GAME_H

#include "stage2game.h"
#include "stage3gamestate.h"

class Stage3Game : public Stage2Game{

public:
    Stage3Game(Stage3GameState* state);
    ~Stage3Game() = default;

    void render(QPainter &painter);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    int direction = 0;
    Stage3GameState* state;

};

#endif // STAGE3GAME_H
