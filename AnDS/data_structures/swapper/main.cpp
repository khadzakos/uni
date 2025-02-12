#include <iostream>
#include <random>

std::mt19937 rnd(time(0));

struct Node {
    Node(int val) : val(val), priority(rnd() << 16u), size(1), sum(val), left(nullptr), right(nullptr) {}

    int val;
    int priority;
    int size;
    int sum;
    Node* left;
    Node* right;
};

class Treap {
public:
    Node* root;

    Treap() {
        root = nullptr;
    }

    ~Treap() {
        clear(root);
    }

    std::pair<Node*, Node*> Split(Node* node, int pos) {
        return split(node, pos);
    }

    Node* Merge(Node* left, Node* right) {
        return merge(left, right);
    }

    void Insert(int val) {
        insert(val);
    }

    int Sum(int left, int right) {
//        std::cout << "Sum:\n";
//        std::cout << left << ' ' << right << '\n';
        if (left > right) {
            return 0;
        }
        std::pair<Node*, Node*> p1 = split(root, right);
//        std::cout << sum(p1.first) << ' ' << sum(p1.second) << '\n';
        std::pair<Node*, Node*> p2 = split(p1.first, left - 1);
//        std::cout << sum(p2.first) << ' ' << sum(p2.second) << '\n';
        int result = sum(p2.second);
        std::cout << "hui: " << result << '\n';
        root = merge(merge(p2.first, p2.second), p1.second);
        return result;
    }

    void See() {
        see(root);
    }

    void See(Node* node) {
        see(node);
    }
private:

    int size(Node* node) {
        return node == nullptr ? 0 : node->size;
    }

    int sum(Node* node) {
        return node == nullptr ? 0 : node->sum;
    }

    void calc(Node* node) {
        if (node == nullptr) {
            return;
        }
        node->size = 1 + size(node->left) + size(node->right);
        node->sum = node->val + sum(node->left) + sum(node->right);
    }

    std::pair<Node*, Node*> split(Node* node, int pos) {
        if (node == nullptr) {
            return {nullptr, nullptr};
        }

        if (size(node->left) + 1 <= pos) {
            std::pair<Node*, Node*> p = split(node->right, pos - size(node->left) - 1);
            node->right = p.first;
            calc(node);
            return {node, p.second};
        } else {
            std::pair<Node*, Node*> p = split(node->left, pos);
            node->left = p.second;
            calc(node);
            return {p.first, node};
        }
    }

    Node* merge(Node* left, Node* right) {
        if (left == nullptr) {
            return right;
        }
        if (right == nullptr) {
            return left;
        }

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            calc(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            calc(right);
            return right;
        }
    }

    void insert(int val) {
        root = merge(root, new Node(val));
    }

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void see(Node* node) {
        if (node == nullptr) {
            return;
        }
        see(node->left);
        std::cout << node->val << ' ';
        see(node->right);
    }
};

void Swap(Treap& even, Treap& odd, int left, int right) {
    std::cout << left << ' ' << right << '\n';
    std::pair<Node*, Node*> p1 = even.Split(even.root, right / 2);
    std::pair<Node*, Node*> p2 = odd.Split(odd.root, right / 2);
    std::pair<Node*, Node*> p3 = even.Split(p1.first, left / 2 - 1);
    std::pair<Node*, Node*> p4 = odd.Split(p2.first, left / 2 - 1);
    std::cout << "P1: ";
    even.See(p1.first);
    std::cout << '\n';
    even.See(p1.second);
    std::cout << '\n';
    std::cout << "P2: ";
    odd.See(p2.first);
    std::cout << '\n';
    odd.See(p2.second);
    std::cout << '\n';
    std::cout << "P3: ";
    even.See(p3.first);
    std::cout << '\n';
    even.See(p3.second);
    std::cout << '\n';
    std::cout << "P4: ";
    odd.See(p4.first);
    std::cout << '\n';
    odd.See(p4.second);
    std::cout << '\n';
    even.root = even.Merge(even.Merge(p3.first, p4.second), p1.second);
    odd.root = odd.Merge(odd.Merge(p4.first, p3.second), p2.second);
}

int main() {
    int n, m;
    for (int swapper = 1; ; ++swapper) {
        std::cin >> n >> m;
        if (n == 0 && m == 0) {
            break;
        }
        Treap even, odd;
        for (int i = 1; i <= n; ++i) {
            int val;
            std::cin >> val;
            if (i % 2 == 0) {
                even.Insert(val);
            } else {
                odd.Insert(val);
            }
        }

        even.See();
        std::cout << '\n';
        odd.See();
        std::cout << '\n';

        std::cout << "Swapper " << swapper << ":\n";
        for (int i = 0; i < m; ++i) {
            int type, left, right;
            std::cin >> type >> left >> right;
            if (type == 1) {
                if (left % 2) {
                    Swap(even, odd, left / 2, right / 2);
                } else {
                    Swap(even, odd, left / 2 + 1, right / 2 + 1);
                }
            } else {
//                std::cout << left << ' ' << right << '\n';
                if (left % 2 == 0 && right % 2 == 0) {
                    std::cout << even.Sum(left / 2, right / 2) + odd.Sum(left / 2 + 1, right / 2) << '\n';
                } else if (left % 2 == 0 && right % 2 == 1) {
                    std::cout << even.Sum(left / 2, right / 2) + odd.Sum(left / 2, right / 2) << '\n';
                } else if (left % 2 == 1 && right % 2 == 0) {
                    std::cout << even.Sum(left / 2 + 1, right / 2) + odd.Sum(left / 2, right / 2 - 1) << '\n';
                } else {
                    std::cout << even.Sum(left / 2, right / 2) + odd.Sum(left / 2, right / 2 + 1) << '\n';
                }

            }
            even.See();
            std::cout << '\n';
            odd.See();
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    return 0;
}
