

#include <iostream>
#include <cmath>

#include "../include/QuadTree.h"
// #include "../include/matplotlibcpp.h"
// namespace plt = matplotlibcpp;

int main( ) {

    //Read the input file 
    std::string file;
    std::cout << "Type the filename & press enter! (Example: test_case.txt) ";
    std::cin >> file;
    std::string directory = "../input/";
    std::string filename = directory + file;

    QuadTree qt;
    auto image = qt.readFile(filename);

    auto rootNode = qt.buildTree(image);
    qt.getPreorderTraversal(rootNode);
    
    // auto intersection_root_node = qt.getIntersection(tree1, tree2);
    // qt.getPreorderTraversal(intersection_root_node);

} 
