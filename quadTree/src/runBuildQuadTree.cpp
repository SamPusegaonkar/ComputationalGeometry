

#include <iostream>
#include <cmath>

#include "../include/QuadTree.h"

// gcc runBuildQuadTree.cpp QuadTree.cpp Node.cpp -lstdc++ -o runBuildQuadTree.o


int main( ) {

    //Read the input file 
    std::cout << "START INPUT\n";
    std::string file;
    std::cout << "Type the filename & press enter! (Example: test_case.txt) ";
    std::cin >> file;
    std::string directory = "../input/";
    std::string filename = directory + file;

    QuadTree qt;
    auto image = qt.readFile(filename);

    //Building Tree
    auto rootNode = qt.buildTree(image);
    std::cout << "SPLIT COMPLETED\n";
    std::cout << "START RQ\n";

    //Preorder Tree
    qt.getPreorderTraversal(rootNode);
    std::cout << "END RQ\n";



} 
