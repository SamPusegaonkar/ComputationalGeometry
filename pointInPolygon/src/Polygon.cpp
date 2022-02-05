#include <iostream>
#include "../include/Polygon.h"

Polygon::Polygon(std::vector<std::shared_ptr<Edge>> &_edges) {
    this->edges = _edges;
}

int Polygon::isPointInPolygon() {

    std::cout << "Entered main function\n";
    int result = 0;
    for ( auto &edge : edges) {
        std::cout << "Edge!\n";

        int temp_result;
        std::cout << edge->vertexA->x << " " << edge->vertexA->y <<  "!\n";
        std::cout << edge->vertexB->x << " " << edge->vertexB->y << "!\n";

        Polygon::intersectEdge(edge, query_point, temp_result);
        std::cout << "Got the result back from insersect_edge!\n";
        if ( temp_result == 2 )
            return 2;
        
        result += temp_result;
    }

    //Odd - Even Case
    if ( result % 2 == 0)
        return 0;
    return 1;
}

int Polygon::isPointInPolygon(std::vector<std::shared_ptr<Edge>> &_edges, std::shared_ptr<Point> &_query_point) {

    edges = _edges;
    query_point = _query_point;
    isPointInPolygon();
}

int Polygon::intersectEdge(std::shared_ptr<Edge>&edge, std::shared_ptr<Point>&point, int &sub_result) {

    std::cout << "Entered the intersectEdge function!\n";

    //Query Point Coordinates
    auto xp = point->x;
    std::cout << "got xp!\n";

    auto yp = point->y;

    //Vertex A of edge e
    auto x1 = edge->vertexA->x;
    auto y1 = edge->vertexA->y;

    //Vertex A of edge e
    auto x2 = edge->vertexB->x;
    auto y2 = edge->vertexB->y;
    std::cout << "Got points!\n";


    //Case 1 : Edge e is on the left of the ray which points to the right
    if ( x1 < xp and x2 < xp)
        return 0;
    std::cout << "Case 1 over!\n";


    //Case 2 : Edge is Horizontal
    if ( y1 == y2 ) {
        auto x_min = x1 < x2 ? x1 : x2;
        auto x_max = x1 > x2 ? x1 : x2;

        if ( (x_min <= xp and xp <= x_max) and (yp == y1)) {
            sub_result = 2;
            return 2;
        }
        sub_result = 0;
        return 0;
    }
    std::cout << "Case 2 over!\n";


    auto x_intersect = ((yp-y1) / (y2-y1)) * (x2-x1) + x1;
    auto y_min = y1 < y2 ? y1 : y2;
    auto y_max = y1 > y2 ? y1 : y2;

    //Case 3 : Point is on the edge 
    if ( x_intersect == xp and (y_min <= yp and yp <= y_max)) {
        sub_result = 2;
        return 2;

    }
    std::cout << "Case 3 over!\n";


    //Case 4 : Intersection Point (of the ray) is the endpoints of edge
    if ( xp < x1 and yp == y1)
        if ( y1 < y2) {
            sub_result = 1;
            return 1;
        }
        else {
            sub_result = 1;
            return 0;
        }

    if ( xp < x2 and yp == y2)
        if ( y2 < y1) {
            sub_result = 1;
            return 1;

        }
        else {
            sub_result = 0;
            return 0;

        }
    std::cout << "Case 4 over!\n";


    //Case 5 : 
    if ( x_intersect > xp and (y_min < yp < y_max)) {
        sub_result = 1;
        return 1;
    }
    
    sub_result = 0;
    return 0;
    std::cout << "Case 5 over!\n";


}

