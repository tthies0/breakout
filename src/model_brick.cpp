#include "model_brick.h"

BrickModel::BrickModel(int width, int x, int y) {
    BrickModel::width = width;
    BrickModel::x = x;
    BrickModel::y = y;
}

bool BrickModel::getIsRemoved() {
    return BrickModel::isRemoved;
}

int BrickModel::isCollided(double x, double y) {

    if (BrickModel::isRemoved) {
        return 0;
    }

    // ToDo Kollision implementieren
    return 0;
}

int BrickModel::getWidth() {
    return BrickModel::width;
}

int BrickModel::getX() {
    return BrickModel::x;
}

int BrickModel::getY() {
    return BrickModel::y;
}