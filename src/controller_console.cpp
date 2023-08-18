#include "controller_console.h"

ConsoleController::ConsoleController(BreakoutModel* model, bool touchpad_mode) {
	this->model = model;
    this->touchpad_mode = touchpad_mode;
};

Controller::KeyAction ConsoleController::getInput() {
    wchar_t ch = getch();
    if(touchpad_mode){
        return action_quit;
    }

    if(ch = KEY_LEFT){
        return action_left;
    }
    if(ch = KEY_RIGHT){
        return action_right;
    }
    if(ch = 'q'){
        return action_quit;
    }
    if(ch = ' '){
        return action_shoot;
    }
    
};
