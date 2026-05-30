// Copyright 2026 NNTU-CS
#include <algorithm>
#include <cctype>
#include  <cstdlib>
#include  <iostream>
#include  <fstream>
#include  <locale>
#include <string>
#include <vector>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: couldn't open the file " << filename << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> nodes = tree.getSortedByFrequency();
    std::ofstream outFile("result/freq.txt");
    std::cout << "Word : Frequency" << std::endl;
    outFile << "Word : Frequency" << std::endl;

    for (const auto& node : nodes) {
        std::cout << node.first << " : " << node.second << std::endl;
        outFile << node.first << " : " << node.second << std::endl;
    }
    outFile.close();
}
