#include "../include/Node.h"

Node::Node() {}

Node::Node( std::string node_type) {
    this->type = node_type;
}

Node::Node( std::string node_type, int depth_) {
    this->type = node_type;
    this->depth = depth_;
}

void Node::initChildren() {
    this->north_west = new Node();
    this->north_east = new Node();
    this->south_west = new Node();
    this->south_east = new Node();
}