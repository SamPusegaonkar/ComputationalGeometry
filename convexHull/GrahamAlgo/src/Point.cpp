#include "../include/Point.h"

Point::Point( float X, float Y ) {
    x = X;
    y = Y;
    r = sqrt(x*x + y*y);
    if ( x == 0)
        theta_in_radian = 0;
    else
       theta_in_radian = atan(y/x);
}

