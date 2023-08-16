#ifndef BREAKOUT_COLLIDABLE_H
#define BREAKOUT_COLLIDABLE_H

class Collidable {
public:
    int isCollided(); // tests if the current ball position collides with the position of the object
                      // 0: no, 1: to a wall, 2: to a ceiling
};

#endif //BREAKOUT_COLLIDABLE_H
