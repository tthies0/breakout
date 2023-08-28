#ifndef BREAKOUT_COLLIDABLE_H
#define BREAKOUT_COLLIDABLE_H

class Collidable {
public:
    Collidable(double width, double height, double x, double y, double rotation)
        :_width(width), _height(height), _x(x), _y(y), _rotation(rotation){};

    double getWidth();
    double getHeight();
    double getX();
    double getY();
    double getRotation();
    void setWidth(double width);
    void setHeight(double height);
    void setX(double x);
    void setY(double y);
    void setRotation(double rotation);

    virtual int handleCollision();

private:
    double _width;
    double _height;
    double _x;
    double _y;
    double _rotation; //Rotation around bottom left corner, from 0 to 2 Pi
};

#endif //BREAKOUT_COLLIDABLE_H
