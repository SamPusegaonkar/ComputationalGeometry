#include <iostream>
#include "../include/Point.h"

int main( ) {

    std::unique_ptr<Point> point1 = std::make_unique<Point>(10, 20);
    std::unique_ptr<Point> point2 = std::make_unique<Point>(10, 20);
    std::cout << point1->x << " " << point1->y << "\n";
    auto result = *point1 == *point2;
    std::cout << result << "\n";


} 