#include <memory>


class Point {
    public:
    double x, y;
    Point( double X, double Y );
    bool operator==(const Point& other) const;

};