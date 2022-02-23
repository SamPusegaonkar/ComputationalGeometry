class Node {

    public:
        char type = 'G';
        Node* north_west = nullptr;
        Node* north_east = nullptr;
        Node* south_west= nullptr;
        Node* south_east = nullptr;
        int depth = 999999;
        Node(char node_type);
        Node( char node_type, Node* nw, Node* ne, Node* sw, Node* se);
        Node(char node_type, int node_depth);
        Node();
        void initChildren();
};