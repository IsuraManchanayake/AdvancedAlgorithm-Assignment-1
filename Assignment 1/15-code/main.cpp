#include "BST.h"
#include "RBTree.h"
#include "SplayTree.h"
#include <iostream>

using namespace std;

int main() {
    BST bst;
    for(size_t i = 0; i < 10; i++) {
        bst.put(i, i);
    }
    for(size_t i = 0; i < 10; i++) {
        bst.delNode(i);
    }
    // bst.put(0, 0);
    // bst.put(-4, 0);
    // bst.put(4, 0);
    // bst.put(-5, 0);
    // bst.put(5, 0);
    // bst.put(-3, 0);
    // bst.put(3, 0);

    
    RBTree rbt;
    for(size_t i = 0; i < 10; i++) {
        rbt.put(i, i);
    }
    for(size_t i = 0; i < 10; i++) {
        rbt.delNode(i);
    }
    // rbt.put(0, 0);
    // rbt.put(-4, 0);
    // rbt.put(4, 0);
    // rbt.put(-5, 0);
    // rbt.put(5, 0);
    // rbt.put(-3, 0);
    // rbt.put(3, 0);

    SplayTree spt;
    for(size_t i = 0; i < 10; i++) {
        spt.put(i, i);
    }
    for(size_t i = 0; i < 10; i++) {
        spt.delNode(i);
    }
    // spt.put(0, 0);
    // spt.put(-4, 0);
    // spt.put(4, 0);
    // spt.put(-5, 0);
    // spt.put(5, 0);
    // spt.put(-3, 0);
    // spt.put(3, 0);

    cout << bst.height() << endl;
    cout << rbt.height() << endl;
    cout << spt.height() << endl;
    return 0;
}