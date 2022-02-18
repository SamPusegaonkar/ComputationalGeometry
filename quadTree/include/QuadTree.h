#include "Node.h"
#include <vector>
#include <string>

class QuadTree {
    public:
        Node* root;
        Node* buildTree(std::vector<std::vector<int>>& image);
        Node* getIntersection( Node* firstTree, Node* secondTree);
        void getPreorderTraversal(Node* root);
        std::vector<std::vector<int>> readFile(std::string& filename);

};