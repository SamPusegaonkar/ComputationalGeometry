#include "Point.h"

class Edge : public Point{
    public:
    Point v1, v2;
    Edge( const std::unique_ptr<Point>& p1, const std::unique_ptr<Point>& p2);

};