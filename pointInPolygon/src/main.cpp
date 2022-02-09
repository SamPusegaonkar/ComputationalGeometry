#include <iostream>

#include "../include/Polygon.h"


// gcc main.cpp  Point.cpp Edge.cpp Polygon.cpp -lstdc++ -o main.o
// ./main.o



int main( ) {

    // std::shared_ptr<Point> point1 = std::make_shared<Point>(-2, -2);
    // std::shared_ptr<Point> point2 = std::make_shared<Point>(-2, 2);
    // std::shared_ptr<Point> point3 = std::make_shared<Point>(2, 2);
    // std::shared_ptr<Point> point4 = std::make_shared<Point>(2, -2);
    // std::cout << point1->x << " " << point1->y << "\n";
    // auto result = *point1 == *point2;
    // std::cout << result << "\n";

    // std::cout << "--------------------------------------------------" << "\n";
    // std::shared_ptr<Edge> edge1 = std::make_shared<Edge>(point1, point2);
    // std::cout << edge1->vertexA->x << " " << edge1->vertexA->x << "\n";
    // std::cout << edge1->vertexB->x << " " << edge1->vertexB->x << "\n";
    // std::cout << "--------------------------------------------------" << "\n";
    // std::shared_ptr<Edge> edge2 = std::make_shared<Edge>(point2, point3);
    // std::cout << edge2->vertexA->x << " " << edge2->vertexA->x << "\n";
    // std::cout << edge2->vertexB->x << " " << edge2->vertexB->x << "\n";
    // std::cout << "--------------------------------------------------" << "\n";
    // std::shared_ptr<Edge> edge3 = std::make_shared<Edge>(point3, point4);
    // std::cout << edge3->vertexA->x << " " << edge3->vertexA->x << "\n";
    // std::cout << edge3->vertexB->x << " " << edge3->vertexB->x << "\n";
    // std::cout << "--------------------------------------------------" << "\n";
    // std::shared_ptr<Edge> edge4 = std::make_shared<Edge>(point4, point1);
    // std::cout << edge4->vertexA->x << " " << edge4->vertexA->x << "\n";
    // std::cout << edge4->vertexB->x << " " << edge4->vertexB->x << "\n";
    // std::cout << "--------------------------------------------------" << "\n";

    // std::vector<std::shared_ptr<Edge>> edges;
    // edges.push_back(edge1);
    // edges.push_back(edge2);
    // edges.push_back(edge3);
    // edges.push_back(edge4);

    // Polygon p(edges);
    // p.setQueryPoint(2.0,2.0);
    // auto final = p.isPointInsidePolygon();
    // std::cout << "The result is: " << final;    
    // std::cout << "--------------------------------------------------" << "\n";


    //Read the input file 
    Polygon p2;
    std::string file;
    std::cout << "Type the filename & press enter! (Example: test_case.txt) ";
    std::cin >> file;
    std::string directory = "../input/";
    std::string filename = directory + file;
    if (p2.readFile(filename) == -1) 
        return -1; 

    // for ( auto edge : p2.edges) {
    //     std::cout<< "hereA\n";
    //     std::cout<< edge->vertexA->x << " " << edge->vertexA->y << "\n";
    //     std::cout<< edge->vertexB->x << " " << edge->vertexB->y << "\n";
    //     std::cout<< "hereB\n";
    // }

    //Taking Query Input
    float query_x, query_y;
    std::cout << "Type the x - coordinate of the query point & press enter! ";
    std::cin >>  query_x;
    std::cout << "Type the y - coordinate of the query point & press enter! ";
    std::cin >>  query_y;
    p2.setQueryPoint(query_x, query_y);

    //Check the result
    auto final = p2.isPointInsidePolygon();
    std::cout << "The result is: " << final << "\n";    
    std::cout << "--------------------------------------------------" << "\n";

} 


///1 == inside
///2 == on the edge
///0 == outside


//== operator
//floating point issue!
//plotting
//remove uncessary libs

