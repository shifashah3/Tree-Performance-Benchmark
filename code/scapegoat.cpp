#include "scapegoat.hpp"
#include<bits/stdc++.h> 
#include <vector>
#include <cmath>
#include <string>
using namespace std;

ScapeGoatTree::ScapeGoatTree() 
{
    root = NULL; 
    n = 0;
    q = 0;
}

int ScapeGoatTree::size(Node2 *node) { 
    if (node == NULL) 
        return 0; 
    return 1 + size(node->left) + size(node->right); 
} 

int ScapeGoatTree::log32(int q) { 
    return (int)(log(q)/log(1.5)); 
}


bool ScapeGoatTree::search(Node2 *r, string val) {
    while (r != NULL) {
        string rval = r->value;
        if (val < rval)
            r = r->left;
        else if (val > rval)
            r = r->right;
        else
            return true;
    }
    return false;
}

bool ScapeGoatTree::search(string val) 
{
    return search(root, val);
}

void ScapeGoatTree::insert(string x) { 
    Node2 *node = new Node2(x); 
    int d = addWithDepth(node); 
    if (d > log32(q)) { 
        Node2 *p = node->parent; 
        while (3*size(p) <= 2*size(p->parent)) 
            p = p->parent; 

        rebuildTree(p->parent); 
    } 

    return; 
} 

vector <Node2 *> arr;
int ScapeGoatTree::makeArrayofPointers(Node2 *ptr, int i) 
{ 
    if (!ptr) 
        return i; 

    i = makeArrayofPointers(ptr->left, i); 
    arr[i++] = ptr;
    return makeArrayofPointers(ptr->right, i); 
}

void ScapeGoatTree::rebuildTree(Node2 *u) { 
    int n = size(u); 
    Node2 *p = u->parent; 
    arr.resize(n);
    makeArrayofPointers(u, 0);
    if (p == NULL) { 
        root = buildBalancedTree(0, n); 
        root->parent = NULL; 
    } else if (p->right == u) { 
        p->right = buildBalancedTree(0, n); 
        p->right->parent = p; 
    } else { 
        p->left = buildBalancedTree(0, n); 
        p->left->parent = p; 
    } 
} 

Node2* ScapeGoatTree::buildBalancedTree(int i, int n) { 
    if (n == 0) 
        return NULL; 
    int m = n / 2; 

    arr[i+m]->left = buildBalancedTree(i, m); 

    if (arr[i+m]->left != NULL) 
        arr[i+m]->left->parent = arr[i+m]; 

    arr[i+m]->right = buildBalancedTree(i+m+1, n-m-1); 
    if (arr[i+m]->right != NULL) 
        arr[i+m]->right->parent = arr[i+m]; 

    return arr[i+m]; 
} 

int ScapeGoatTree::addWithDepth(Node2 *u) {
    Node2 *temp_root = root; 
    if (temp_root == NULL) { 
        root = u; 
        n++;
        q++;
        return 0; 
    } 
    bool done = false; 
    int d = 0; 
    do { 
        if (u->value < temp_root->value) 
        { 
            if (temp_root->left == NULL) 
            { 
                temp_root->left = u; 
                u->parent = temp_root; 
                done = true; 
            } else
                temp_root = temp_root->left; 
        } 
        else if (u->value > temp_root->value) 
        { 
            if (temp_root->right == NULL) 
            { 
                temp_root->right = u; 
                u->parent = temp_root; 
                done = true; 
            } 
            else
                temp_root = temp_root->right; 
        } else
            return -1; 
        d++; 
    } while (!done); 

    n++;
    q++;
    return d; 
}

Node2 *ScapeGoatTree::inorderPred(Node2 *r) {
    r=r->left;
    while(r->right) {
        r=r->right;
    }
    return r;
}

Node2* ScapeGoatTree::deleteBST(Node2 *r, string key) {
    if(!r)
        return NULL;
    if(r->value > key) {
        r->left = deleteBST(r->left, key);
    } else if(r->value < key) {
        r->right = deleteBST(r->right, key);
    } else {
        if(!r->left) {
            Node2* temp = r->right;
            return temp;
        } else if(!r->right) {
            Node2* temp = r->left;
            return temp;
        }
        Node2 *temp = inorderPred(r);
        r->value = temp->value;
        r->left = deleteBST(r->left, temp->value);
    }
    return r;
}

bool ScapeGoatTree::deleteNode(string key) 
{
    if (search(root, key)) 
	{
        root = deleteBST(root, key);
        n--;
        if (q > 2 * n) 
		{
            rebuildTree(root);
            q = n;
        }
        return true;
    } 
	else 
	{
        return false;
    }
}


