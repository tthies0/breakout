#include <ncurses.h>
#include <stdlib.h>
#include <iostream>

#include "model_simulator_breakout.h"
#include "view_console.h"
#include "controller_console.h"

int main() {
    BreakoutModel* breakout = new BreakoutModel();
    ConsoleView* view = new ConsoleView(breakout);
    ConsoleController* controller = new ConsoleController(breakout);
    wchar_t ch = '\0';
    while(ch != 'q') {
        ch = controller->getInput();
        breakout->simulate_game_step();
    }
    delete breakout;
    delete view;
    return 0;
}