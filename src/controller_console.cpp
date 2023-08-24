#include "controller_console.h"
#include <ncurses.h> // include the ncurses library for console input/output
#include <iostream>

ConsoleController::ConsoleController(BreakoutModel* model, bool touchpad_mode) {
	this->model = model;
    this->touchpad_mode = touchpad_mode;
};

Controller::KeyAction ConsoleController::getInput() {
    if(touchpad_mode){
        handleTouchpad();
    }
    wchar_t ch = getch();
    switch (ch)
    {
    case 'q':
        return action_quit;
    case KEY_LEFT:
        return action_left;
    case KEY_RIGHT:
        return action_right;
    case ' ':
        return action_shoot;
    default:
        return no_action;
    }
    
};

Controller::KeyAction ConsoleController::handleTouchpad(){
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    MEVENT event;
    wchar_t mo = getch();
    if(mo!=KEY_MOUSE){
        return no_action;
    }
    if(getmouse(&event) == OK && event.bstate & BUTTON1_PRESSED){
        printf("AAAAAAAAAA");
    }
    return action_quit;

}