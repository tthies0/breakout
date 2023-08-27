#include "view_console.h"
#include "model_simulator_breakout.h"
#include <ncurses.h>
#include <stdlib.h>
#include "brick.h"


ConsoleView::ConsoleView(BreakoutModel* model) {
	setup_view();
	this->model = model;
	this->model->addObserver(this);
};

ConsoleView::~ConsoleView() {
    endwin();
};

void ConsoleView::setModel(BreakoutModel* model){
    this->model = model;
    this->model->addObserver(this);
}

void ConsoleView::update() {

    // libncurses standard loop calls
    erase();
    refresh();

    if(model->getState()==BreakoutModel::won){
        mvprintw(BreakoutModel::gameHeight/2, BreakoutModel::gameWidth/2, "You won with %i Points", model->getScore());
        mvprintw(BreakoutModel::gameHeight/2 + 2, BreakoutModel::gameWidth/2, "Press r to restart");
        return;
    }
    if(model->getState()==BreakoutModel::lost){
        mvprintw(BreakoutModel::gameHeight/2, BreakoutModel::gameWidth/2, "You lost with %i Points", model->getScore());
        mvprintw(BreakoutModel::gameHeight/2 + 2, BreakoutModel::gameWidth/2, "Press r to restart");
        return;
    }
    
    // Example for building the game view
    for(int i = 0; i < BreakoutModel::gameWidth +1; i++) {
        mvaddch(0, i, wallTexture);
    }
    for(int i = 0; i < BreakoutModel::gameHeight; i++) {
        mvaddch(i, 0, wallTexture);
        mvaddch(i, BreakoutModel::gameWidth + 1, wallTexture);
    }
    // Show points of player
    mvprintw(1, BreakoutModel::gameWidth + 3, "%i", model->getScore());

    // Draw different objects.
    
    for(Ball ball : model->getBalls()){
        mvaddch(BreakoutModel::gameHeight-ball.getY()+1,ball.getX()+1, ballTexture);
    }

    for(Brick brick : model->getBricks()){
        if(brick.getState()==0){
            continue;
        }

        char thisBrickTexture = brickTexture;
        if(brick.getState()==2){
            thisBrickTexture = brickHitTwiceTexture;
        }
        if(brick.getState()==3){
            thisBrickTexture = brickAddBallTexture;
        }
        for(int i = 0; i<brick.getWidth(); i++){
            mvaddch(BreakoutModel::gameHeight-brick.getY()+1,brick.getX()+i+1, thisBrickTexture);
            mvaddch(BreakoutModel::gameHeight-brick.getY()-brick.getHeight()+1,brick.getX()+i+1, thisBrickTexture);
        }
        for(int i = 0; i<brick.getHeight(); i++){
            mvaddch(BreakoutModel::gameHeight-brick.getY()-i+1,brick.getX()+1, thisBrickTexture);
            mvaddch(BreakoutModel::gameHeight-brick.getY()-i+1, brick.getX()+brick.getWidth()+1, thisBrickTexture);
        }
        
    }

    for(int i = 0; i<model->getPaddle().getWidth(); i++){
        mvaddch(BreakoutModel::gameHeight-model->getPaddle().getY(), model->getPaddle().getX()+i+1, paddleTexture);
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