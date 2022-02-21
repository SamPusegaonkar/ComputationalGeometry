#include <fstream>
#include <sstream>
#include <iostream>

#include "../include/QuadTree.h"

Node* QuadTree::buildTree(std::vector<std::vector<int>>& image) {
    root = new Node();
    buildTreeHelper(root, 0, 0, matrix_size, 0);
    return root;
}

void QuadTree::buildTreeHelper(Node* node, int row, int col, int matrix_size, int depth) {
    if ( matrix_size == 1) {    
        node->type = setNodeType(row, col);
        return;
    }
    else{
        int color = image[row][col];
        for ( int current_row = row; current_row < matrix_size; current_row++ ) {
            for ( int current_col = col; current_col < matrix_size; current_col++ ) {
                int pixel = image[current_row][current_col];
                if ( pixel != color) {
                    std::cout << "FIND a pixel with different value at " << current_col+1 << " " << current_row+1 <<" " << matrix_size << " \n";
                    std::cout << "SPLIT block " << depth << "\n";
                    int corner_row = getBlockStartRow(current_row, matrix_size);
                    int corner_col = getBlockStartCol(current_col, matrix_size);
                    std::cout << corner_row << " " << corner_col << "\n";

                    node->initChildren();
                    buildTreeHelper(node->north_west, corner_row, corner_col, matrix_size/2, 4*depth+1);
                    // buildTreeHelper(node->north_east, getBlockStartRow(current_row, row), col - getBlockStartCol(current_col, col), matrix_size/2, 4*depth+2);
                    // buildTreeHelper(node->south_west, row - getBlockStartRow(current_row, row), getBlockStartCol(current_col, col), matrix_size/2, 4*depth+3);
                    // buildTreeHelper(node->south_east, row - getBlockStartRow(current_row, row), col - getBlockStartCol(current_col, col), matrix_size/2, 4*depth+4);
                }
            }
        }
        
    }
}

//get corner of the blocks
//for loop range



int QuadTree::getBlockStartRow(int current_row, int total_rows) {
    std::cout << "Getting the start row of the block\n";
    std::cout << current_row << " " << total_rows << "\n";
    if ( current_row < (total_rows/2)) {
        std::cout << "Returning 0 - from if\n";
        return 0;
    }
    std::cout << "Returning "<< (total_rows/2) << "\n";
    return (total_rows/2);

}

int QuadTree::getBlockStartCol(int current_col, int total_cols) {
    std::cout << "Getting the start col of the block\n";
    std::cout << current_col << " " << total_cols << "\n";
    std::cout << total_cols/2 << "\n";
    if ( current_col < (total_cols/2)) {
        std::cout << "Returning 0 - from if\n";
        return 0;
    }
        
    std::cout << "Returning "<< (total_cols/2) << "\n";
    return (total_cols/2);
    
}


char QuadTree::setNodeType(int& row, int& col){

    if ( image[row][col] == 1)
        return 'W';
    return 'B';

}

Node* QuadTree::getIntersection( Node* firstTree, Node* secondTree) {

}
void QuadTree::getPreorderTraversal(Node* node) {
    if ( root == NULL) {
        return;
    }
    
    getPreorderTraversal(node->north_west);
    getPreorderTraversal(node->north_east);
    getPreorderTraversal(node->south_west);
    getPreorderTraversal(node->south_west);
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