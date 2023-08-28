#include <ncurses.h>
#include <stdlib.h>
#include <iostream>

#include "model_simulator_breakout.h"
#include "view_console.h"
#include "controller_console.h"

int main() {
    bool botMode = false;

    BreakoutModel* breakout = new BreakoutModel();
    ConsoleView* view = new ConsoleView(breakout);
    ConsoleController* controller = new ConsoleController(breakout);
    Key::Action ch = Key::no_action;
    while(ch != Key::action_quit){
        if(ch==Key::action_restart){
            delete breakout;
            breakout = new BreakoutModel();
            view->setModel(breakout);
            botMode = false;
        }

        if(ch==Key::action_bot){
            botMode = !botMode;
        }
        ch = controller->getInput();
        if(botMode && ch==Key::no_action){
            ch = controller->getBotInput(breakout->getBalls().at(0).getX(), breakout->getPaddle().getX()+breakout->getPaddle().getWidth()/2);
        }
        breakout->simulate_game_step(ch);
    }
    delete breakout;
    delete view;
    return 0;
}