#include "model_border.h"
#include "model_simulator_breakout.h"

int BorderModel::isCollided(double x, double y) {
    int width = BreakoutModel::gameWidth;
    int height = BreakoutModel::gameHeight;

    if (x < 0 || x > width) {
        return 1;
    } else if (y > height) {
        return 2;
    } else if (y < 0) {
        return 3;
    } else {
        return 0;
    }

}