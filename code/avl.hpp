#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <string>
#include <algorithm>

struct Node 
{
    std::string key;
    int height;
    Node* left;
    Node* right;
};

class AVL {
public:
    AVL();
    ~AVL();

    void insert(std::string key);
    bool remove(std::string key);
    bool search(std::string key);
    void inorderTraversal();
    void postOrderDeletion(Node* root);

private:
    Node* root;

    int height(Node* node);
    int max(int a, int b);
    Node* newNode(std::string key);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getBalance(Node* node);
    Node* insert(Node* node, std::string key);
    Node* minValueNode(Node* node);
    bool deleteNode(Node* &root, std::string key);
    Node* search(Node* root, std::string key);
    void inorder(Node* root);
};

#endif // AVL_HPP
