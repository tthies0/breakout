#ifndef BREAKOUT_MODEL_PADDLE_H
#define BREAKOUT_MODEL_PADDLE_H

class Paddle : public Collidable{
public:
    Paddle(double startPos) : _position(startPos){}; // set start position

    void movePaddleLeft(); // moves the paddle one step closer to the left side (if possible)
    void movePaddleRight(); // moves the paddle one step closer to the right side (if possible)
    double getWidth();
    double getHeight();
    double getPos();

    static const double yPosition = 5

private:
    double _position; // position of paddle (left side)
    const double _width = 5; // width of paddle
    const double _height = 2; // height of paddle
    const double _paddleSpeed = 2; 
};

#endif //BREAKOUT_MODEL_PADDLE_H
