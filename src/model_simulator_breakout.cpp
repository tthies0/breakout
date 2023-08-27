#define _USE_MATH_DEFINES

#include "model_simulator_breakout.h"
// #include <ncurses.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "paddle.h"
#include "collidable.h"
#include "brick.h"

BreakoutModel::BreakoutModel()
{
    srand(static_cast <unsigned> (time(0)));
    

    _state = running;
    _paddle = new Paddle{30, 1, BreakoutModel::gameWidth / 2, 1, 0, 4};
    Ball b{10, 10, 0, 1, 0};
    _balls.emplace_back(b);

    
    for(int i = 0; i<16; i++){
        for(int j = 0; j<4; j++){
            int state = 1;
            double randomFloat = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
            if(randomFloat<.1){
                state=3;
            }
            if(randomFloat>.9){
                state=2;
            }
           _bricks.emplace_back(Brick{4.999, 2, i*5, j*3+13, 0, state}); 
        }
    }
    
};

void BreakoutModel::simulate_game_step(Key::Action ch)
{
    int highestBall = 0;
    if(_state!=running){
        return;
    }

    if(ch == Key::action_right){
        _paddle->setX(_paddle->getX() + _paddle->getPaddleSpeed());
    }
    if(ch == Key::action_left){
        _paddle->setX(_paddle->getX() - _paddle->getPaddleSpeed());
    }
    for(Ball& ball : _balls){
        highestBall = fmax(highestBall, ball.getY());

        if(ball.getSpeed() == 0.){
            ball.setX(_paddle->getX() + _paddle->getWidth()/2);
            ball.setY(_paddle->getY()+2);

            if(ch == Key::action_shoot){
                ball.setDirectionX(0);
                ball.setDirectionY(1);
                ball.setSpeed(startBallSpeed);
            }
        }

        checkBorder(ball);
        if(checkHandlePaddleCollision(ball, *_paddle)){
            continue;
        }
        if(checkCollisionChangeState(ball).collidedObject!=nullptr){
            continue;
        }
        ball.setX(ball.getX() + ball.getSpeed() * ball.getDirectionX());
        ball.setY(ball.getY() + verticalNerf * ball.getSpeed() * ball.getDirectionY());
    }
    if(highestBall<0 && _state!=won){
        _state = lost;
    }
    

    notifyUpdate();
};

BreakoutModel::GameState BreakoutModel::getState(){
    return _state;
}

int BreakoutModel::getScore(){
    return _score;
}

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
    Collision coll = calcIntersect(ball, paddle);
    if(coll.collidedObject==nullptr){
        return false;
    }
    ball.setDirectionX(-(paddle.getX() + paddle.getWidth()/2 -ball.getX())/(paddle.getWidth()*.5));
    ball.setDirectionY(sqrt(1-pow(ball.getDirectionX(),2)));
    return true;
}

void BreakoutModel::checkBorder(Ball& ball){
    if(ball.getX()<0 || ball.getX()>gameWidth){
        ball.setDirectionX(ball.getDirectionX() * -1);
    }
    if(ball.getY()>gameHeight){
        ball.setDirectionY(ball.getDirectionY() * -1);
    }

    //Safety so that the ball doesnt bounce left and right indefinitely
    if(abs(ball.getDirectionY())<0.05){
        ball.setDirectionY(sqrt(1/10));
        ball.setDirectionX(sqrt(9/10));
    }


}

void BreakoutModel::reflectBall(Ball& ball, BreakoutModel::Collision collision)
{
    //Normalize surface normal
    double normalLength = sqrt(collision.surfaceNormalX * collision.surfaceNormalX + collision.surfaceNormalY * collision.surfaceNormalY);
    double normalX = collision.surfaceNormalX / normalLength;
    double normalY = collision.surfaceNormalY / normalLength;

    double dot = ball.getDirectionX() * normalX + ball.getDirectionY() * normalY;

    ball.setDirectionX(ball.getDirectionX() - 2 * normalX * dot);
    ball.setDirectionY(ball.getDirectionY() - 2 * normalY * dot);

    //Normalize for safety
    dot = ball.getDirectionX() * ball.getDirectionX() + ball.getDirectionY() * ball.getDirectionY();

    ball.setDirectionX(ball.getDirectionX()/sqrt(dot));
    ball.setDirectionY(ball.getDirectionY()/sqrt(dot));

    

    double remainingDist = ball.getSpeed() - collision.distance;
    ball.setX(collision.x + (remainingDist + .5) * ball.getDirectionX());
    ball.setY(collision.y + verticalNerf * (remainingDist + .5) * ball.getDirectionY());
}

BreakoutModel::Collision BreakoutModel::checkCollisionChangeState(Ball& ball)
{
    bool maybeWon = true;
    Collision nearestCollision{0,0,0,0,0,nullptr};
    for (Brick& brick : _bricks)
    {
        if(brick.getState()==0){
            continue;
        }
        maybeWon = false;
        Collision temp = calcIntersect(ball, brick);
        if(temp.collidedObject==nullptr){
            continue;
        }
        if (nearestCollision.collidedObject == nullptr)
        {
            nearestCollision = temp;
            continue;
        }
        
        if (temp.distance < nearestCollision.distance)
        {
            nearestCollision = temp;
        }
    }
    if(maybeWon){
        _state = won;
    }
    if (nearestCollision.collidedObject == nullptr)
    {
        return nearestCollision;
    }
    int action = nearestCollision.collidedObject->handleCollision();
    reflectBall(ball, nearestCollision);
    
    switch (action)
    {
    case(1):
        _score++;
        break;
    case(2):
        break;
    case(3):
        _score++;
        _balls.emplace_back(Ball{nearestCollision.x, nearestCollision.y, 0, -1, startBallSpeed});
        break;
    default:
        break;
    }
    return nearestCollision;
}

BreakoutModel::Collision BreakoutModel::calcIntersect(Ball& ball, Collidable& collidable)
{
    Collision nearestIntersect{0,0,0,0,0,nullptr};

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
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, blX, blY, tlX, tlY, &collidable);
        nearestIntersect = temp;
    }

    // top:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, tlX, tlY, trX, trY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, tlX, tlY, trX, trY, &collidable);
        if (nearestIntersect.collidedObject == nullptr || temp.distance < nearestIntersect.distance)
        {
            nearestIntersect = temp;
        }
    }
    // right:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, trX, trY, brX, brY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, trX, trY, brX, brY, &collidable);
        if (nearestIntersect.collidedObject == nullptr || temp.distance < nearestIntersect.distance)
        {
            nearestIntersect = temp;
        }
    }
    // bottom:
    if (intersect(ball_currentX, ball_currentY, ball_nextX, ball_nextY, brX, brY, blX, blY))
    {
        Collision temp = getIntersection(ball_currentX, ball_currentY, ball_nextX, ball_nextY, brX, brY, blX, blY, &collidable);
        if (nearestIntersect.collidedObject == nullptr || temp.distance < nearestIntersect.distance)
        {
            nearestIntersect = temp;
            
        }
    }
    if (nearestIntersect.collidedObject == nullptr)
    {
        return nearestIntersect;
    }
    return nearestIntersect;
}

// Calculates the intersections of two lines, returns Collision with collision coordinates and normal from the CD segment
BreakoutModel::Collision BreakoutModel::getIntersection(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, Collidable* collidedObject)
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

    Collision collision{collisionX, collisionY, -sY, sX, distOnAB, collidedObject};

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