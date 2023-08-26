#include "view_console.h"
#include "model_simulator_breakout.h"
#include <ncurses.h>
#include <stdlib.h>
#include "brick.h"


ConsoleView::ConsoleView(BreakoutModel* model) {
	setup_view();
	this->model = model;
	this->model->addObserver(this);
    this->test = 1;
};

ConsoleView::~ConsoleView() {
    endwin();
};

void ConsoleView::update() {
    // libncurses standard loop calls
    erase();
    refresh();

    // Example for building the game view
    for(int i = 0; i < BreakoutModel::gameWidth; i++) {
        mvaddch(0, i, wallTexture);
    }
    for(int i = 0; i < BreakoutModel::gameHeight; i++) {
        mvaddch(i, 0, wallTexture);
        mvaddch(i, BreakoutModel::gameWidth - 1, wallTexture);
    }
    // Show points of player
    mvprintw(1, BreakoutModel::gameWidth / 2 / 2, "%i", model->getBalls().at(0).getX());

    // Draw different objects.

    for(Ball ball : model->getBalls()){
        mvaddch(BreakoutModel::gameHeight-ball.getY(),ball.getX(), ballTexture);
    }

    for(Brick brick : model->getBricks()){
        if(brick.getState()!=Brick::normal){
            continue;
        }
        mvaddch(BreakoutModel::gameHeight-brick.getY(),brick.getX(), brickTexture);
    }

    for(int i = 0; i<model->getPaddle().getWidth(); i++){
        mvaddch(BreakoutModel::gameHeight-model->getPaddle().getY()-1, model->getPaddle().getX()+i, paddleTexture);
    }


};

void ConsoleView::setup_view() {
    // Init ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(30);
};