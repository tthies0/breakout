#define _USE_MATH_DEFINES

#include "model_simulator_breakout.h"
// #include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#include "paddle.h"
#include "collidable.h"

BreakoutModel::BreakoutModel()
{
    _state = running;
    _paddle = new Paddle{5., 1., BreakoutModel::gameWidth / 2, 2., 0.};
};

void BreakoutModel::simulate_game_step()
{

    
    notifyUpdate();
};

void BreakoutModel::reflectBall(Ball ball, BreakoutModel::Collision collision)
{

    double direction = fmod(ball.getDirection() + (fmod(collision.surfaceNormal - ball.getDirection() + M_PI_2, M_PI * 2)) - M_PI_2, M_PI * 2); // calculate new ball direction
    ball.setDirection(direction);
    double remainingDist = ball.getSpeed() - collision.distance;
    ball.setX(collision.x + remainingDist * cos(direction));
    ball.setX(collision.y + remainingDist * sin(direction));
}

BreakoutModel::Collision *BreakoutModel::checkCollisionChangeState(Ball ball)
{

    Collision *nearestCollision = nullptr;
    for (Brick brick : _bricks)
    {
        if (nearestCollision == nullptr)
        {
            nearestCollision = calcIntersect(ball, brick);
            continue;
        }
        Collision *temp = calcIntersect(ball, brick);
        if (temp->distance < nearestCollision->distance)
        {
            nearestCollision = temp;
        }
    }
    if (nearestCollision == nullptr)
    {
        return nullptr;
    }
    nearestCollision->collidedObject->handleCollision();
    reflectBall(ball, *nearestCollision);
    return nearestCollision;
}

BreakoutModel::Collision *BreakoutModel::calcIntersect(Ball ball, Collidable collidable)
{
    Collision *nearestIntersect = nullptr;

    double ball_currentX = ball.getX();
    double ball_currentY = ball.getY();

    double ball_nextX = ball.getX() + cos(ball.getDirection()) * ball.getSpeed();
    double ball_nextY = ball.getY() + sin(ball.getDirection()) * ball.getSpeed();

    // BL : bottom left, TL : top left, TR : top right, BR : bottom right
    double blX = collidable.getX();
    double blY = collidable.getY();

    double tlX = collidable.getX() + cos(collidable.getRotation() + M_PI_2) * collidable.getHeight();
    double tlY = collidable.getY() + sin(collidable.getRotation() + M_PI_2) * collidable.getHeight();

    double trX = tlX + cos(collidable.getRotation()) * collidable.getWidth();
    double trY = tlY + sin(collidable.getRotation()) * collidable.getWidth();

    double brX = collidable.getX() + cos(collidable.getRotation()) * collidable.getWidth();
    double brY = collidable.getY() + sin(collidable.getRotation()) * collidable.getWidth();

    // left:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, blX, blY, tlX, tlY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, blX, blY, tlX, tlY);
        nearestIntersect = &temp;
        nearestIntersect->surfaceNormal = M_PI + collidable.getRotation();
    }
    // top:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, tlX, tlY, trX, trY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, tlX, tlY, trX, trY);
        if (temp.distance < nearestIntersect->distance)
        {
            nearestIntersect = &temp;
            nearestIntersect->surfaceNormal = M_PI_2 + collidable.getRotation();
        }
    }
    // right:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, trX, trY, brX, brY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, trX, trY, brX, brY);
        if (temp.distance < nearestIntersect->distance)
        {
            nearestIntersect = &temp;
            nearestIntersect->surfaceNormal = collidable.getRotation();
        }
    }
    // bottom:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, brX, brY, blX, blY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, brX, brY, blX, blY);
        if (temp.distance < nearestIntersect->distance)
        {
            nearestIntersect = &temp;
            nearestIntersect->surfaceNormal = 2 * M_PI_2 + collidable.getRotation();
        }
    }
    if (nearestIntersect == nullptr)
    {
        return nearestIntersect;
    }
    nearestIntersect->collidedObject = &collidable;
    return nearestIntersect;
}

// Calculates the intersections of two lines
BreakoutModel::Collision BreakoutModel::getIntersection(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy)
{
    double rX = Bx - Ax;
    double rY = By - Ay;
    double sX = Dx - Cx;
    double sY = Dy - Cy;

    double acX = Cx - Ax;
    double acY = Cy - Ay;

    double distOnAB = (acX * sY - acY * sX) / (rX * sY - rY * sX);

    double collisionX = Ax + distOnAB * rX;
    double collisionY = Ay + distOnAB * rY;

    Collision collision{collisionX, collisionY, 0., distOnAB, nullptr};

    return collision;
}

// From https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
// Checks if two line segments collide
bool BreakoutModel::intersect(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy)
{
    if (abs((Bx - Ax) / (By - Ay)) == abs((Dx - Cx) / (Dy - Cy)))
    { // False when the two line segments are parallel
        return false;
    }
    return ccw(Ax, Ay, Cx, Cy, Dx, Dy) != ccw(Bx, By, Cx, Cy, Dx, Dy) and ccw(Ax, Ay, Bx, By, Cx, Cy) != ccw(Ax, Ay, Bx, By, Dx, Dy);
};
// From https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
bool BreakoutModel::ccw(double Ax, double Ay, double Bx, double By, double Cx, double Cy)
{
    return (Cy - Ay) * (Bx - Ax) > (By - Ay) * (Cx - Ax);
};