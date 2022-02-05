#include "../include/Point.h"

Point::Point( double X, double Y ) {
    x = X;
    y = Y;
}


bool Point::operator==(const Point& other) const {
    if ( other.x == this->x && other.y == this->y)
        return true;
    return false;
}