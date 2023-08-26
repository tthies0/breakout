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
    _paddle = new Paddle{5, 1, BreakoutModel::gameWidth / 2, 1, 0};
    _border = new Border{BreakoutModel::gameWidth, BreakoutModel::gameHeight+5, 0, -5, 0};
    Ball b{10, 10, sqrt(.5), sqrt(.5), .5};
    _balls.emplace_back(b);
    
};

void BreakoutModel::simulate_game_step(Controller::KeyAction ch)
{
    if(ch == Controller::action_right){
        _paddle->setX(_paddle->getX() + _paddle->getPaddleSpeed());
    }
    if(ch == Controller::action_right){
        _paddle->setX(_paddle->getX() - _paddle->getPaddleSpeed());
    }

    for(Ball& ball : _balls){
        if(ball.getSpeed() == 0.){
            ball.setX(_paddle->getX());
            ball.setY(_paddle->getY()+1);

            if(ch == Controller::action_shoot){
                ball.setDirectionX(0);
                ball.setDirectionY(1);
                ball.setSpeed(startBallSpeed);
            }
        }

        if(checkBorder(ball)){
            continue;
        }
        if(checkHandlePaddleCollision(ball, *_paddle)){
            continue;
        }
        if(checkCollisionChangeState(ball)!=nullptr){
            continue;
        }
        ball.setX(ball.getX() + ball.getSpeed() * ball.getDirectionX());
        ball.setY(ball.getY() + ball.getSpeed() * ball.getDirectionY());
    }
    
    notifyUpdate();
};

std::vector<Brick> BreakoutModel::getBricks(){
    return _bricks;
}
std::vector<Ball> BreakoutModel::getBalls(){
    return _balls;
}

Paddle BreakoutModel::getPaddle(){
    return *_paddle;
}

bool BreakoutModel::checkHandlePaddleCollision(Ball& ball, Paddle paddle){
    Collision* coll = calcIntersect(ball, paddle);
    if(coll==nullptr){
        return false;
    }
    ball.setDirectionY(-ball.getDirectionY());
    ball.setDirectionX((paddle.getX()-ball.getX())/paddle.getWidth()*3);
    return true;
}

bool BreakoutModel::checkBorder(Ball& ball){
    //TODO: Implement game loss by not hitting ball with paddle
    Collision* coll = calcIntersect(ball, *_border);
    if(coll==nullptr){
        return false;
    }
    reflectBall(ball, *coll);
    return true;
}

void BreakoutModel::reflectBall(Ball& ball, BreakoutModel::Collision collision)
{
    double dot = ball.getDirectionX() * collision.surfaceNormalX + ball.getDirectionY() * collision.surfaceNormalY;

    ball.setDirectionX(ball.getDirectionX() - 2 * collision.surfaceNormalX * dot);
    ball.setDirectionY(ball.getDirectionY() - 2 * collision.surfaceNormalY * dot);

    //Normalize for safety
    dot = ball.getDirectionX() * ball.getDirectionX() + ball.getDirectionY() * ball.getDirectionY();

    ball.setDirectionX(ball.getDirectionX()/sqrt(dot));
    ball.setDirectionY(ball.getDirectionY()/sqrt(dot));

    double remainingDist = ball.getSpeed() - collision.distance;
    ball.setX(collision.x + (remainingDist + .5) * ball.getDirectionX());
    ball.setY(collision.y + (remainingDist + .5) * ball.getDirectionY());
}

BreakoutModel::Collision *BreakoutModel::checkCollisionChangeState(Ball& ball)
{

    Collision *nearestCollision = nullptr;
    for (Brick& brick : _bricks)
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

BreakoutModel::Collision *BreakoutModel::calcIntersect(Ball& ball, Collidable collidable)
{
    Collision *nearestIntersect = nullptr;

    double ball_currentX = ball.getX();
    double ball_currentY = ball.getY();

    double ball_nextX = ball.getX() + ball.getDirectionX() * ball.getSpeed();
    double ball_nextY = ball.getY() + ball.getDirectionY() * ball.getSpeed();

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
    }
    // top:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, tlX, tlY, trX, trY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, tlX, tlY, trX, trY);
        if (nearestIntersect == nullptr || temp.distance < nearestIntersect->distance)
        {
            nearestIntersect = &temp;
        }
    }
    // right:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, trX, trY, brX, brY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, trX, trY, brX, brY);
        if (nearestIntersect == nullptr || temp.distance < nearestIntersect->distance)
        {
            nearestIntersect = &temp;
        }
    }
    // bottom:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, brX, brY, blX, blY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, brX, brY, blX, blY);
        if (nearestIntersect == nullptr || temp.distance < nearestIntersect->distance)
        {
            nearestIntersect = &temp;
        }
    }
    if (nearestIntersect == nullptr)
    {
        return nearestIntersect;
    }
    nearestIntersect->collidedObject = &collidable;
    return nearestIntersect;
}

// Calculates the intersections of two lines, returns Collision with collision coordinates and normal from the CD segment
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

    Collision collision{collisionX, collisionY, -sY, sX, distOnAB, nullptr};

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