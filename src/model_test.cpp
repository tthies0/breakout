#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

#include <cmath>

#include "model_simulator_breakout.h"
#include "ball.h"

BOOST_AUTO_TEST_SUITE(ModelTest);

BOOST_AUTO_TEST_CASE(LineIntersection)
{
    BreakoutModel* breakout = new BreakoutModel();

    BOOST_TEST(breakout->intersect(1,0, -1,0, 0,1, 0,-1));
    BOOST_TEST(!breakout->intersect(1,0, 0,-1, 0,1, -1,0));
}

BOOST_AUTO_TEST_CASE(Collision)
{
    BreakoutModel* breakout = new BreakoutModel();

    BreakoutModel::Collision testColl = breakout->getIntersection(1,0, -1,0, 0,1, 0,-1, nullptr);
    
    BOOST_TEST(testColl.x == .0);
    BOOST_TEST(testColl.y == .0);
    
    BOOST_TEST(testColl.surfaceNormalX == 2.);
    BOOST_TEST(testColl.surfaceNormalY == 0.);

    
}

BOOST_AUTO_TEST_CASE(BallReflection)
{
    BreakoutModel* breakout = new BreakoutModel();
    
    double sqrt2 = std::sqrt(.5);
    
    
    Ball ball{-.5, -.5, sqrt2, sqrt2, 2};
    
    BreakoutModel::Collision coll{0., 0., -1., 0., 1, nullptr};
    
    breakout->reflectBall(ball, coll);
    
    BOOST_TEST(ball.getDirectionX() == -sqrt2);
    BOOST_TEST(ball.getDirectionY() == sqrt2);
}

BOOST_AUTO_TEST_SUITE_END()