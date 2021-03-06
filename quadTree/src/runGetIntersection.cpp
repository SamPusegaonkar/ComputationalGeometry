#include <iostream>
#include <cmath>

#include "../include/QuadTree.h"

// gcc runGetIntersection.cpp QuadTree.cpp Node.cpp -lstdc++ -o runGetIntersection.o


int main( ) {

    //Read the input file 
    std::cout << "START INPUT\n";
    std::string file;
    std::cout << "Type name of the first file & press enter! (Example: test_case_1.txt) ";
    std::cin >> file;
    std::string directory = "../input/";
    std::string filename1 = directory + file;

    std::cout << "Type name of the second file & press enter! (Example: test_case_2.txt) ";
    std::cin >> file;
    std::string filename2 = directory + file;

    //INTERSECTION TEST
    Node* intersection_root_node = new Node();
    QuadTree qt1, qt2;

    auto image1 = qt1.readFile(filename1);
    auto image2 = qt2.readFile(filename2);
    std::cout << "---------------------------------------------\n";
    auto tree1 = qt1.buildTree(image1);
    std::cout << "SPLIT COMPLETED\n";
    std::cout << "---------------------------------------------\n";
    auto tree2 = qt2.buildTree(image2);
    std::cout << "SPLIT COMPLETED\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "START INTERSECTION\n";

    intersection_root_node = qt1.getIntersection(tree1, tree2);
    std::cout << "END INTERSECTION\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "START RQ\n";
    qt1.getPreorderTraversal(intersection_root_node);
    std::cout << "END RQ\n";
    std::cout << "---------------------------------------------\n";


} 

//double printing!
