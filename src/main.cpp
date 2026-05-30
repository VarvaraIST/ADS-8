// Copyright 2026 NNTU-CS
#include <iostream>

#include "bst.h"


void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    makeTree(tree, "src/war_peace.txt");

    std::cout << "Unique words: " << tree.size() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << std::endl;
    printFreq(tree);
    return 0;
}
