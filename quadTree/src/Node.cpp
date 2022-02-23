#include "../include/Node.h"

Node::Node() {}

Node::Node( char node_type) {
    this->type = node_type;
}


void Node::initChildren() {
    this->north_west = new Node();
    this->north_east = new Node();
    this->south_west = new Node();
    this->south_east = new Node();
}