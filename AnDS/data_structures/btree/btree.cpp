#include <iostream>

#include "btree.h"

Node::Node(int t) {
    this->t = t;
    this->isLeaf = true;
    this->parent = nullptr;
}

BTree::BTree(int t) {
    this->t_ = t;
    this->root = nullptr;
    this->size_ = 0;
}

void clear(Node* node) {
    if (node == nullptr) {
        return;
    }
    for (auto child : node->children) {
        clear(child);
    }
    delete node;
}

BTree::~BTree() {
    clear(root);
}

size_t BTree::size() const {
    return root != nullptr ? static_cast<size_t>(size_) : 0;
}

bool find(Node* node, int key) {
    if (node == nullptr) {
        return false;
    }
    int i = 0;
    while (i < node->key.size() && key > node->key[i]) {
        ++i;
    }
    if (i < node->key.size() && key == node->key[i]) {
        return true;
    }
    if (node->isLeaf) {
        return false;
    }
    return find(node->children[i], key);
}

int64_t calcSum(Node* node) {
    if (node->isLeaf) {
        int64_t sum = 0;
        for (int key : node->key) {
            sum += key;
        }
        return sum;
    }
    int64_t sum = 0;
    for (auto child : node->children) {
        sum += calcSum(child);
    }
    return sum;
}

int64_t BTree::sum() const {
    return root != nullptr ? calcSum(root) : 0;
}

void insert_to_leaf(Node* node, int key) {
    int i = 0;
    while (i < node->key.size() && key > node->key[i]) {
        ++i;
    }
    node->key.insert(node->key.begin() + i, key);
}

void split_child(Node* node, int i, int& size) {
    Node* new_node = new Node(node->t);
    Node* child = node->children[i];
    new_node->isLeaf = child->isLeaf;

    for (int i = 0; i < node->t - 1; ++i) {
        new_node->key.push_back(child->key[i + node->t]);
    }

    if (!child->isLeaf) {
        for (int i = 0; i < node->t; ++i) {
            new_node->children.push_back(child->children[i + node->t]);
            new_node->children[i]->parent = new_node;
        }
    }

    child->key.resize(node->t - 1);
    if (!child->isLeaf) {
        child->children.resize(node->t);
    }
    node->children.insert(node->children.begin() + i + 1, new_node);
    node->key.insert(node->key.begin() + i, child->key[node->t - 1]);

    new_node->parent = node;
    ++size;
}

void insert_non_full(Node* node, int key, const int& t, int& size) {
    if (node->isLeaf) {
        insert_to_leaf(node, key);
        return;
    }
    int i = 0;
    while (i < node->key.size() && key > node->key[i]) {
        ++i;
    }
    if (node->children[i]->key.size() == 2 * t - 1) {
        split_child(node, i, size);
        if (key > node->key[i]) {
            ++i;
        }
    }
    insert_non_full(node->children[i], key, t, size);
}

void BTree::insert(int key) {
    if (find(root, key)) {
        return;
    }
    if (root == nullptr) {
        root = new Node(this->t_);
        root->key.push_back(key);
        ++size_;
        return;
    }
    if (root->key.size() == 2 * t_ - 1) {
        Node* new_root = new Node(t_);
        new_root->isLeaf = false;
        new_root->children.push_back(root);
        root->parent = new_root;
        root = new_root;
        split_child(root, 0, size_);
        ++size_;
    }
    insert_non_full(root, key, t_, size_);
}
