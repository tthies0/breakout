#ifndef BREAKOUT_COLLIDABLE_H
#define BREAKOUT_COLLIDABLE_H

class Collidable {
public:
    virtual int isCollided(double x, double y) = 0; // tests if the current ball position collides with the position of the object
                                  // 0: no, 1: to a wall, 2: to a ceiling, 3: ball left the field
};

#endif //BREAKOUT_COLLIDABLE_H
