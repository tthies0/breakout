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
    Key::Action ch = Key::no_action;
    while(ch != Key::action_quit){
        if(ch==Key::action_restart){
            delete breakout;
            breakout = new BreakoutModel();
            view->setModel(breakout);
        }

        ch = controller->getInput();
        breakout->simulate_game_step(ch);
    }
    delete breakout;
    delete view;
    return 0;
}