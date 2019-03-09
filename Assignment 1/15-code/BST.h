#include <stdexcept>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

struct BST {
    struct Node {
        int key;
        int val;
        Node* left;
        Node* right;
        size_t size;

        Node(int key, int val, size_t size)
            : key(key), val(val), size(size), left(nullptr), right(nullptr) {}
    };

    Node* root;
    
    BST() { root = nullptr; }

    bool isEmpty(void) const {
        return size() == 0;
    }

    size_t size(void) const {
        return size(root);
    }

    size_t size(Node* x) const {
        if(x == nullptr) return 0;
        return x->size;
    }

    bool contains(int key) const {
        return get(root, key) != nullptr;
    }

    int get(int key) const {
        Node* n = get(root, key);
        if(n == nullptr) throw std::runtime_error("key not found"); 
        return n->val;
    }

    Node* get(Node* x, int key) const {
        if(x == nullptr) return nullptr;
        if(key < x->key) return get(x->left, key);
        else if(key > x->key) return get(x->right, key);
        return x;
    }

    void put(int key, int val) {
        root = put(root, key, val);
    }

    Node* put(Node* x, int key, int val) {
        if(x == nullptr) return new Node(key, val, 1);
        if(key < x->key) {
            x->left = put(x->left, key, val);
        } else if(key > x->key) {
            x->right = put(x->right, key, val);
        } else {
            x->val = val;
        }
        x->size = 1 + size(x->left) + size(x->right);
        return x;
    }

    void deleteMin(void) {
        if(isEmpty()) {
            throw new std::runtime_error("Empty tree");
        }
        root = deleteMin(root);
    }

    Node* deleteMin(Node* x) {
        if(x->left == nullptr) {
            Node* right = x->right;
            delete x;
            return right;
        }
        x->left = deleteMin(x->left);
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }

    void delteMax(void) {
        if(isEmpty()) {
            throw new std::runtime_error("Empty tree");
        }
        root = delteMax(root);
    }

    Node* delteMax(Node* x) {
        if(x->right == nullptr) {
            Node* left = x->left;
            delete x;
            return left;
        }
        x->right = delteMax(x->right);
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }

    void delNode(int key) {
        root = delNode(root, key);
    }

    Node* delNode(Node* x, int key) {
        if(x == nullptr) {
            return nullptr;
        }
        if(key < x->key) {
            x->left = delNode(x->left, key);
        } else if(key > x->key) {
            x->right = delNode(x->right, key);
        } else {
            if(x->right == nullptr) {
                Node* left = x->left;
                delete x;
                return left;
            }
            if(x->left == nullptr) {
                Node* right = x->right;
                delete x;
                return right;
            }
            Node* t = x;
            x = minNode(t->right);
            x->right = deleteMin(t->right);
            x->left = t->left;
        }
        x->size = size(x->left) + size(x->right) + 1;
        return x;
    }

    int min(void) {
        return minNode(root)->key;
    }

    Node* minNode(Node* x) {
        if(x->left == nullptr) {
            return x;
        }
        return minNode(x->left);
    }

    int max(void) {
        return maxNode(root)->key;
    }

    Node* maxNode(Node* x) {
        if(x->right == nullptr) {
            return x;
        }
        return maxNode(x->right);
    }

    size_t height() {
        return height(root);
    }

    size_t height(Node* x) {
        if(x == nullptr) {
            return 0;
        }
        size_t left_h = height(x->left) + 1;
        size_t right_h = height(x->right) + 1;
        return left_h < right_h ? right_h : left_h;
    }
};