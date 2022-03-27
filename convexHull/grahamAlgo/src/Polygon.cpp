#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <map>
#include <stack>
#include "../include/Polygon.h"

Polygon::Polygon() {}

bool customComparator (Point& a, Point& b) { 
    if ( a.theta_in_radian == b.theta_in_radian)
        return a.r < b.r;
    return a.theta_in_radian < b.theta_in_radian; 
}

std::vector<Point> Polygon::sortPoints(std::vector<Point>&points) {
    sort(points.begin(), points.end(), customComparator);
    allPoints = points;
    return points;
}

Point Polygon::getBottomRightMostPoint(std::vector<Point>&points) {
    float minYCord = std::numeric_limits<float>::max();

    for ( auto point : points) {
        if ( point.y < minYCord) {
            minYCord = point.y;
        }
    }

    std::map<float, std::vector<Point>> bottomMostPoints;

    for ( auto point : points) {
        if ( isEqual(point.y, minYCord)) {
            bottomMostPoints[minYCord].push_back(point);
        }
    }
    std::cout << "The bottomost point is: ";
    std::cout<< bottomMostPoints[minYCord][0].x << " " << bottomMostPoints[minYCord][0].y << "\n";
    return bottomMostPoints[minYCord][0];
}

int Polygon::getIndexofBottomRightMostPoint(Point& bottomMostPoint, std::vector<Point>&points) {
    
    for ( int i = 0; i < points.size(); i++) {
        auto point = points[i];
        if ( isEqual(point.x, bottomMostPoint.x) && isEqual(point.y, bottomMostPoint.y))
            return i;
    }
    return -1;
}


bool Polygon::isEqual(float a, float b) {
    if ( fabs(a-b) < 0.0001){
        //std::cout << "Correct";
        return true;
    }
    return false;
}

void Polygon::printAllPoints() {
    
    for ( auto point : allPoints) {
        std::cout<< point.x << " " << point.y << " " << point.theta_in_radian << "\n";
    }
    std::cout<< "----------------------------------------\n";
}

void Polygon::printAllPoints( std::vector<Point>& points) {
    
    for ( auto point : points) {
        std::cout<< point.x << " " << point.y << " " << point.theta_in_radian << "\n";
    }
    std::cout<< "----------------------------------------\n";
}

void Polygon::printConvexHullPoints() {
    
    for ( auto point : convexHullPoints) {
        std::cout<< point.x << " " << point.y << " " << point.theta_in_radian << "\n";
    }
    std::cout<< "----------------------------------------\n";
}

bool Polygon::isLessThanOrEqual(float a, float b) {
    //Order of the parameter matters!

    if ( a < b || fabs(a-b) < 0.0001){
        //std::cout << "Correcthiiiii\n";
        return true;
    }
    return false;
}


std::vector<Point> Polygon::readFile(std::string& filename) {
    std::fstream myfile(filename, std::ios_base::in);
    std::vector<Point> points;

    if (!myfile) {
        std::cerr << "Error: Could not find the requested file!\n";
        return points; //Error
    }

    std::string line;
    int number_of_lines = 0;
    if (getline(myfile, line)) 
        number_of_lines = std::stoi(line);

    if ( number_of_lines <= 0) {
        std::cerr << "Number of lines is less than or equal to 0\n";
        return points; //Error
    }

    // std::cout<<number_of_lines<< " :Number of lines \n";
    int counter = 1;
    std::string linetxt;
    while (std::getline(myfile, linetxt)){
        std::istringstream iss(linetxt);
        float a, b;
        if ( counter > number_of_lines) continue;
        if (!(iss >> a >> b) && counter <= number_of_lines ) { 
            std::cout << counter << ":Counter\n";
            std::cerr << "There is something wrong with the input file!\n";
            return points; //Error
        } 

        // std::cout<< a << " " << b<< "\n";
        counter++;
        points.push_back(Point(a, b));
        // std::cout << "Reading Line\n";    
    }
    std::cout << "Completed reading line\n";
    return points;
    
}

bool Polygon::isPointOrientedCorrectly(Point& p1, Point& p2, Point& p3) {

    auto p3p1X = p1.x - p3.x;
    auto p3p1Y = p1.y - p3.y;
    auto p3p2X = p2.x - p3.x;
    auto p3p2Y = p2.y - p3.y;

    auto determinent = (p3p1X * p3p2Y ) - (p3p1Y *p3p2X );
    // std::cout<< "The determinent is " << determinent << "\n";
    if (determinent < 0)
        return true;
    return false;

}


// std::vector<Point> Polygon::getConvexHullPoints(std::vector<Point>&points) {
    
//     Point bottomMostPoint = getBottomRightMostPoint(points);
//     int pivotIndex = getIndexofBottomRightMostPoint(bottomMostPoint, points);
//     std::stack<Point> stack;
    
//     for (int i = 0; i < points.size(); i++) {
//         int index = (pivotIndex + i) % points.size();
//         std::cout<< "The index is: " << index << "\n";
//         if ( stack.size() < 2) {
//             std::cout<< "Stack size is less than 2\n";
//             stack.push(points[index]);
//         }
//         else{
//             std::cout<< "Stack size is: " << stack.size() << "\n";
//             auto middlePoint = stack.top();
//             stack.pop();
//             auto firstOuterPoint = stack.top();
//             stack.pop();
//             auto secondOuterPoint = points[index];
//             std::cout<< firstOuterPoint.x << " " << firstOuterPoint.y << " " << firstOuterPoint.theta_in_radian <<"\n";
//             std::cout<< middlePoint.x << " " << middlePoint.y << " " << middlePoint.theta_in_radian <<"\n";
//             std::cout<< secondOuterPoint.x << " " << secondOuterPoint.y << " " << secondOuterPoint.theta_in_radian <<"\n";

//             if (isPointOrientedCorrectly(firstOuterPoint, secondOuterPoint, middlePoint)) {
//                 stack.push(firstOuterPoint);
//                 stack.push(middlePoint);
//                 stack.push(secondOuterPoint);
//                 std::cout<< "The middle point is oriented correctly \n";
//             }
//             else{
//                 stack.push(firstOuterPoint);
//                 stack.push(secondOuterPoint);
//                 std::cout<< "The middle point is NOT oriented correctly \n";

//             }
//         }
//         std::cout<< "----------------------------------------------------------------------------\n";

//     }
//     while (stack.size() > 0 ){
//         auto point = stack.top();
//         stack.pop();
//         convexHullPoints.push_back(point);
//     }
//     return convexHullPoints;
// }

std::vector<Point> Polygon::getConvexHullPoints(std::vector<Point>&points) {
    
    Point bottomMostPoint = getBottomRightMostPoint(points);
    int pivotIndex = getIndexofBottomRightMostPoint(bottomMostPoint, points);

    std::cout<< "The first index is: " << pivotIndex << "\n";
    std::stack<Point> stack;
    
    stack.push(points[pivotIndex]);
    stack.push(points[(pivotIndex+1) % points.size()]);

    for (int iterator = 2; iterator < points.size(); iterator++) {
        int index = (pivotIndex + iterator) % points.size();
        std::cout<< "The index is: " << index << "\n";

        auto secondOuterPoint = points[index]; //next 
        auto middlePoint = stack.top(); //p
        stack.pop();
        auto firstOuterPoint = stack.top(); //useless ->just for declaration.
        // std::cout<< "New Iteration!\n";

        // std::cout<< firstOuterPoint.x << " " << firstOuterPoint.y << " " << firstOuterPoint.theta_in_radian <<"\n";
        // std::cout<< middlePoint.x << " " << middlePoint.y << " " << middlePoint.theta_in_radian <<"\n";
        // std::cout<< secondOuterPoint.x << " " << secondOuterPoint.y << " " << secondOuterPoint.theta_in_radian <<"\n";
        // std::cout<< "Before While Loop!\n";

        while( stack.size() > 0 and !isPointOrientedCorrectly(stack.top(), secondOuterPoint, middlePoint)) {
            middlePoint = stack.top();
            stack.pop();
            // std::cout<< firstOuterPoint.x << " " << firstOuterPoint.y << " " << firstOuterPoint.theta_in_radian <<"\n";
            // std::cout<< middlePoint.x << " " << middlePoint.y << " " << middlePoint.theta_in_radian <<"\n";
            // std::cout<< secondOuterPoint.x << " " << secondOuterPoint.y << " " << secondOuterPoint.theta_in_radian <<"\n";
            // std::cout << "Middle Point is incorrect-------\n";
            
        }
        stack.push(middlePoint);
        stack.push(points[index]);
        std::cout<< "----------------------------------------------------------------------------\n";

    }

    Point potentialColinearPoint = stack.top();
    stack.pop();

    if(isPointOrientedCorrectly(stack.top(), bottomMostPoint, potentialColinearPoint)) {
        stack.push(potentialColinearPoint);
    }

    std::cout << stack.size() << ": size of stack" << "\n";
    while (stack.size() > 0 ){
        auto point = stack.top();
        stack.pop();
        std::cout<< point.x << " " << point.y << " " << point.theta_in_radian <<"\n";
        convexHullPoints.push_back(point);
    }
    std::cout << "-----------------------------------------------\n";
    std::reverse(convexHullPoints.begin(), convexHullPoints.end());
    convexHullPoints.push_back(bottomMostPoint);
    return convexHullPoints;
}
