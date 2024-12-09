#include "rbtree.h"
#include <iostream>

Node::Node(int key) {
    height = 0;
    size = 1;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    this->key = key;
    color = Color::RED;
}

RBTree::RBTree() {
    root = nullptr;
}

RBTree::RBTree(std::initializer_list<int> list) : RBTree() {
    for (int key : list) {
        insert(key);
    }
}

RBTree::~RBTree() = default;

void updateSizeAndHeight(Node *node) {
    while (node != nullptr) {
        int leftHeight = node->left == nullptr ? 0 : node->left->height;
        int rightHeight = node->right == nullptr ? 0 : node->right->height;
        node->height = std::max(leftHeight, rightHeight) + (node->color == Color::BLACK ? 1 : 0);
        node->size = (node->left == nullptr ? 0 : node->left->size) + (node->right == nullptr ? 0 : node->right->size) + 1;
        node = node->parent;
    }
}

void rotateRight(Node *&root, Node *node) {
    Node *left = node->left;
    node->left = left->right;

    if (left->right != nullptr) {
        left->right->parent = node;
    }

    left->parent = node->parent;
    if (node->parent == nullptr) {
        root = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }

    left->right = node;
    node->parent = left;

    updateSizeAndHeight(node);
    updateSizeAndHeight(left);
}

void rotateLeft(Node *&root, Node *node) {
    Node *right = node->right;
    node->right = right->left;

    if (right->left != nullptr) {
        right->left->parent = node;
    }

    right->parent = node->parent;
    if (node->parent == nullptr) {
        root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }

    right->left = node;
    node->parent = right;

    updateSizeAndHeight(node);
    updateSizeAndHeight(right);
}

void insertFix(Node *&root, Node *node) {
    while (node != root && node->parent->color == Color::RED) {
        if (node->parent == node->parent->parent->left) {
            Node *uncle = node->parent->parent->right;
            if (uncle != nullptr && uncle->color == Color::RED) {
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(root, node);
                }
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                rotateRight(root, node->parent->parent);
            }
        } else {
            Node *uncle = node->parent->parent->left;
            if (uncle != nullptr && uncle->color == Color::RED) {
                node->parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(root, node);
                }
                node->parent->color = Color::BLACK;
                node->parent->parent->color = Color::RED;
                rotateLeft(root, node->parent->parent);
            }
        }
    }
    root->color = Color::BLACK;
}

void seeTree(Node *node, int level = 0) {
    if (node == nullptr) {
        return;
    }
    seeTree(node->right, level + 1);
    for (int i = 0; i < level; i++) {
        std::cout << "    ";
    }
    std::cout << node->key << " " << (node->color == Color::RED ? "R" : "B") << std::endl;
    seeTree(node->left, level + 1);
}

void seeSizesandHeights(Node *node) {
    if (node == nullptr) {
        return;
    }
    seeSizesandHeights(node->left);
    std::cout << "Key: " << node->key << " Size: " << node->size << " Height: " << node->height << std::endl;
    seeSizesandHeights(node->right);
}

void RBTree::insert(int key) {
    Node *node = new Node(key);
    node->left = nullptr;
    node->right = nullptr;

    Node *current = root;
    Node *parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (key == current->key) {
            return;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;
    if (parent == nullptr) {
        root = node;
    } else if (key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }

    updateSizeAndHeight(node);

    if (node->parent == nullptr) {
        node->color = Color::BLACK;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    insertFix(root, node);

//    seeTree(root);
//    seeSizesandHeights(root);
}

int *RBTree::find(int key) {
    Node *current = root;
    while (current != nullptr) {
        if (key == current->key) {
            return &(current->key);
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr;
}

int RBTree::size() const {
    return root == nullptr ? 0 : root->size;
}

int *RBTree::lowerBound(int key) {
    Node *current = root;
    Node *result = nullptr;
    while (current != nullptr) {
        if (key == current->key) {
            return &(current->key);
        } else if (key <= current->key) {
            result = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (result == nullptr) {
        return nullptr;
    }
    return &(result->key);
}

bool RBTree::empty() const {
    return root == nullptr;
}

void RBTree::erase(int key) {
    Node *current = root;
    while (current != nullptr) {
        if (key == current->key) {
            break;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) {
        return;
    }

    Node *node = current;
    Color originalColor = node->color;
    Node *x;
    if (current->left == nullptr) {
        x = current->right;
        transplant(root, current, current->right);
    } else if (current->right == nullptr) {
        x = current->left;
        transplant(root, current, current->left);
    } else {
        node = minimum(current->right);
        originalColor = node->color;
        x = node->right;
        if (node->parent == current) {
            if (x != nullptr) {
                x->parent = node;
            }
        } else {
            transplant(root, node, node->right);
            node->right = current->right;
            node->right->parent = node;
        }
        transplant(root, current, node);
        node->left = current->left;
        node->left->parent = node;
        node->color = current->color;
    }

    if (originalColor == Color::BLACK) {
        eraseFix(root, x);
    }

    updateSizeAndHeight(x);
}

int RBTree::height() const {
    return root == nullptr ? 0 : root->height;
}