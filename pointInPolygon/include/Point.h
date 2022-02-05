#include <memory>
#include <vector>

class Point {
    public:
        double x, y;
        Point();
        Point( double X, double Y );
        bool operator==(const Point& other) const;

};