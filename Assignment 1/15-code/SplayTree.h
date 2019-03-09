#include <stdexcept>
#include <iostream>

struct SplayTree {
    struct Node {
        int key;
        int val;
        Node* left;
        Node* right;

        Node(int key, int val) 
            : key(key), val(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    SplayTree() : root(nullptr) {}

    bool contains(int key) {
        return get(key) != nullptr;
    }

    Node* get(int key) {
        root = splay(root, key);
        if(key == root->key) {
            return root;
        }
        return nullptr;
    }

    void put(int key, int val) {
        if(root == nullptr) {
            root = new Node(key, val);
            return;
        }
        root = splay(root, key);
        if(key < root->key) {
            Node* n = new Node(key, val);
            n->left = root->left;
            n->right = root;
            root->left = nullptr;
            root = n;
        } else if(key > root->key) {
            Node* n = new Node(key, val);
            n->right = root->right;
            n->left = root;
            root->right = nullptr;
            root = n;
        } else {
            root->val = val;
        }
    }

    void delNode(int key) {
        if(root == nullptr) {
            return;
        }
        root = splay(root, key);
        if(key == root->key) {
            if(root->left == nullptr) {
                root = root->right;
            } else {
                Node* x = root->right;
                root = root->left;
                splay(root, key);
                root->right = x;
            }
        }
    }

    Node* splay(Node* h, int key) {
        if(h == nullptr) {
            return nullptr;
        }
        if(key < h->key) {
            if(h->left == nullptr) {
                return h;
            }
            if(key < h->left->key) {
                h->left->left = splay(h->left->left, key);
                h = rotateRight(h);
            } else if(key > h->left->key) {
                h->left->right = splay(h->left->right, key);
                if(h->left->right != nullptr) {
                    h->left = rotateLeft(h->left);
                }
            }
            if(h->left == nullptr) {
                return h;
            } else {
                return rotateRight(h);
            }
        } else if(key > h->key) {
            if(h->right == nullptr) {
                return h;
            }
            if(key < h->right->key) {
                h->right->left = splay(h->right->left, key);
                if(h->right->left != nullptr) {
                    h->right = rotateRight(h->right);
                }
            } else if(key > h->right->key) {
                h->right->right = splay(h->right->right, key);
                h = rotateLeft(h);
            }
            if(h->right == nullptr) {
                return h;
            } else {
                return rotateLeft(h);
            }
        } else {
            return h;
        }
    }

    size_t height(void) const {
        return height(root);
    }

    size_t height(Node* x) const {
        if(x == nullptr) {
            return 0;
        }
        size_t left_h = height(x->left) + 1;
        size_t right_h = height(x->right) + 1;
        return left_h > right_h ? left_h : right_h;
    }

    size_t size(void) const {
        return size(root);
    }

    size_t size(Node* x) const {
        if(x == nullptr) {
            return 0;
        }
        return 1 + size(x->left) + size(x->right);
    }

    Node* rotateRight(Node* h) {
        Node* x = h->left;
        h->left = x->right;
        x->right = h;
        return x;
    }

    Node* rotateLeft(Node* h) {
        Node* x = h->right;
        h->right = x->left;
        x->left = h;
        return x;
    }
};