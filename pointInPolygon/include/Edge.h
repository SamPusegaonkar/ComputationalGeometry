#include "Point.h"

class Edge {
    public:
        std::shared_ptr<Point> vertexA, vertexB;
        Edge();
        Edge( std::unique_ptr<Point>& p1, std::unique_ptr<Point>& p2 );
        Edge( std::shared_ptr<Point>& p1, std::shared_ptr<Point>& p2 );
};