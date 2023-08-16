#include "model_ball.h"

BallModel::BallModel(double x, double y, double dx, double dy) {
    BallModel::resetBall(x, y, dx, dy);
}

void BallModel::resetBall(double x, double y, double dx, double dy) {
    BallModel::x = x;
    BallModel::y = y;
    BallModel::dx = dx;
    BallModel::dy = dy;
}

double BallModel::getX() {
    return BallModel::x;
}

double BallModel::getY() {
    return BallModel::y;
}

double BallModel::getDX() {
    return BallModel::dx;
}

double BallModel::getDY() {
    return BallModel::dy;
}

void BallModel::collideX() {
    BallModel::dx *= -1;
}

void BallModel::collideY() {
    BallModel::dy *= -1;
}

void BallModel::simulate_step() {
    BallModel::x += BallModel::dx;
    BallModel::y += BallModel::dy;
}