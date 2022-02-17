

#include <iostream>
#include <cmath>

#include "../include/Polygon.h"
#include "../include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

// gcc main.cpp  Point.cpp Polygon.cpp -lstdc++ -o main.o
// g++ main.cpp  Point.cpp Polygon.cpp -I/usr/include/python2.7 -lpython2.7 -o main.o
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

    std::vector<float> x, y;
    for(auto point : points) {
        x.push_back(point.x);
        y.push_back(point.y);
    }

    // // Set the size of output image to 1200x780 pixels
    plt::figure_size(1200, 780);
    // // Plot line from given x and y data. Color is selected automatically.
    plt::scatter(x, y, 2);
    plt::title("Sample figure");
    plt::legend();
    // plt::save("./basic.png");

    // p.printAllPoints(points);
    auto sortedPoints = p.sortPoints(points);
    // p.printAllPoints(sortedPoints);
    //Check the result
    p.printAllPoints();
    auto result = p.getConvexHullPoints(sortedPoints);
    p.printAllPoints(result);

    std::vector<float> final_x, final_y;
    for(auto point : result) {
        final_x.push_back(point.x);
        final_y.push_back(point.y);
    }
    plt::plot(final_x, final_y);
    plt::show();

} 

// 0.48239 -0.477617
