#include <fstream>
#include <sstream>
#include <iostream>

#include "../include/QuadTree.h"

Node* QuadTree::buildTree(std::vector<std::vector<int>>& image) {
    root = new Node();
    return buildTreeHelper(root, 0, 0, matrix_size);
}

Node* QuadTree::buildTreeHelper(Node* node, int row, int col, int matrix_size) {

    // if ( matrix_size == 1) {
    //     node->type = setNodeType(row, col);
    // }
    // else{
    //     int color = image[row][col];

    // }


}

char QuadTree::setNodeType(int row, int col){

    if ( image[row][col] == 1)
        return 'W';
    return 'B';

}

Node* QuadTree::getIntersection( Node* firstTree, Node* secondTree) {

}
void QuadTree::getPreorderTraversal(Node* root) {

}

std::vector<std::vector<int>> QuadTree::readFile(std::string& filename) {

    std::fstream myfile(filename, std::ios_base::in);

    if (!myfile) {
        std::cerr << "Error: Could not find the requested file!\n";
        return image; //Error
    }

    std::string line;
    int matrix_size = 0;
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