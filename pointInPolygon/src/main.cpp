#include <iostream>
#include "../include/Polygon.h"


// gcc main.cpp  Point.cpp Edge.cpp Polygon.cpp -lstdc++ -o main.o
// ./main.o

int main( ) {

    //Read the input file 
    Polygon p2;
    std::string file;
    std::cout << "Type the filename & press enter! (Example: test_case.txt) ";
    std::cin >> file;
    std::string directory = "../input/";
    std::string filename = directory + file;
    if (p2.readFile(filename) == -1) 
        return -1; 

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

//plotting
//remove uncessary libs

