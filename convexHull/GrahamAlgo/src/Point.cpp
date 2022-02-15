#include "../include/Point.h"

Point::Point( float X, float Y ) {
    x = X;
    y = Y;
    r = sqrt(x*x + y*y);
    theta_in_radian = atan(y/x);
}

