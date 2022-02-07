#include <iostream>
#include <fstream>
#include <sstream>

#include "../include/Polygon.h"

Polygon::Polygon() {}

Polygon::Polygon(std::vector<std::shared_ptr<Edge>> &_edges) {
    this->edges = _edges;
}

void Polygon::setQueryPoint( double X, double Y) {
    this->query_point = std::make_shared<Point>(X,Y);
}

int Polygon::readFile(std::string& filename) {
    std::fstream myfile(filename, std::ios_base::in);

    if (!myfile) {
        std::cerr << "Error: Could not find the requested file!\n";
        return -1;
    }

    std::string line;
    int number_of_lines = 0;
    if (getline(myfile, line)) 
        number_of_lines = std::stoi(line);
    
    if ( number_of_lines <= 0) {
        std::cout << "Number of lines is less than or equal to 0\n";
        return -1;
    }

    std::vector<Point> points;
    // std::cout<<number_of_lines<< " :Number of lines \n";
    int counter = 0;
    std::string linetxt;
    while (std::getline(myfile, linetxt)){
        std::istringstream iss(linetxt);
        double a, b;
        if (!(iss >> a >> b)) { 
            std::cout << "There is something wrong with the input file!\n";
            return -1; 
        } 
        // std::cout<< a << " " << b<< "\n";
        counter++;
        points.push_back(Point(a, b));    
    }

    convertPointToEdges(points);
}

void Polygon::convertPointToEdges(std::vector<Point>&points) {

    std::vector<std::shared_ptr<Edge>> _edges;
    int n = points.size();

    for ( int i = 0; i < n; i++) {
        
        std::shared_ptr<Point> p1 = std::make_shared<Point>(points[i].x, points[i].y);
        std::shared_ptr<Point> p2 = std::make_shared<Point>(points[(i+1)%n].x, points[(i+1)%n].y);

        std::shared_ptr<Edge> edge = std::make_shared<Edge>(p1, p2);
        _edges.push_back(edge);
    }

    edges = _edges;
}



int Polygon::isPointInsidePolygon() {

    // std::cout << "Entered main function\n";
    int result = 0;
    for ( auto &edge : edges) {
        // std::cout << "Edge!\n";

        int temp_result = 0;
        
        Polygon::intersectEdge(edge, query_point, temp_result);
        std::cout << "Edge: ";
        std::cout << "("<< edge->vertexA->x << ", " << edge->vertexA->y << ") ";
        std::cout << "("<< edge->vertexB->x << ", " << edge->vertexB->y << ")";
        std::cout << ", intersection: " << temp_result << "\n";

        if ( temp_result == 2 )
            return 2;
        
        result += temp_result;
    }

    //Odd - Even Case
    if ( result % 2 == 0)
        return 0;
    return 1;
}

int Polygon::isPointInsidePolygon(std::vector<std::shared_ptr<Edge>> &_edges, std::shared_ptr<Point> &_query_point) {

    edges = _edges;
    query_point = _query_point;
    isPointInsidePolygon();
}

int Polygon::intersectEdge( std::shared_ptr<Edge> &edge, std::shared_ptr<Point>&point, int &sub_result) {

    // std::cout << "Entered the intersectEdge function!\n";

    //Query Point Coordinates
    auto xp = point->x;
    auto yp = point->y;
    // std::cout << xp << " " << yp << "\n";


    //Vertex A of edge e
    auto x1 = edge->vertexA->x;
    auto y1 = edge->vertexA->y;
    // std::cout << x1 << " " << y1 << "\n";


    //Vertex A of edge e
    auto x2 = edge->vertexB->x;
    auto y2 = edge->vertexB->y;
    // std::cout << x2 << " " << y2 << "\n";

    // std::cout << "Got points!\n";


    //Case 1 : Edge e is on the left of the ray which points to the right
    if ( (x1 < xp && x2 < xp) ) {
        std::cout<<"Case 1-0\n";
        sub_result = 0;
        return 0;

    }
        
    // std::cout << "Case 1 over!\n";


    //Case 2 : Edge is Horizontal
    if ( y1 == y2 ) {
        std::cout<<"Case 2\n";
        auto x_min = x1 < x2 ? x1 : x2;
        auto x_max = x1 > x2 ? x1 : x2;

        if ( (x_min <= xp && xp <= x_max) and (yp == y1)) {
            std::cout<<"Case 2 - 2\n";
            sub_result = 2;
            return 2;
        }
        else {
            std::cout<<"Case 2-0\n";
            sub_result = 0;
            return 0;
        }
    }
    // std::cout << "Case 2 over!\n";


    auto x_intersect = ((yp-y1) / (y2-y1)) * (x2-x1) + x1;
    auto y_min = y1 < y2 ? y1 : y2;
    auto y_max = y1 > y2 ? y1 : y2;

    //Case 3 : Point is on the edge 
    if ( x_intersect == xp and (y_min <= yp and yp <= y_max)) {
        std::cout<<"Case 3-2\n";
        sub_result = 2;
        return 2;

    }
    // std::cout << "Case 3 over!\n";


    //Case 4 : Intersection Point (of the ray) is the endpoints of edge
    if ( xp < x1 and yp == y1){
        if ( y1 < y2) {
            std::cout<<"Case 4-1\n";
            sub_result = 1;
            return 1;
        }
        else {
            std::cout<<"Case 4-0\n";
            sub_result = 0;
            return 0;
        }
    }

    if ( xp < x2 and yp == y2) {
        if ( y2 < y1) {
            std::cout<<"Case 4-1\n";
            sub_result = 1;
            return 1;

        }
        else {
            std::cout<<"Case 4-0\n";
            sub_result = 0;
            return 0;

        }
    }

    // std::cout << "Case 4 over!\n";


    //Case 5 : 
    if ( x_intersect > xp and (y_min < yp and yp < y_max)) {
        std::cout<<"Case 5-1\n";
        sub_result = 1;
        return 1;
    } else{
        std::cout<<"Case 5-0\n";
        sub_result = 0;
        return 0;
    }
    
    // std::cout << "Case 5 over!\n";


    if ( (xp > x2 and xp > x1) or (xp < x1 and xp < x2)) {
        std::cout<<"Case Extra Check-0\n";
        sub_result = 0;
        return 0;
    }

}