#include "controller_console.h"
#include <ncurses.h> // include the ncurses library for console input/output
#include <iostream>

ConsoleController::ConsoleController(BreakoutModel* model) {
	this->model = model;
};

Key::Action ConsoleController::getBotInput(int ballX, int paddleX){
    const int passableError = 4;
    if(abs(ballX-paddleX)>passableError){
        if(paddleX>ballX){
            return Key::action_left;
        }
        if(paddleX<ballX){
            return Key::action_right;
        }
    }
    return Key::no_action;
}

Key::Action ConsoleController::getInput() {
    wchar_t ch = getch();
    switch (ch)
    {
    case 'q':
        return Key::action_quit;
    case 'r':
        return Key::action_restart;
    case 'b':
        return Key::action_bot;
    case KEY_LEFT:
        return Key::action_left;
    case KEY_RIGHT:
        return Key::action_right;
    case ' ':
        return Key::action_shoot;
    default:
        return Key::no_action;
    }
    
};

