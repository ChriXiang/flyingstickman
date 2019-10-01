#include "stage3game.h"

#include "entity.h"
#include "player.h"
#include "leaderdialog.h"

#include <iostream>

Stage3Game::Stage3Game(Stage3GameState* state)
    : Stage2Game(state),
      state(state){
}

void Stage3Game::render(QPainter &painter) {
    if (state->getBackground() != nullptr) {
        //boundary check
        if (state->getBackground()->getCoordinate().getXCoordinate() > 0.0){
            if (direction == -1 || Config::config()->getStickman()->getXPosition() <= (int)Config::config()->getWorldWidth()/2)
                state->getBackground()->render(painter, true, direction);
            else
                state->getBackground()->render(painter, paused || (state->getPlayerColliding() == 1), direction);
        }
        else if (state->getBackground()->getCoordinate().getXCoordinate() < state->getBackground()->getFinishpoint()){
            if (direction == 1 || Config::config()->getStickman()->getXPosition() >= (int)Config::config()->getWorldWidth()/2)
                state->getBackground()->render(painter, true, direction);
            else
                state->getBackground()->render(painter, paused || (state->getPlayerColliding() == 1), direction);
        }
        else{
            state->getBackground()->render(painter, paused || (state->getPlayerColliding() == 1), direction);
        }

    }

    if (state->getPlayer() != nullptr) {
        state->getPlayer()->render(painter);
    }

    // Render all entities stored in the game state
    state->getRootEntity()->render(painter);
    QRect test_box_level(150,50,100,200);
    QRect test_box_life(750,50,100,200);
    QRect test_box_score(450,50,100,200);
    QFont font;
    QPen pen;
    if (Config::config()->getBackgroundNumber() == 2){
        pen.setColor(Qt::white);
    }
    else{
        pen.setColor(Qt::black);
    }

    font.setPointSize(20);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen(pen);
    // draw text and show them on the screen
    painter.drawText(test_box_score,"Score: " + QString::number(state->getScore()));
    painter.drawText(test_box_level,"Level: " + QString::number(state->getLevel()));
    painter.drawText(test_box_life,"Life: " + QString::number(state->getStickman()->getCurrentLive()));
}

void Stage3Game::keyPressEvent(QKeyEvent *event) {
    // Call key press event for parent class
    Stage2Game::keyPressEvent(event);

    if (event->type()==QEvent::KeyPress) {
        if (event->key() == Qt::Key_Left) {
            // Make stickman move backward
            direction = -1;
        }
        if (event->key() == Qt::Key_Right) {
            // Make stickman move foreward
            direction = 1;
        }
        if (event->key() == Qt::Key_P) {
            // replace original pause dialog
            // show leader board
            pause();
            LeaderDialog leader_dialog(&this->paused);
            leader_dialog.setModal(true);
            leader_dialog.setWindowTitle("Leader Board");
            leader_dialog.exec();
        }
    }

}

void Stage3Game::keyReleaseEvent(QKeyEvent *event) {
    if (event->type()==QEvent::KeyRelease) {
        if (event->key() == Qt::Key_Left) {
            // Make stickman move backward
            direction = 0;
        }
        if (event->key() == Qt::Key_Right) {
            // Make stickman move foreward
            direction = 0;
        }
    }
}

void Stage3Game::paintEvent(QPaintEvent* /*event*/) {
    // boundary check
    // and update game
    if (direction == -1 && state->getBackground()->getCoordinate().getXCoordinate() > 0.0){
        state->update(true, direction);
        if (state->getPlayer() != nullptr) {
            state->getPlayer()->update(paused, (double)1.0, direction);
            if (Config::config()->getStickman()->getXPosition() > 10.0){
                Config::config()->getStickman()->changeXPosition(Config::config()->getStickman()->getXPosition() + direction * Config::config()->getStickman()->getVelocity());

            }
        }

    }
    else if (direction == 1 && Config::config()->getStickman()->getXPosition() <= (int)Config::config()->getWorldWidth()/2){
        state->update(true, direction);
        if (state->getPlayer() != nullptr) {
            state->getPlayer()->update(paused, (double)1.0, direction);
            Config::config()->getStickman()->changeXPosition(Config::config()->getStickman()->getXPosition() + direction * Config::config()->getStickman()->getVelocity());
        }
    }
    else if (direction == 1 && state->getBackground()->getCoordinate().getXCoordinate() < state->getBackground()->getFinishpoint()){
        state->update(true, direction);
        if (state->getPlayer() != nullptr) {
            state->getPlayer()->update(paused, (double)1.0, direction);
            if (Config::config()->getStickman()->getXPosition() < Config::config()->getWorldWidth() - 10.0){
                Config::config()->getStickman()->changeXPosition(Config::config()->getStickman()->getXPosition() + direction * Config::config()->getStickman()->getVelocity());
            }
        }
    }
    else if (direction == -1 && Config::config()->getStickman()->getXPosition() >= (int)Config::config()->getWorldWidth()/2){
        state->update(true, direction);
        if (state->getPlayer() != nullptr) {
            state->getPlayer()->update(paused, (double)1.0, direction);
            Config::config()->getStickman()->changeXPosition(Config::config()->getStickman()->getXPosition() + direction * Config::config()->getStickman()->getVelocity());
        }
    }
    else{
        state->update(paused,direction);
    }

    // Render game
    QPainter painter(this);
    render(painter);
}
