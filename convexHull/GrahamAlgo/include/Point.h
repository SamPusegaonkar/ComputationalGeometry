#include <memory>
#include <vector>
#include <cmath>

class Point {
    public:
        float x, y, r = 0, theta_in_radian = 0; // Unit for r doesnt matter
        Point();
        Point( float X, float Y );

};