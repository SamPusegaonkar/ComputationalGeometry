#include <vector>
#include "Edge.h"

class Polygon : public Edge {
    public: 
    std::vector<std::unique_ptr<Edge>> edges;
    void readFile(std::string filename);
    std::vector<std::unique_ptr<Edge>> getPoints();
    int isPointInPolygon();
    int intersectEdge(std::unique_ptr<Edge> e, std::unique_ptr<Point> p,int m);


};

