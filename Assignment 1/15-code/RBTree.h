#include <stdexcept>
#include <iostream>

struct RBTree {
    enum class Color {
        red,
        black
    };

    struct Node {
        int key;
        int val;
        Node* left;
        Node* right;
        Color col;
        size_t size;

        Node(int key, int val, Color col, size_t size)
            : key(key), val(val), col(col), size(size), left(nullptr), right(nullptr) {}
    };

    Node* root;

    RBTree() : root(nullptr) {}

    bool isRed(Node* x) const {
        if(x == nullptr) return false;
        return x->col == Color::red;
    }

    size_t size(Node* x) const {
        if(x == nullptr) return 0;
        return x->size;
    }

    size_t size(void) const {
        return size(root);
    }

    bool isEmpty(void) const {
        return size() == 0;
    }

    int get(int key) const {
        Node* n = get(root, key);
        if(n == nullptr) {
            throw new std::runtime_error("Key not found");
        }
        return n->val;
    }

    Node* get(Node* x, int key) const {
        while(x != nullptr) {
            if(key < x->key) {
                x = x->left;
            } else if(key > x->key) {
                x = x->right;
            } else {
                return x;
            }
        }
        return nullptr;
    }

    bool contains(int key) const {
        return get(root, key) != nullptr;
    }

    void put(int key, int val) {
        root = put(root, key, val);
        root->col = Color::black;
    }

    Node* put(Node* h, int key, int val) {
        if(h == nullptr) {
            return new Node(key, val, Color::red, 1);
        }

        if(key < h->key) {
            h->left = put(h->left, key, val);
        } else if(key > h->key) {
            h->right = put(h->right, key, val);
        } else {
            h->val = val;
        }

        if(isRed(h->right) && !isRed(h->left)) {
            h = rotateLeft(h);
        }
        if(isRed(h->left) && isRed(h->left->left)) {
            h = rotateRight(h);
        }
        if(isRed(h->left) && isRed(h->right)) {
            flipColors(h);
        }
        h->size = size(h->left) + size(h->right) + 1;
        return h;
    }

    void deleteMin(void) {
        if(isEmpty()) {
            throw new std::runtime_error("Empty RBTree");
        }
        if(!isRed(root->left) && !isRed(root->right)) {
            root->col = Color::red;
        }
        root = deleteMin(root);
        if(!isEmpty()) root->col = Color::black;
    }

    Node* deleteMin(Node* h) {
        if(h->left == nullptr) {
            return nullptr;
        }
        if(!isRed(h->left) && !isRed(h->left->left)) {
            h = moveRedLeft(h);
        }
        h->left = deleteMin(h->left);
        return balance(h);
    }

    void deleteMax(void) {
        if(isEmpty()) {
            throw new std::runtime_error("Empty RBTree");
        }
        if(!isRed(root->left) && !isRed(root->right)) {
            root->col = Color::red;
        }
        root = deleteMax(root);
        if(!isEmpty()) root->col = Color::black;
    }

    Node* deleteMax(Node* h) {
        if(isRed(h->left)) {
            h = rotateRight(h);
        }
        if(h->right == nullptr) {
            return nullptr;
        }
        if(!isRed(h->right) && !isRed(h->right->left)) {
            h = moveRedRight(h);
        }
        h->right = deleteMax(h->right);
        return balance(h);
    }

    void delNode(int key) {
        if(!contains(key)) {
            return;
        }
        if(!isRed(root->left) && !isRed(root->right)) {
            root->col = Color::red;
        }
        root = delNode(root, key);
        if(!isEmpty()) {
            root->col = Color::black;
        }
    }

    Node* delNode(Node* h, int key) {
        if(key < h->key) {
            if(!isRed(h->left) && !isRed(h->left->left)) {
                h = moveRedLeft(h);
            }
            h->left = delNode(h->left, key);
        } else {
            if(isRed(h->left)) {
                h = rotateRight(h);
            }
            if(key == h->key && h->right == nullptr) {
                return nullptr;
            }
            if(!isRed(h->right) && !isRed(h->right->left)) {
                h = moveRedRight(h);
            }
            if(key == h->key) {
                Node* x = minNode(h->right);
                h->key = x->key;
                h->val = x->val;
                h->right = deleteMin(h->right);
            } else {
                h->right = delNode(h->right, key);
            }
        }
        return balance(h);
    }

    Node* rotateRight(Node* h) {
        Node* x = h->left;
        h->left = x->right;
        x->right = h;
        x->col = x->right->col;
        x->right->col = Color::red;
        x->size = h->size;
        h->size = size(h->left) + size(h->right) + 1;
        return x;
    }

    Node* rotateLeft(Node* h) {
        Node* x = h->right;
        h->right = x->left;
        x->left = h;
        x->col = x->left->col;
        x->left->col = Color::red;
        x->size = h->size;
        h->size = size(h->left) + size(h->right) + 1;
        return x;
    }

    Color opp(Color col) {
        return col == Color::red ? Color::black : Color::red;
    }

    void flipColors(Node* h) {
        h->col = opp(h->col);
        h->left->col = opp(h->left->col);
        h->right->col = opp(h->right->col);
    }

    Node* moveRedLeft(Node* h) {
        flipColors(h);
        if(isRed(h->right->left)) {
            h->right = rotateRight(h->right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    Node* moveRedRight(Node* h) {
        flipColors(h);
        if(isRed(h->left->left)) {
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

    Node* balance(Node* h) {
        if(isRed(h->right)) {
            h = rotateLeft(h);
        }
        if(isRed(h->left) && isRed(h->left->left)) {
            h = rotateRight(h);
        }
        if(isRed(h->left) && isRed(h->right)) {
            flipColors(h);
        }
        h->size = size(h->left) + size(h->right) + 1;
        return h;
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

    int minNode(void) const {
        if(isEmpty()) {
            throw new std::runtime_error("Empty tree");
        }
        return minNode(root)->key;
    }

    Node* minNode(Node* x) const {
        if(x->left == nullptr) {
            return x;
        } 
        return minNode(x->left);
    }

    int maxNode(void) const {
        if(isEmpty()) {
            throw new std::runtime_error("Empty tree");
        }
        return maxNode(root)->key;
    }

    Node* maxNode(Node* x) const {
        if(x->right == nullptr) {
            return x;
        } 
        return maxNode(x->right);
    }
};