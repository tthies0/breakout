#include "controller_console.h"
#include <ncurses.h> // include the ncurses library for console input/output
#include <iostream>

ConsoleController::ConsoleController(BreakoutModel* model, bool touchpad_mode) {
	this->model = model;
    this->touchpad_mode = touchpad_mode;
};

Key::Action ConsoleController::getInput() {
    if(touchpad_mode){
        handleTouchpad();
    }
    wchar_t ch = getch();
    switch (ch)
    {
    case 'q':
        return Key::action_quit;
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

Key::Action ConsoleController::handleTouchpad(){
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    MEVENT event;
    wchar_t mo = getch();
    if(mo!=KEY_MOUSE){
        return Key::no_action;
    }
    if(getmouse(&event) == OK && event.bstate & BUTTON1_PRESSED){
        printf("AAAAAAAAAA");
    }
    return Key::action_quit;

}