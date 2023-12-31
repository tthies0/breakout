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
    enum GameState{running, lost, won};
    BreakoutModel(); // constructor

    void simulate_game_step(Key::Action ch); // simulates one step of the Pong game

    static constexpr double gameWidth = 80; // game width
    static constexpr double gameHeight = 25; // game height
    static constexpr double startBallSpeed = 1.2; // starting speed of every ball
    static constexpr double verticalNerf = .5; // because vertical distance between chars is bigger

    std::vector<Brick> getBricks();
    std::vector<Ball> getBalls();
    Paddle getPaddle();
    int getScore();
    GameState getState();
    
    struct Collision{ // A calculated Collision with a surface normal
        Collision(double x, double y, double surfaceNormalX, double surfaceNormalY, double distance, Collidable* collidedObject)
            : x(x), y(y), surfaceNormalX(surfaceNormalX), surfaceNormalY(surfaceNormalY), distance(distance), collidedObject(collidedObject){};
        double x;
        double y;
        double surfaceNormalX; //X Part (may be normalized)
        double surfaceNormalY; //Y Part (may be normalized)
        double distance;
        Collidable* collidedObject;
    };
    
    bool intersect(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy);//Checks if two line segments intersect
    Collision getIntersection(double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, Collidable* collidedObject);// gets the intersection point of two lines
    
    void reflectBall(Ball& ball, Collision collision); //Reflects the ball given a Collision
    
    
private:
    GameState _state;
    int _score = 0;

    std::vector<Brick> _bricks;
    std::vector<Ball> _balls;
    Paddle* _paddle;

    void checkBorder(Ball& ball); //Checks for Collision with border and changes balls direction
    bool checkHandlePaddleCollision(Ball& ball, Paddle paddle); //Checks for and handle collision with paddle for every ball
    Collision checkCollisionChangeState(Ball& ball); //Checks all intersections and returns the nearest one, notifies Collidable of collision
    Collision calcIntersect(Ball& ball, Collidable& collidable); //Calculates the Intersection of Ball direction and a single Collidable
    bool ccw(double Ax, double Ay, double Bx, double By, double Cx, double Cy);
};

#endif // end of header file
