#ifndef BREAKOUT_MODEL_BALL_H
#define BREAKOUT_MODEL_BALL_H

class BallModel {
public:
    BallModel(double x, double y, double dx, double dy); // constructor for start position and direction

    void resetBall(double x, double y, double dx, double dy); // reset ball position and direction

    double getX(); // get current x-position
    double getY(); // get current y-position
    double getDX(); // get current x-velocity
    double getDY(); // get current y-velocity

    void collideX(); // updates x-velocity
    void collideY(); // updates y-velocity

    void simulate_step(); // updates the current position

private:
    double x; // current x-position
    double y; // current y-position
    double dx; // current x-velocity
    double dy; // current y-velocity
};

#endif //BREAKOUT_MODEL_BALL_H
