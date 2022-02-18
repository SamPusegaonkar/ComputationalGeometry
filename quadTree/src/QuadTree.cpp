#include <fstream>
#include <sstream>
#include <iostream>

#include "../include/QuadTree.h"

Node* QuadTree::buildTree(std::vector<std::vector<int>>& image) {

}

Node* QuadTree::getIntersection( Node* firstTree, Node* secondTree) {

}
void QuadTree::getPreorderTraversal(Node* root) {

}

std::vector<std::vector<int>> QuadTree::readFile(std::string& filename) {

    std::fstream myfile(filename, std::ios_base::in);
    std::vector<std::vector<int>> image;

    if (!myfile) {
        std::cerr << "Error: Could not find the requested file!\n";
        return image; //Error
    }

    std::string line;
    int row_size = 0;
    if (getline(myfile, line)) 
        row_size = std::stoi(line);

    if ( row_size <= 0) {
        std::cerr << "Number of rows is less than or equal to 0\n";
        return image; //Error
    }
    int col_size = row_size;

    std::cout<<row_size << " " << col_size << " : Number of rows and cols \n";
    
    
    int counter = 1;
    std::string linetxt;
    while (std::getline(myfile, linetxt)){
        std::istringstream iss(linetxt);
        int a;
        std::vector<int>row;
        if ( counter > row_size) continue;
        // if (!(iss >> a) && counter <= row_size ) { 
        //     std::cout << counter << ":Counter\n";
        //     std::cerr << "There is something wrong with the input file!\n";
        //     return image; //Error
        // } 

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