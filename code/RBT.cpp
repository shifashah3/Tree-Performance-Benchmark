#include "RBT.hpp"

Node2::Node2(const std::string& value) : value(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

RedBlackTree::RedBlackTree() : root(nullptr) {}

RedBlackTree::~RedBlackTree() {
    deleteTree();
}

void RedBlackTree::rotateLeft(Node2* x) {
    Node2* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node2* x) {
    Node2* y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixViolation(Node2* x) {
    Node2* parent = nullptr;
    Node2* grandparent = nullptr;
    while ((x != root) && (x->color != BLACK) && (x->parent->color == RED)) {
        parent = x->parent;
        grandparent = x->parent->parent;
        if (parent == grandparent->left) {
            Node2* uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent;
            } else {
                if (x == parent->right) {
                    rotateLeft(parent);
                    x = parent;
                    parent = x->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                x = parent;
            }
        } else {
            Node2* uncle = grandparent->left;
            if ((uncle != nullptr) && (uncle->color == RED)) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent;
            } else {
                if (x == parent->left) {
                    rotateRight(parent);
                    x = parent;
                    parent = x->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                x = parent;
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::insert(const std::string& value) {
    Node2* node = new Node2(value);
    insertHelper(node);
}

void RedBlackTree::insertHelper(Node2* z) {
    Node2* x = root;
    Node2* y = nullptr;
    while (x != nullptr) {
        y = x;
        if (z->value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->value < y->value)
        y->left = z;
    else
        y->right = z;
    fixViolation(z);
}

void RedBlackTree::inorder() {
    inorderHelper(root);
}

void RedBlackTree::inorderHelper(Node2* x) {
    if (x != nullptr) {
        inorderHelper(x->left);
        std::cout << x->value << " ";
        inorderHelper(x->right);
    }
}

Node2* RedBlackTree::minValueNode(Node2* node) {
    Node2* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node2* RedBlackTree::searchTree(const std::string& key) {
    return searchTreeHelper(root, key);
}

Node2* RedBlackTree::searchTreeHelper(Node2* node, const std::string& key) {
    if (node == nullptr || node->value == key)
        return node;
    if (key < node->value)
        return searchTreeHelper(node->left, key);
    return searchTreeHelper(node->right, key);
}

bool RedBlackTree::deleteNode(const std::string& value) {
    bool x = deleteNodeHelper(root, value);
    return x;
}

bool RedBlackTree::deleteNodeHelper(Node2* node, const std::string& key) {
    Node2* z = nullptr;
    while (node != nullptr) {
        if (node->value == key) {
            z = node;
        }
        if (key <= node->value)
            node = node->left;
        else
            node = node->right;
    }
    if (z == nullptr) {
        return false; // Key not found, return false
    }
    Node2* x;
    Node2* y = z;
    Color yOriginalColor = y->color;
    if (z->left == nullptr) {
        x = z->right;
        fixDoubleBlack(z);
    } else if (z->right == nullptr) {
        x = z->left;
        fixDoubleBlack(z);
    } else {
        y = minValueNode(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            fixDoubleBlack(y);
            y->right = z->right;
            y->right->parent = y;
        }
        fixDoubleBlack(z);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        y->parent = z->parent;
        if (z->parent == nullptr)
            root = y;
        else if (z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
        delete z;
        if (yOriginalColor == BLACK)
            fixDoubleBlack(x);
    }
    return true; // Deletion successful, return true
}

void RedBlackTree::fixDoubleBlack(Node2* x) {
    if (x == root)
        return;
    Node2* sibling = nullptr;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            sibling = x->parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                sibling = x->parent->right;
            }
            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rotateRight(sibling);
                    sibling = x->parent->right;
                }
                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            sibling = x->parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                sibling = x->parent->left;
            }
            if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rotateLeft(sibling);
                    sibling = x->parent->left;
                }
                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlackTree::deleteTree() {
    deleteTreeHelper(root);
    root = nullptr;
}

void RedBlackTree::deleteTreeHelper(Node2* node) {
    if (node == nullptr)
        return;
    deleteTreeHelper(node->left);
    deleteTreeHelper(node->right);
    delete node;
}

void RedBlackTree::readDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file: " << filename << std::endl;
        return;
    }
    std::string value;
    while (std::getline(file, value)) {
        insert(value);
    }
    file.close();
}

void RedBlackTree::saveTreeToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
        return;
    }
    saveTreeHelper(root, file);
    file.close();
}

void RedBlackTree::saveTreeHelper(Node2* node, std::ofstream& file) {
    if (node == nullptr) return;
    // Write node data and color to file
    file << node->value << " " << (node->color == RED ? "RED" : "BLACK") << std::endl;
    saveTreeHelper(node->left, file);
    saveTreeHelper(node->right, file);
}
