#include "avl.hpp"

AVL::AVL() 
{
    root = nullptr;
}
AVL::~AVL()
{
    postOrderDeletion(root);
}

int AVL::height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVL::max(int a, int b) {
    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

Node* AVL::newNode(std::string key) 
{
    Node* node = new Node;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

Node* AVL::rightRotate(Node* y) 
{
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* AVL::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int AVL::getBalance(Node* node) 
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node* AVL::insert(Node* node, std::string key) {
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // if node is already in the tree

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node); //Calculating Balance Factor
    // If not balanced - we perform rotation

    // Left Left Case
    if (balance > 1 && key < node->left->key) // Height of left subtree is greater 
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key) // Height of right subtree is graeter
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) { // Height of right of left subtree is greater
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) { // Height of left of right subtree is greater
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVL::insert(std::string key) 
{
    root = insert(root, key);
}

Node* AVL::minValueNode(Node* node) {
    Node* current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

bool AVL::deleteNode(Node* &root, std::string key) {
    if (root == nullptr) // Empty tree - node not found
        return false;

    bool deleted = false; // Flag to track if node is found and deleted

    // If key is less than current nodes key - recursively call on left subtree
    if (key < root->key)
        deleted = deleteNode(root->left, key);
    // If key is less than current nodes key - recursively call on left subtree
    else if (key > root->key)
        deleted = deleteNode(root->right, key);
    else 
    {   // Case1: No child or one child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp;
            if (root->left != nullptr)
                temp = root->left;
            else
                temp = root->right;
            if (temp == nullptr) 
            {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
            deleted = true; // Node found and deleted
        } 
        else 
        {   // Case 2: Two children 
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            deleted = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return deleted; // Return if node is nullptr

    root->height = 1 + max(height(root->left), height(root->right));

    // Recalculated balance factor - rotation performed accordingly
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return deleted; // Return flag indicating whether node is found and deleted
}

bool AVL::remove(std::string key) {
    return deleteNode(root, key);
}


Node* AVL::search(Node* root, std::string key) {
    if (root == nullptr || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

bool AVL::search(std::string key) {
    return search(root, key) != nullptr;
}

void AVL::inorderTraversal() {
    inorder(root);
    std::cout << std::endl;
}

void AVL::inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}

void AVL::postOrderDeletion(Node* root){
    if (root == nullptr){
        return;
    }
    postOrderDeletion(root->left);
    postOrderDeletion(root->right);
    delete root;
    root = nullptr;
}
