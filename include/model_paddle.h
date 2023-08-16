#ifndef BREAKOUT_MODEL_PADDLE_H
#define BREAKOUT_MODEL_PADDLE_H

#include "Collidable.h"

class PaddleModel : public Collidable {
public:
    PaddleModel(int start); // set start position

    void movePaddleLeft(); // moves the paddle one step closer to the left side (if possible)
    void movePaddleRight(); // moves the paddle one step closer to the right side (if possible)

private:
    int position; // position of paddle (left side)
    int width = 5; // width of paddle
    int height = 2; // height of paddle
};

#endif //BREAKOUT_MODEL_PADDLE_H
