class Node {
    public:
        char type;
        Node* north_west;
        Node* north_east;
        Node* south_west;
        Node* south_east;
        Node( char node_type, Node* nw, Node* ne, Node* sw, Node* se);
        Node();

};