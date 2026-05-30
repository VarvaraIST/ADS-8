// Copyright 2026 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int nodeCount;

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* insert(Node* node, const T& key, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, inserted);
        } else if (key > node->key) {
            node->right = insert(node->right, key, inserted);
        } else {
            node->count++;
            inserted = false;
        }
        return node;
    }

    Node* search(Node* node, const T& key) const {
        if (node == nullptr || node->key == key) {
            return node;
        }
        if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    int depth(Node* node) const {
        if (node == nullptr) return -1;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void collectNodes(Node* node,
    std::vector<std::pair<std::string, int>>& nodes) const {
        if (node == nullptr) return;
        collectNodes(node->left, nodes);
        nodes.push_back({ node->key, node->count });
        collectNodes(node->right, nodes);
    }

 public:
    BST() : root(nullptr), nodeCount(0) {}

    ~BST() {
        clear(root);
    }

    int getFrequency(const T& key) const {
        Node* node = search(root, key);
        return node ? node->count : 0;
    }

    int search(const T& key) const {
        return search(root, key) != nullptr;
    }

    void insert(const T& key) {
        bool inserted = false;
        root = insert(root, key, inserted);
        if (inserted) {
            nodeCount++;
        }
    }
    int depth() const {
        return depth(root);
    }

    int size() const {
        return nodeCount;
    }

    std::vector<std::pair<std::string, int>> getSortedByFrequency() const {
        std::vector<std::pair<std::string, int>> nodes;
        collectNodes(root, nodes);

        std::sort(nodes.begin(), nodes.end(),
            [](const std::pair<std::string, int>& a,
                const std::pair<std::string, int>& b) {
                    return a.second > b.second;
            });
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
