

#include <iostream>
#include <cmath>

#include "../include/QuadTree.h"
// #include "../include/matplotlibcpp.h"
// namespace plt = matplotlibcpp;

// gcc main.cpp  QuadTree.cpp Node.cpp -lstdc++ -o main.o

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
    for ( auto row : image) {
        for ( auto value : row) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }

    auto rootNode = qt.buildTree(image);
    std::cout << "START RQ\n";
    // qt.getPreorderTraversal(rootNode);
    std::cout << "END RQ\n";
    
    // auto intersection_root_node = qt.getIntersection(tree1, tree2);
    // qt.getPreorderTraversal(intersection_root_node);

} 
