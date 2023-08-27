#ifndef CONTROLLER_BREAKOUT_H_ // header guard to prevent multiple includes
#define CONTROLLER_BREAKOUT_H_

#include "model_simulator_breakout.h" // include the Pong Model header file
#include "KeyAction.h"
#include <ncurses.h> // include the ncurses library for console input/output

class Controller
{
public:
    // You should consider how to keep this as general as possible. And should set the type accordingly.
    virtual Key::Action getInput() = 0; // declare a pure virtual function for getting user input
};

class ConsoleController : public Controller // derive ConsoleController class from the Controller base class
{
    BreakoutModel* model; // pointer to the BreakoutModel object

public:
    ConsoleController(BreakoutModel* model); // constructor that takes a BreakoutModel pointer as parameter

    Key::Action getInput(); // override the getInput() function to get input from the console
};

#endif  // end of header guard
