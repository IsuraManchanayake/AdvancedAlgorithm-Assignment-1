#include <stdexcept>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

class BST {
public:
    BST();
    size_t height();
    bool isEmpty(void) const;
    size_t size(void) const;
    bool contains(int key) const;
    int get(int key) const;
    void put(int key, int val);
    void deleteMin(void);
    void deleteMax(void);
    void del(int key);
    int min(void);
    int max(void);
    void print_in_order(void) const;
private:
    struct Node;
    Node* root;
    size_t size(Node* x) const;
    Node* get(Node* x, int key) const;
    Node* put(Node* x, int key, int val);
    Node* deleteMin(Node* x);
    Node* deleteMax(Node* x);
    Node* del(Node* x, int key);
    Node* minNode(Node* x);
    Node* maxNode(Node* x);
    size_t height(Node* x);
    void print_in_order(Node* x) const;
};

struct BST::Node {
    int key;
    int val;
    Node* left;
    Node* right;
    size_t size;

    Node(int key, int val, size_t size)
        : key(key), val(val), size(size), left(nullptr), right(nullptr) {}
};
    
BST::BST() : root(nullptr) {}

bool BST::isEmpty(void) const {
    return size() == 0;
}

size_t BST::size(void) const {
    return size(root);
}

size_t BST::size(Node* x) const {
    if(x == nullptr) return 0;
    return x->size;
}

bool BST::contains(int key) const {
    return get(root, key) != nullptr;
}

int BST::get(int key) const {
    Node* n = get(root, key);
    if(n == nullptr) throw std::runtime_error("key not found"); 
    return n->val;
}

BST::Node* BST::get(Node* x, int key) const {
    if(x == nullptr) return nullptr;
    if(key < x->key) return get(x->left, key);
    else if(key > x->key) return get(x->right, key);
    return x;
}

void BST::put(int key, int val) {
    root = put(root, key, val);
}

BST::Node* BST::put(Node* x, int key, int val) {
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

void BST::deleteMin(void) {
    if(isEmpty()) {
        throw new std::runtime_error("Empty tree");
    }
    root = deleteMin(root);
}

BST::Node* BST::deleteMin(Node* x) {
    if(x->left == nullptr) {
        Node* right = x->right;
        delete x;
        return right;
    }
    x->left = deleteMin(x->left);
    x->size = size(x->left) + size(x->right) + 1;
    return x;
}

void BST::deleteMax(void) {
    if(isEmpty()) {
        throw new std::runtime_error("Empty tree");
    }
    root = deleteMax(root);
}

BST::Node* BST::deleteMax(Node* x) {
    if(x->right == nullptr) {
        Node* left = x->left;
        delete x;
        return left;
    }
    x->right = deleteMax(x->right);
    x->size = size(x->left) + size(x->right) + 1;
    return x;
}

void BST::del(int key) {
    root = del(root, key);
}

BST::Node* BST::del(Node* x, int key) {
    if(x == nullptr) {
        return nullptr;
    }
    if(key < x->key) {
        x->left = del(x->left, key);
    } else if(key > x->key) {
        x->right = del(x->right, key);
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
        Node *t = minNode(x->right);
        x->key = t->key;
        x->right = del(x->right, t->key);
    }
    x->size = size(x->left) + size(x->right) + 1;
    return x;
}

int BST::min(void) {
    return minNode(root)->key;
}

BST::Node* BST::minNode(Node* x) {
    if(x->left == nullptr) {
        return x;
    }
    return minNode(x->left);
}

int BST::max(void) {
    return maxNode(root)->key;
}

BST::Node* BST::maxNode(Node* x) {
    if(x->right == nullptr) {
        return x;
    }
    return maxNode(x->right);
}

size_t BST::height() {
    return height(root);
}

size_t BST::height(Node* x) {
    if(x == nullptr) {
        return 0;
    }
    size_t left_h = height(x->left) + 1;
    size_t right_h = height(x->right) + 1;
    return left_h < right_h ? right_h : left_h;
}

void BST::print_in_order(void) const {
    print_in_order(root);
    cout << '\n';
}

void BST::print_in_order(Node* x) const {
    if(x != nullptr) {
        print_in_order(x->left);
        cout << x->key << ' ';
        print_in_order(x->right);
    }
}