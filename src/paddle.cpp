#include "paddle.h"
#include "model_simulator_breakout.h"

Paddle::Paddle(double startPos) : _position(startPos){}

void Paddle::movePaddleLeft() {

    if (_position - _width > BreakoutModel::gameWidth) {
        _position += _paddleSpeed;
    }

}

void Paddle::movePaddleRight() {

    if (_position + _width < BreakoutModel::gameWidth) {
        _position += _paddleSpeed;
    }

}
