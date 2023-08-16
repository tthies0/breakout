#ifndef MODEL_BREAKOUT_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_BREAKOUT_H_

#include "observer.h" // include header file for the Observable class

class BreakoutModel : public Observable { // PongModel class inherits from Observable class
public:
    BreakoutModel(); // constructor

    void simulate_game_step(); // simulates one step of the Pong game

    static const int gameWidth = 40; // game width
    static const int gameHeight = 24; // game height
};

#endif // end of header file
