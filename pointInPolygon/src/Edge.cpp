#include "../include/Edge.h"


Edge::Edge( std::unique_ptr<Point>& p1, std::unique_ptr<Point>& p2 ) {

    vertexA = std::move(p1);
    vertexB = std::move(p2);
}

Edge::Edge( std::shared_ptr<Point>& p1, std::shared_ptr<Point>& p2 ) {

    vertexA = p1;
    vertexB = p2;
}
