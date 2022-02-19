#include "Node.h"
#include <vector>
#include <string>

class QuadTree {
    public:
        Node* root;
        int matrix_size = 0;
        std::vector<std::vector<int>> image;
        Node* buildTree(std::vector<std::vector<int>>& image);
        Node* getIntersection( Node* firstTree, Node* secondTree);
        void getPreorderTraversal(Node* root);
        std::vector<std::vector<int>> readFile(std::string& filename);
        Node* buildTreeHelper(Node* node, int row, int col, int matrix_size);
        char setNodeType(int row, int col);
        
};