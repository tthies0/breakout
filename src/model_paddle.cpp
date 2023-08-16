#include "model_paddle.h"
#include "model_simulator_breakout.h"

PaddleModel::PaddleModel(int start) {
    PaddleModel::position = start;
}

void PaddleModel::movePaddleLeft() {

    if (PaddleModel::position > 0) {
        PaddleModel::position -= 1;
    }

}

void PaddleModel::movePaddleRight() {

    if (PaddleModel::position + PaddleModel::width < BreakoutModel::gameWidth) {
        PaddleModel::position += 1;
    }

}

int PaddleModel::isCollided(double x, double y) {
    // ToDo implementieren
    return 0;
}