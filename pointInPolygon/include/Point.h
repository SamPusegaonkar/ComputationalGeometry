#include <memory>


class Point {
    public:
    double x, y;
    Point( double X, double Y );
    bool operator==(const std::unique_ptr<Point>& other) const;
    bool operator==(const Point& other) const;


   
};