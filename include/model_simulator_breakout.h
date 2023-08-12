#ifndef MODEL_BREAKOUT_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_BREAKOUT_H_

#include "observer.h" // include header file for the Observable class

class BreakoutModel : public Observable { // PongModel class inherits from Observable class
public:
    BreakoutModel(); // constructor

    int getGameWidth(); // returns the game's width
    int getGameHeight(); // returns the game's height

    void simulate_game_step(); // simulates one step of the Pong game

private:
    int width = 40; // game width
    int height = 24; // game height
    int dir = 1; // ball direction
};

#endif // end of header file
