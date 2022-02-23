#include "Node.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>


class QuadTree {
    public:
        Node* root = NULL;
        int matrix_size = 0;
        std::unordered_map<int,std::unordered_set<int>>depthColors;
        std::unordered_set<int>splits;
        std::vector<std::vector<int>> image;
        Node* buildTree(std::vector<std::vector<int>>& image);
        void getIntersection( Node* firstTree, Node* secondTree, Node* thirdTree);
        void getPreorderTraversal(Node* root);
        std::vector<std::vector<int>> readFile(std::string& filename);
        void buildTreeHelper(Node* node, int row, int col, int matrix_size, int depth);
        char setNodeType(int& row, int& col);
        Node* copyRecursively(Node* node);
        
};