#include "controller_console.h"

ConsoleController::ConsoleController(BreakoutModel* model) {
	this->model = model;
};

wchar_t ConsoleController::getInput() {
    wchar_t ch = getch();
    
    return ch;
};
