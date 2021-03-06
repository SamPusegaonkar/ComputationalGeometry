#include <fstream>
#include <sstream>
#include <iostream>

#include "../include/QuadTree.h"

Node* QuadTree::buildTree(std::vector<std::vector<int>>& image) {
    root = new Node();
    // std::cout<< "Entering\n";
    buildTreeHelper(root, 0, 0, matrix_size, 0);
    return root;
}

void QuadTree::buildTreeHelper(Node* node, int row, int col, int matrix_size, int depth) {
    node->depth = depth;

    if ( matrix_size <= 0 )
        return;

    else if ( matrix_size == 1) {  
        if( depthColors.find(depth) == depthColors.end()) {
            std::unordered_set<int>colors;
            depthColors[depth] = colors;
        } 
        int pixel = image[row][col];
        depthColors[depth].insert(pixel);
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

                    if ( splits.find(depth) == splits.end()) {
                        std::cout << "FIND a pixel with different value at (" << current_col+1 << " " << current_row+1 << ") \n";
                        std::cout << "SPLIT block " << depth << "\n";
                        splits.insert(depth);
                    }

                    node->initChildren();
                    buildTreeHelper(node->north_west, 
                        row, 
                        col, 
                        matrix_size/2, 4*depth+1);

                    buildTreeHelper(node->north_east, 
                        row, 
                        matrix_size/2 + col, 
                        matrix_size/2, 4*depth+2);

                    buildTreeHelper(node->south_west, 
                        matrix_size/2 + row, 
                        col, 
                        matrix_size/2, 4*depth+3);

                    buildTreeHelper(node->south_east, 
                        matrix_size/2 + row, 
                        matrix_size/2 + col, 
                        matrix_size/2, 4*depth+4);

                }
            }  
        } 
        if ( depthColors[depth].size() == 1) {
            node->type = setNodeType(row, col);
        }
    }
}


std::string QuadTree::setNodeType(int& row, int& col){

    if ( image[row][col] == 0)
        return "WHITE";
    return "BLACK";

}

Node* QuadTree::getIntersection( Node* firstTreeNode, Node* secondTreeNode) {
    // std::cout << "Entering!\n";
    
    
    if ( firstTreeNode->type == "WHITE" or secondTreeNode->type == "WHITE") {
        auto thirdTreeNode = new Node();
        thirdTreeNode->type = "WHITE";
        thirdTreeNode->depth = firstTreeNode->depth;

        return thirdTreeNode;
    }
    else if ( firstTreeNode->type == "BLACK") {
        // std::cout <<secondTreeNode->depth << " depth!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        auto thirdTreeNode = copyRecursively(secondTreeNode);
        thirdTreeNode->depth = firstTreeNode->depth;

        // getPreorderTraversal(thirdTreeNode);
        // std::cout <<secondTreeNode->depth << " completed!_!&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&-\n";
        return thirdTreeNode;
    }
    else if ( secondTreeNode->type == "BLACK") {
        // std::cout <<secondTreeNode->depth << " depth-----------------------------------------\n";
        auto thirdTreeNode = copyRecursively(firstTreeNode);
        thirdTreeNode->depth = firstTreeNode->depth;

        // getPreorderTraversal(thirdTreeNode);
        // std::cout <<secondTreeNode->depth << " completed!_!_1-1--1-1-1-1--1-1-1-1--1-1-1-\n";
        return thirdTreeNode;
    }
    else{
        auto thirdTreeNode = new Node();
        thirdTreeNode->initChildren();
        thirdTreeNode->depth = firstTreeNode->depth;
        std::cout << firstTreeNode->depth  << " " << firstTreeNode->type << " " << secondTreeNode->type << " "
                  << thirdTreeNode->type << "\n";
        thirdTreeNode->north_west = getIntersection(firstTreeNode->north_west, secondTreeNode->north_west);
        thirdTreeNode->north_east = getIntersection(firstTreeNode->north_east, secondTreeNode->north_east);
        thirdTreeNode->south_west = getIntersection(firstTreeNode->south_west, secondTreeNode->south_west);
        thirdTreeNode->south_east = getIntersection(firstTreeNode->south_east, secondTreeNode->south_east);
        if (thirdTreeNode->north_west->type == "WHITE" and thirdTreeNode->north_east->type == "WHITE" and 
            thirdTreeNode->south_west->type == "WHITE" and thirdTreeNode->south_east->type == "WHITE"){
            thirdTreeNode->type = "WHITE";
            thirdTreeNode->north_west = nullptr;
            thirdTreeNode->north_east = nullptr;
            thirdTreeNode->south_west = nullptr;
            thirdTreeNode->south_east = nullptr;
        }
        thirdTreeNode->depth = firstTreeNode->depth;
        return thirdTreeNode;
    }
    // std::cout << firstTreeNode->depth  << " " << firstTreeNode->type << " " << secondTreeNode->type << " "
    //               << thirdTreeNode->type << "\n";
    // return thirdTreeNode;
    
}

Node* QuadTree::copyRecursively( Node* node ) {

    if ( node == nullptr) {
        return nullptr;
    }
    Node* rootNode = new Node(node->type, node->depth);
    rootNode->initChildren();
    rootNode->north_west = copyRecursively(node->north_west);
    rootNode->north_east = copyRecursively(node->north_east);
    rootNode->south_west = copyRecursively(node->south_west);
    rootNode->south_east = copyRecursively(node->south_east);
    // std::cout << rootNode->type << " " << rootNode->depth << " copying\n";
    // if ( rootNode->north_east != nullptr)
    //     std::cout << rootNode->north_east->type << " " << rootNode->north_east->depth << " copying\n";
    // else
    //     std::cout << "found nothing\n";

    return rootNode;
}


void QuadTree::getPreorderTraversal(Node* node) {
    if ( node == nullptr) {
        return;
    }
    std::cout << node->depth << " " << node->type << "\n";
    // std::cout << node->north_west->depth << " " << node->north_west->type << "\n";
    // std::cout << node->north_east->depth << " " << node->north_east->type << "\n";
    // std::cout << node->south_west->depth << " " << node->south_west->type << "\n";
    // std::cout << node->south_east->depth << " " << node->south_east->type << "\n";
    getPreorderTraversal(node->north_west);
    getPreorderTraversal(node->north_east);
    getPreorderTraversal(node->south_west);
    getPreorderTraversal(node->south_east);
    // std::cout << node->type << " " << node->depth << " copying\n";
    // if ( node->north_east == nullptr)
    //     std::cout << "found nothing\n"; 

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

    // std::cout << matrix_size << " " << matrix_size << " : Number of rows and cols \n";
    
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
    // std::cout << "Completed reading line\n";
    return image;

}


