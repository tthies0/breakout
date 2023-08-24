#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

class Ball{
public:
    Ball(double x, double y, double direction, double speed); // constructor for start position and direction

    void resetBall(double x, double y, double direction, double speed); // reset ball position and direction

    double getX(); // get current x-position
    double getY(); // get current y-position
    double getDirection(); // get current direction
    double getSpeed(); // get current speed
    void setX(double x); // set current x-position
    void setY(double y); // set current y-position
    void setDirection(double direction); // set current direction
    void setSpeed(double speed); // set current speed

private:
    double _x; // current x-position
    double _y; // current y-position
    double _direction; // current direction from 0.0 to 2 Pi (0 = 2 Pi = facing right)
    double _speed; // current speed
};

#endif //BREAKOUT_BALL_H
