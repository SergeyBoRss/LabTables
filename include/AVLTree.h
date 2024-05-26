//
// Created by Sergey on 13.05.2024.
//

#include <string>
#include "Polynomial.h"

using namespace std;

class AVLTreeNode {
public:
    string key;
    Polynomial pol;
    AVLTreeNode *left;
    AVLTreeNode *right;
    int height;

    AVLTreeNode(const string &key, Polynomial &pol)
            : key(key), pol(pol), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLTreeNode *root;

    int height(AVLTreeNode *node);

    int balanceTr(AVLTreeNode *node);

    AVLTreeNode *rightRot(AVLTreeNode *y);

    AVLTreeNode *leftRot(AVLTreeNode *x);

    AVLTreeNode *minNode(AVLTreeNode *node);

    AVLTreeNode *insert(AVLTreeNode *node, const string &key, Polynomial &value);

    AVLTreeNode *remove(AVLTreeNode *node, const string &key);

    AVLTreeNode *find(AVLTreeNode *node, const string &key);

    void print(AVLTreeNode *node);

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree();

    void addPol(const string &key, Polynomial &pol);

    void removePol(const string &key);

    Polynomial *findPol(const string &key);

    void print();
};