#include "../include/Point.h"

Point::Point( float X, float Y ) {
    x = X;
    y = Y;
    r = sqrt(x*x + y*y);
    if ( y == 0 && x == 0)
        theta_in_radian = 0;
    else
        theta_in_radian = atan2(y,x);
	theta_in_radian = (theta_in_radian*180)/3.141592654;
}

Point::Point() {}
