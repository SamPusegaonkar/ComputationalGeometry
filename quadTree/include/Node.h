#include <iostream>

class Node {


    public:
        std::string type = "GRAY";
        Node* north_west = nullptr;
        Node* north_east = nullptr;
        Node* south_west= nullptr;
        Node* south_east = nullptr;
        int depth = 999999;
        Node( std::string node_type);
        Node( std::string node_type, Node* nw, Node* ne, Node* sw, Node* se);
        Node( std::string node_type, int node_depth);
        Node();
        void initChildren();
};