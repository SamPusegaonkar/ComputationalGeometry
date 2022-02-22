#include "../include/Node.h"

Node::Node() {}

void Node::initChildren() {
    this->north_west = new Node();
    this->north_east = new Node();
    this->south_west = new Node();
    this->south_east = new Node();
}