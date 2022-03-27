

#include <iostream>
#include <cmath>

#include "../include/Polygon.h"
#include "../include/matplotlibcpp.h"

namespace plt = matplotlibcpp;

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

    plt::figure_size(1200, 780);

    //Printing all points
    plt::scatter(x, y, 2);
    plt::title("Sample figure");
    plt::legend();

    auto sortedPoints = p.sortPoints(points);
    // p.printAllPoints();
    auto result = p.getConvexHullPoints(sortedPoints);
    // p.printAllPoints(result);

    //Printing all convex hull points
    std::vector<float> final_x, final_y;
    for(auto point : result) {
        final_x.push_back(point.x);
        final_y.push_back(point.y);
    }
    plt::plot(final_x, final_y);
    plt::show();

} 
