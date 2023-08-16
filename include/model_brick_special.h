#ifndef BREAKOUT_MODEL_BRICK_SPECIAL_H
#define BREAKOUT_MODEL_BRICK_SPECIAL_H

#include "model_brick.h"

class SpecialBrickModel : public BrickModel {
public:
    SpecialBrickModel(int width, int x, int y, int hitAmount); // sets width, position and amount of hits needed

private:
    int hitCounter = 0; // saves how many hits have already occurred
};

#endif //BREAKOUT_MODEL_BRICK_SPECIAL_H
