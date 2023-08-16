#ifndef BREAKOUT_BORDER_H
#define BREAKOUT_BORDER_H

#include "Collidable.h"

class BorderModel : public Collidable {
public:
    int isCollided(double x, double y);
};

#endif //BREAKOUT_BORDER_H
