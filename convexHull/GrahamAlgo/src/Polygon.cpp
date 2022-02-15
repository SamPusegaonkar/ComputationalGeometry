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
    return a.theta_in_radian < b.theta_in_radian; 
}

std::vector<Point> Polygon::sortPoints(std::vector<Point>&points) {
    sort(points.begin(), points.end(), customComparator);
    return points;
}

Point Polygon::getBottomRightMostPoint(std::vector<Point>&points) {
    float minYCord = std::numeric_limits<float>::max();

    for ( auto point : points) {
        if ( point.x < minYCord) {
            minYCord = point.x;
        }
    }

    std::map<float, std::vector<Point>> bottomMostPoints;

    for ( auto point : points) {
        if ( isEqual(point.x, minYCord)) {
            bottomMostPoints[minYCord].push_back(point);
        }
    }

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
        std::cout<< point.x << " " << point.y << "\n";
    }
    std::cout<< "----------------------------------------\n";
}

void Polygon::printAllPoints( std::vector<Point>& points) {
    
    for ( auto point : points) {
        std::cout<< point.x << " " << point.y << point.theta_in_radian << "\n";
    }
    std::cout<< "----------------------------------------\n";
}


bool Polygon::isLessThanOrEqual(float a, float b) {
    //Order of the parameter matters!

    if ( a < b or fabs(a-b) < 0.0001){
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
        return points; //TODO: throw exception!
    }

    std::string line;
    int number_of_lines = 0;
    if (getline(myfile, line)) 
        number_of_lines = std::stoi(line);

    if ( number_of_lines <= 0) {
        std::cout << "Number of lines is less than or equal to 0\n";
        return points; //TODO: throw exception
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
            std::cout << "There is something wrong with the input file!\n";
            return points; //TODO: throw exception!
        } 

        // std::cout<< a << " " << b<< "\n";
        counter++;
        points.push_back(Point(a, b));
        std::cout << "Reading Line\n";    
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
    if (determinent > 0)
        return true;
    return false;

}


std::vector<Point> Polygon::getConvexHullPoints(std::vector<Point>&points) {
    
    Point bottomMostPoint = getBottomRightMostPoint(points);
    int index = getIndexofBottomRightMostPoint(bottomMostPoint, points);
    std::stack<Point> stack;
    int counter = 0;
    while ( counter < 10) {
        
        if ( stack.size() < 2) {
            index++;
            stack.push(points[index % points.size()]);
            
        }
        else{
            auto middlePoint = stack.top();
            stack.pop();
            auto firstOuterPoint = stack.top();
            stack.pop();
            index++;
            auto secondOuterPoint = points[index % points.size()];
            if (isPointOrientedCorrectly(firstOuterPoint, secondOuterPoint, middlePoint)) {
                stack.push(firstOuterPoint);
                stack.push(middlePoint);
                stack.push(secondOuterPoint);
            }
            else{
                stack.push(firstOuterPoint);
                stack.push(secondOuterPoint);
            }
        }
        counter++;
        
    }


    while (stack.size() < 0 ){
        auto point = stack.top();
        stack.pop();
        convexHullPoints.push_back(point);
    }
    return convexHullPoints;
}
