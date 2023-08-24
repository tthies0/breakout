#ifndef BREAKOUT_COLLIDABLE_H
#define BREAKOUT_COLLIDABLE_H

class Collidable {
public:
    Collidable(double width, double height, double x, double y);

    double getWidth();
    double getHeight();
    double getX();
    double getY();

private:
    double _width;
    double _height;
    double _x;
    double _y;
};

#endif //BREAKOUT_COLLIDABLE_H
