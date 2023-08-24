#ifndef BREAKOUT_MODEL_BRICK_SPECIAL_H
#define BREAKOUT_MODEL_BRICK_SPECIAL_H

#include "brick.h"

class SpecialBrickModel : public Brick {
public:
    SpecialBrickModel(int width, int height, int x, int y, double rotation, BrickState state = normal) : Brick(width, height, x, y, rotation, state){}; // sets width, position and amount of hits needed

private:
};

#endif //BREAKOUT_MODEL_BRICK_SPECIAL_H
