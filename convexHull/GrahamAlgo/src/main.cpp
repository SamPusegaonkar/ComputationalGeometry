

#include <iostream>
#include "../include/Polygon.h"


// gcc main.cpp  Point.cpp Polygon.cpp -lstdc++ -o main.o
// ./main.o

int main( ) {

    //Read the input file 
    std::string file;
    std::cout << "Type the filename & press enter! (Example: test_case.txt) ";
    std::cin >> file;
    std::string directory = "../input/";
    std::string filename = directory + file;

    Polygon p;
    auto points = p.readFile(filename);
    auto sortedPoints = p.sortPoints(points);
    //Check the result
    p.getConvexHullPoints(sortedPoints);
    p.printAllConvexHullPoints();
    std::cout << "--------------------------------------------------" << "\n";

} 



//plotting
//remove uncessary libs

