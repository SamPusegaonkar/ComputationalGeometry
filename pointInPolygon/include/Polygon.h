#include "Edge.h"

class Polygon {
    public: 
        std::vector<std::shared_ptr<Edge>> edges;
        std::shared_ptr<Point>query_point;
        Polygon(std::vector<std::shared_ptr<Edge>> &edges);
        Polygon();
        void setQueryPoint(float x, float y);
        int readFile(std::string &filename);
        std::vector<std::unique_ptr<Edge>> getPoints();
        int isPointInsidePolygon(std::vector<std::shared_ptr<Edge>> &edges, std::shared_ptr<Point> &point);
        int isPointInsidePolygon();
        int intersectEdge( std::shared_ptr<Edge>&edge, std::shared_ptr<Point>&point, int &sub_result);
        void convertPointToEdges(std::vector<Point> &points);
        bool isEqual(float a, float b);
        bool isLessThanOrEqual(float a, float b);

};  

