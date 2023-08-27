#ifndef MODEL_BREAKOUT_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_BREAKOUT_H_

#include "observer.h" // include header file for the Observable class
#include "collidable.h"
#include "paddle.h"
#include "brick.h"
#include "ball.h"
#include "KeyAction.h"
#include <vector>

class BreakoutModel : public Observable { // PongModel class inherits from Observable class
public:

    BreakoutModel(); // constructor

    void simulate_game_step(Key::Action ch); // simulates one step of the Pong game

    static constexpr double gameWidth = 100; // game width
    static constexpr double gameHeight = 20; // game height
    static constexpr double startBallSpeed = .5; // starting speed of every ball

    std::vector<Brick> getBricks();
    std::vector<Ball> getBalls();
    Paddle getPaddle();
    int getScore();

private:
    enum GameState{running, lost, won};
    GameState _state;
    int _score = 0;

    struct Collision{ // A calculated Collision with a surface normal
        Collision(double x, double y, double surfaceNormalX, double surfaceNormalY, double distance, Collidable* collidedObject)
            : x(x), y(y), surfaceNormalX(surfaceNormalX), surfaceNormalY(surfaceNormalY), distance(distance), collidedObject(collidedObject){};
        double x;
        double y;
        double surfaceNormalX; //X Part (always normalized)
        double surfaceNormalY; //Y Part (always normalized)
        double distance;
        Collidable* collidedObject;
    };
    std::vector<Brick> _bricks;
    std::vector<Ball> _balls;
    Paddle* _paddle;

    void checkBorder(Ball& ball); //Checks for Collision with border and changes balls direction
    bool checkHandlePaddleCollision(Ball& ball, Paddle paddle); //Checks for and handle collision with paddle for every ball
    void reflectBall(Ball& ball, Collision collision); //Reflects the ball given a Collision
    Collision checkCollisionChangeState(Ball& ball); //Checks all intersections and returns the nearest one, notifies Collidable of collision
    Collision calcIntersect(Ball& ball, Collidable& collidable); //Calculates the Intersection of Ball direction and a single Collidable
    bool intersect(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy);//Checks if two line segments intersect
    bool ccw(double Ax, double Ay, double Bx, double By, double Cx, double Cy);
    Collision getIntersection(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, Collidable* collidedObject);// gets the intersection point of two lines
};

#endif // end of header file
