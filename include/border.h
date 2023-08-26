#ifndef BREAKOUT_BORDER_H // header guard to prevent multiple inclusions of the same header file
#define BREAKOUT_BORDER_H
#include "collidable.h"

class Border : public Collidable{
    public:
    Border(double width, double height, double x, double y, double rotation) : Collidable(width, height, x, y, rotation){};
};

#endif // end of header file