#include <fstream>
#include <sstream>
#include <iostream>

#include "../include/QuadTree.h"

Node* QuadTree::buildTree(std::vector<std::vector<int>>& image) {
    root = new Node();
    std::cout<< "Entering\n";
    buildTreeHelper(root, 0, 0, matrix_size, 0);
    return root;
}

void QuadTree::buildTreeHelper(Node* node, int row, int col, int matrix_size, int depth) {
    node->depth = depth;
    if( depthColors.find(depth) == depthColors.end()) {
        std::unordered_set<int>colors;
        depthColors[depth] = colors;
    }

    if ( matrix_size == 1) {    
        node->type = setNodeType(row, col);
        return;
    }
    else{
        
        int color = image[row][col];

        for ( int current_row = row; current_row < row + matrix_size; current_row++ ) {
            for ( int current_col = col; current_col < col + matrix_size; current_col++ ) {
                
                int pixel = image[current_row][current_col];

                if( depthColors.find(depth) == depthColors.end()) {
                    std::unordered_set<int>colors;
                    depthColors[depth] = colors;
                }
                depthColors[depth].insert(pixel);

                if ( pixel != color) {
                    std::cout << "FIND a pixel with different value at " << current_col+1 << " " << current_row+1 <<" " << matrix_size << " \n";
                    std::cout << "SPLIT block " << depth << "\n";

                    node->initChildren();

                    buildTreeHelper(node->north_west, 
                        getBlockStartRow(row, matrix_size), 
                        getBlockStartCol(col, matrix_size), 
                        matrix_size/2, 4*depth+1);

                    buildTreeHelper(node->north_east, 
                        getBlockStartRow(row, matrix_size), 
                        matrix_size/2 + getBlockStartCol(col, matrix_size), 
                        matrix_size/2, 4*depth+2);

                    buildTreeHelper(node->south_west, 
                        matrix_size/2 + getBlockStartRow(row, matrix_size), 
                        getBlockStartCol(col, matrix_size), 
                        matrix_size/2, 4*depth+3);

                    buildTreeHelper(node->south_east, 
                        matrix_size/2 + getBlockStartRow(row, matrix_size), 
                        matrix_size/2 + getBlockStartCol(col, matrix_size), 
                        matrix_size/2, 4*depth+4);

                }
            }  
        } 
        if ( depthColors[depth].size() == 2)
            node->type = setNodeType(row, col);
        else
            node->type = image[row][col] == 1 ? 'B' : 'W';
    }
}



int QuadTree::getBlockStartRow(int current_row, int total_rows) {
    // std::cout << "Getting the start row of the block\n";
    // std::cout << current_row << " " << total_rows << "\n";
    if ( current_row < (total_rows/2)) {
        // std::cout << "Returning 0 - from if\n";
        return 0;
    }
    // std::cout << "Returning "<< (total_rows/2) << "\n";
    return (total_rows/2);

}

int QuadTree::getBlockStartCol(int current_col, int total_cols) {
    // std::cout << "Getting the start col of the block\n";
    // std::cout << current_col << " " << total_cols << "\n";
    if ( current_col < (total_cols/2)) {
        // std::cout << "Returning 0 - from if\n";
        return 0;
    }
        
    // std::cout << "Returning "<< (total_cols/2) << "\n";
    return (total_cols/2);
    
}


char QuadTree::setNodeType(int& row, int& col){

    if ( image[row][col] == 0)
        return 'W';
    return 'B';

}

Node* QuadTree::getIntersection( Node* firstTree, Node* secondTree) {

}
void QuadTree::getPreorderTraversal(Node* node) {
    if ( node == nullptr) {
        return;
    }
    std::cout << node->depth << " " << node->type << "\n";
    getPreorderTraversal(node->north_west);
    getPreorderTraversal(node->north_east);
    getPreorderTraversal(node->south_west);
    getPreorderTraversal(node->south_east);
}

std::vector<std::vector<int>> QuadTree::readFile(std::string& filename) {

    std::fstream myfile(filename, std::ios_base::in);

    if (!myfile) {
        std::cerr << "Error: Could not find the requested file!\n";
        return image; //Error
    }

    std::string line;
    if (getline(myfile, line)) 
        matrix_size = std::stoi(line);

    if ( matrix_size <= 0) {
        std::cerr << "Number of rows is less than or equal to 0\n";
        return image; //Error
    }

    std::cout << matrix_size << " " << matrix_size << " : Number of rows and cols \n";
    
    int counter = 1;
    std::string linetxt;
    while (std::getline(myfile, linetxt)){
        std::istringstream iss(linetxt);
        int a;
        std::vector<int>row;
        if ( counter > matrix_size) continue;
        while ( iss >> a) {
            row.push_back(a);
        }

        // std::cout<< a << " " << b<< "\n";
        counter++;
        image.push_back(row);
        // std::cout << "Reading Line\n";    
    }
    std::cout << "Completed reading line\n";
    return image;

}