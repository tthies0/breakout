#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

class Ball{
public:
    Ball(double x, double y, double directionX, double directionY, double speed); // constructor for start position and direction

    double getX(); // get current x-position
    double getY(); // get current y-position
    double getDirectionX(); // get current direction
    double getDirectionY(); // get current direction
    double getSpeed(); // get current speed
    void setX(double x); // set current x-position
    void setY(double y); // set current y-position
    void setDirectionX(double direction); // set current direction
    void setDirectionY(double direction); // set current direction
    void setSpeed(double speed); // set current speed

private:
    double _x; // current x-position
    double _y; // current y-position
    double _directionX; // current direction X part
    double _directionY; // current direction Y part(always normal vector)
    double _speed; // current speed
};

#endif //BREAKOUT_BALL_H
