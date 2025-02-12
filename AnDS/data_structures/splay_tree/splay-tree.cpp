#include "splay-tree.h"

#include <iostream>

Node::Node(int key, Node *parent) : key(key), left(nullptr), right(nullptr), parent(parent) {}

SplayTree::SplayTree() : root(nullptr) {}

SplayTree::~SplayTree() {
    clear(root);
}

void SplayTree::insert(int key) {
    Node *node = root;
    if (node == nullptr) {
        root = new Node(key, nullptr);
        return;
    }
    while (node != nullptr) {
        if (key < node->key) {
            if (node->left == nullptr) {
                node->left = new Node(key, node);
                return;
            }
            node = node->left;
        } else if (key > node->key) {
            if (node->right == nullptr) {
                node->right = new Node(key, node);
                return;
            }
            node = node->right;
        } else {
            return;
        }
    }
}

Node *SplayTree::find(int key) const {
    Node *node = root;
    while (node != nullptr) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            return node;
        }
    }
    return nullptr;
}

void SplayTree::rotateLeft(Node *node) {
    Node *parent = node->parent;
    Node *right = node->right;

    if (parent != nullptr) {
        if (parent->left == node) {
            parent->left = right;
        } else {
            parent->right = right;
        }
    }

    Node *temp = right->left;
    right->left = node;
    node->right = temp;
    node->parent = right;
    right->parent = parent;

    if (node->right != nullptr) {
        node->right->parent = node;
    }
}

void SplayTree::rotateRight(Node *node) {
    Node *parent = node->parent;
    Node *left = node->left;

    if (parent != nullptr) {
        if (parent->left == node) {
            parent->left = left;
        } else {
            parent->right = left;
        }
    }

    Node *temp = left->right;
    left->right = node;
    node->left = temp;
    node->parent = left;
    left->parent = parent;

    if (node->left != nullptr) {
        node->left->parent = node;
    }
}

int SplayTree::splay(Node *node) {
    int rotations = 0;
    while (node->parent != nullptr) {
        if (node == node->parent->left) {
            if (node->parent->parent == nullptr) {
                rotateRight(node->parent);
                rotations++;
            } else if (node->parent == node->parent->parent->left) {
                rotateRight(node->parent->parent);
                rotations++;
                rotateRight(node->parent);
                rotations++;
            }  else {
                rotateRight(node->parent);
                rotateLeft(node->parent);
                rotations++;
            }
        } else {
            if (node->parent->parent == nullptr) {
                rotateLeft(node->parent);
                rotations++;
            } else if (node->parent == node->parent->parent->right) {
                rotateLeft(node->parent->parent);
                rotations++;
                rotateLeft(node->parent);
                rotations++;
            } else {
                rotateLeft(node->parent);
                rotateRight(node->parent);
                rotations++;
            }
        }
    }
    root = node;
    return rotations;
}

int SplayTree::getHeight() const {
    return getHeight(root);
}

int SplayTree::getHeight(Node *node) const {
    if (node == nullptr) {
        return 0;
    }
    return (node == root ? 0 : 1) + std::max(getHeight(node->left), getHeight(node->right));
}

void SplayTree::clear(Node *node) {
    if (node == nullptr) {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}