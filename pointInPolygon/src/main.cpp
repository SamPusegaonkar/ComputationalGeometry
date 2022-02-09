

#include <iostream>
#include "../include/Polygon.h"


// gcc main.cpp  Point.cpp Edge.cpp Polygon.cpp -lstdc++ -o main.o
// ./main.o
///1 == inside
///2 == on the edge
///0 == outside


int main( ) {

    //Read the input file 
    std::string file;
    std::cout << "Type the filename & press enter! (Example: test_case.txt) ";
    std::cin >> file;
    std::string directory = "../input/";
    std::string filename = directory + file;

    Polygon p;
    if (p.readFile(filename) == -1) 
        return -1; 

    //Taking Query Input
    float query_x, query_y;
    std::cout << "Type the x - coordinate of the query point & press enter! ";
    std::cin >>  query_x;
    std::cout << "Type the y - coordinate of the query point & press enter! ";
    std::cin >>  query_y;
    p.setQueryPoint(query_x, query_y);

    //Check the result
    auto final = p.isPointInsidePolygon();
    std::cout << "The result is: " << final << "\n";    
    if ( final == 0)
        std::cout << "The query point is outside the polygon!" << "\n";    
    else if( final == 2 )
        std::cout << "The query point is on the polygon!" << "\n";   
    else if( final == 1 )
        std::cout << "The query point is inside the polygon!" << "\n";   
    std::cout << "--------------------------------------------------" << "\n";

} 



//plotting
//remove uncessary libs

