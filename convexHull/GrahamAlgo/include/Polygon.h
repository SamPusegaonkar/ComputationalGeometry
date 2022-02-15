#include "Point.h"

class Polygon {
    public: 
        std::vector<Point> allPoints;
        std::vector<Point> convexHullPoints;
        Polygon();
        std::vector<Point> readFile(std::string &filename);
        std::vector<Point> sortPoints(std::vector<Point>&points);
        Point getBottomRightMostPoint(std::vector<Point>&points);
        int getIndexofBottomRightMostPoint(Point& bottomMostPoint, std::vector<Point>&points);
        std::vector<Point> getConvexHullPoints(std::vector<Point>&points);
        void printAllPoints();
        void printAllPoints(std::vector<Point>& points);
        void printConvexHullPoints();
        bool isEqual(float a, float b);
        bool isLessThanOrEqual(float a, float b);
        bool isPointOrientedCorrectly(Point& p1, Point& p2, Point& p3);

};  

