#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

enum Color { RED, BLACK };

struct Node2 {
    std::string value;
    Color color;
    Node2* left;
    Node2* right;
    Node2* parent;

    Node2(const std::string& value);
};

class RedBlackTree {
private:
    Node2* root;

    void rotateLeft(Node2* x);
    void rotateRight(Node2* x);
    void fixViolation(Node2* x);
    void insertHelper(Node2* z);
    void inorderHelper(Node2* x);
    Node2* minValueNode(Node2* node);
    bool deleteNodeHelper(Node2* node, const std::string& key);
    void fixDoubleBlack(Node2* x);
    Node2* searchTreeHelper(Node2* node, const std::string& key);
    void deleteTreeHelper(Node2* node);
    void saveTreeHelper(Node2* node, std::ofstream& file);

public:
    RedBlackTree();
    ~RedBlackTree();
    void insert(const std::string& data);
    bool deleteNode(const std::string& data);
    void inorder();
    Node2* searchTree(const std::string& key);
    void deleteTree();
    void readDataFromFile(const std::string& filename);
    void saveTreeToFile(const std::string& filename);
};

#endif
