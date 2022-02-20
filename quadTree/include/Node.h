class Node {
    public:
        char type;
        Node* north_west = nullptr;
        Node* north_east = nullptr;
        Node* south_west= nullptr;
        Node* south_east = nullptr;
        Node( char node_type, Node* nw, Node* ne, Node* sw, Node* se);
        Node();
        int left_i = 0;

};