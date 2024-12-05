#include <iostream>

#include "avl_tree.h"

Node::Node(int value) {
    height = 1;
    left = nullptr;
    right = nullptr;
    this->value = value;
}

Node::~Node() = default;

AVLTree::AVLTree() : root_(nullptr), size_(0) {}

AVLTree::AVLTree(int value) : root_(new Node(value)), size_(0) {}

int AVLTree::getHeight() {
    return getNodeHeight(root_);
}

void AVLTree::insert(int value) {
    root_ = insertNode(root_, value);
}

void AVLTree::erase(int value) {
    root_ = removeNode(root_, value);
}

int *AVLTree::find(int value) {
    Node *elem = findNode(root_, value);
    if (elem == nullptr) {
        return nullptr;
    }

    return &(elem->value);
}

int *AVLTree::traversal() {
    int *array = new int[size_];
    int index = 0;
    traversalInternal(root_, array, &index);
    return array;
}

int *AVLTree::lowerBound(int value) {
    Node *elem = lowerBoundInternal(root_, value);
    if (elem == nullptr) {
        return nullptr;
    }

    return &(elem->value);
}

bool AVLTree::empty() {
    return root_ == nullptr;
}

Node *AVLTree::getRoot() {
    return root_;
}

int AVLTree::getSize() {
    return size_;
}

AVLTree::~AVLTree() {
    delete root_;
}

int AVLTree::getNodeHeight(Node *node) {
    return node == nullptr ? 0 : node->height;
}

int AVLTree::balanceFactor(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return getNodeHeight(node->right) - getNodeHeight(node->left);
}

void AVLTree::balanceHeight(Node *node) {
    int leftHeight = getNodeHeight(node->left);
    int rightHeight = getNodeHeight(node->right);
    node->height = std::max(leftHeight, rightHeight) + 1;
}

Node *AVLTree::rotateRight(Node *node) {
    Node *left = node->left;
    node->left = left->right;
    left->right = node;
    balanceHeight(node);
    balanceHeight(left);
    return left;
}

Node *AVLTree::rotateLeft(Node *node) {
    Node *right = node->right;
    node->right = right->left;
    right->left = node;
    balanceHeight(node);
    balanceHeight(right);
    return right; 
}

Node *AVLTree::balanceNode(Node *node) {
    balanceHeight(node);
    if (balanceFactor(node) > 1) {
        if (balanceFactor(node->right) < 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    } else if (balanceFactor(node) < -1) {
        if (balanceFactor(node->left) > 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    return node;
}

Node *AVLTree::insertNode(Node *node, int value) {
    if (node == nullptr) {
        ++size_;
        return new Node(value);
    }
    if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    } 
    
    return balanceNode(node);
}

Node *AVLTree::findMinNode(Node *node) {
    if (node->left == nullptr) {
        return node;
    }
    return findMinNode(node->left);
}

Node *AVLTree::removeMinNode(Node *node) {
    if (node->left == nullptr) {
        return node->right;
    }
    node->left = removeMinNode(node->left);
    return balanceNode(node);
}

Node *AVLTree::removeNode(Node *node, int value) {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (value < node->value) {
        node->left = removeNode(node->left, value);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value);
    } else {
        Node *left = node->left;
        Node *right = node->right;
        --size_;
        delete node;
        if (right == nullptr) {
            return left;
        }
        Node *min = findMinNode(right);
        min->right = removeMinNode(right);
        min->left = left;
        return balanceNode(min);
    }
    return balanceNode(node);
}

Node *AVLTree::findNode(Node *node, int value) {
    if (node == nullptr) {
        return nullptr;
    }
    
    if (node->value == value) {
        return node;
    } else if (value < node->value) {
        return findNode(node->left, value);
    } else {
        return findNode(node->right, value);
    }
}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {
    if (node == nullptr) {
        return;
    }
    
    traversalInternal(node->left, array, index);
    array[*(index)] = node->value;
    ++(*index);
    traversalInternal(node->right, array, index);
}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {
    if (current == nullptr) {
        return nullptr;
    }
    
    if (current->value == value) {
        return current;
    } else if (current->value < value) {
        return lowerBoundInternal(current->right, value);
    } else {
        if (current->left == nullptr) {
            return current;
        }
        return lowerBoundInternal(current->left, value);
    }
}
