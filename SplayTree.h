#include <stdexcept>
#include <iostream>

struct SplayTree {
public:
    SplayTree();
    bool contains(int key);
    void put(int key, int val);
    void del(int key);
    size_t height(void) const;
    size_t size(void) const;
    void print_in_order(void) const;
private:
    struct Node;
    Node* root;
    Node* get(int key);
    Node* splay(Node* h, int key);
    Node* rotateRight(Node* h);
    Node* rotateLeft(Node* h);
    size_t height(Node* x) const;
    size_t size(Node* x) const;
    void print_in_order(Node* x) const;
};

struct SplayTree::Node {
    int key;
    int val;
    Node* left;
    Node* right;

    Node(int key, int val) 
        : key(key), val(val), left(nullptr), right(nullptr) {}
};

SplayTree::SplayTree() : root(nullptr) {}

bool SplayTree::contains(int key) {
    return get(key) != nullptr;
}

SplayTree::Node* SplayTree::get(int key) {
    root = splay(root, key);
    if(key == root->key) {
        return root;
    }
    return nullptr;
}

void SplayTree::put(int key, int val) {
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

void SplayTree::del(int key) {
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

SplayTree::Node* SplayTree::splay(Node* h, int key) {
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

size_t SplayTree::height(void) const {
    return height(root);
}

size_t SplayTree::height(Node* x) const {
    if(x == nullptr) {
        return 0;
    }
    size_t left_h = height(x->left) + 1;
    size_t right_h = height(x->right) + 1;
    return left_h > right_h ? left_h : right_h;
}

size_t SplayTree::size(void) const {
    return size(root);
}

size_t SplayTree::size(Node* x) const {
    if(x == nullptr) {
        return 0;
    }
    return 1 + size(x->left) + size(x->right);
}

SplayTree::Node* SplayTree::rotateRight(Node* h) {
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    return x;
}

SplayTree::Node* SplayTree::rotateLeft(Node* h) {
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    return x;
}

void SplayTree::print_in_order(void) const {
    print_in_order(root);
    std::cout << '\n';
}

void SplayTree::print_in_order(Node* x) const {
    if(x != nullptr) {
        print_in_order(x->left);
        std::cout << x->key << ' ';
        print_in_order(x->right);
    }
}