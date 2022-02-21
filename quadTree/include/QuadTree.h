#include "Node.h"
#include <vector>
#include <string>

class QuadTree {
    public:
        Node* root = NULL;
        int matrix_size = 0;
        std::vector<std::vector<int>> image;
        Node* buildTree(std::vector<std::vector<int>>& image);
        Node* getIntersection( Node* firstTree, Node* secondTree);
        void getPreorderTraversal(Node* root);
        std::vector<std::vector<int>> readFile(std::string& filename);
        void buildTreeHelper(Node* node, int row, int col, int matrix_size, int depth);
        char setNodeType(int& row, int& col);
        int getBlockStartRow(int current_row, int total_rows);
        int getBlockStartCol(int current_col, int total_cols);
        
};