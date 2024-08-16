#ifndef SCAPEGOAT_TREE_HPP
#define SCAPEGOAT_TREE_HPP

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <string>
#include "RBT.hpp"
using namespace std;


class ScapeGoatTree 
{
public:
    ScapeGoatTree();
    int size(Node2 *node);
    int log32(int q);

    bool search(string val);
    void insert(string x);
    bool deleteNode(string key);

private:
    int n, q;
    Node2 *root;
    bool search(Node2 *r, string val);
    int makeArrayofPointers(Node2 *ptr, int i);
    void rebuildTree(Node2 *u);
    Node2 *buildBalancedTree(int i, int n);
    int addWithDepth(Node2 *u);
    Node2 *inorderPred(Node2 *r);
    Node2 *deleteBST(Node2 *r, string key);
};

#endif // SCAPEGOAT_TREE_HPP


