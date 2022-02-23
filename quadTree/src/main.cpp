

#include <iostream>
#include <cmath>

#include "../include/QuadTree.h"
// #include "../include/matplotlibcpp.h"
// namespace plt = matplotlibcpp;

// gcc main.cpp  QuadTree.cpp Node.cpp -lstdc++ -o main.o

int main( ) {

    //Read the input file 
    // std::cout << "START INPUT\n";
    // std::string file;
    // std::cout << "Type the filename & press enter! (Example: test_case.txt) ";
    // std::cin >> file;
    std::string directory = "../input/";
    // std::string filename = directory + file;

    // QuadTree qt;
    // auto image = qt.readFile(filename);

    // //Building Tree
    // auto rootNode = qt.buildTree(image);
    // std::cout << "SPLIT COMPLETED\n";
    // std::cout << "START RQ\n";

    // //Preorder Tree
    // qt.getPreorderTraversal(rootNode);
    // std::cout << "END RQ\n";


    //INTERSECTION TEST
    Node* intersection_root_node = new Node();
    QuadTree qt1, qt2;
    std::string filename1 = directory + "2.txt";
    std::string filename2 = directory + "3.txt";
    auto image1 = qt1.readFile(filename1);
    auto image2 = qt2.readFile(filename2);
    auto tree1 = qt1.buildTree(image1);
    auto tree2 = qt2.buildTree(image2);
    std::cout << "---------------------------------------------\n";
    std::cout << "START INTERSECTION\n";

    qt1.getIntersection(tree1, tree2, intersection_root_node);
    std::cout << "END INTERSECTION\n";
    std::cout << "---------------------------------------------\n";

    qt1.getPreorderTraversal(intersection_root_node);

} 

//double printing!
