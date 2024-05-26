//
// Created by Sergey on 13.05.2024.
//

#include "AVLTree.h"
#include <iostream>

using namespace std;

int AVLTree::height(AVLTreeNode *node) {
    if (node == nullptr) {
        return 0;
    } else {
        return node->height;
    }
}

int AVLTree::balanceTr(AVLTreeNode *node) {
    if (node == nullptr) {
        return 0;
    } else {
        return height(node->left) - height(node->right);
    }
}

AVLTreeNode *AVLTree::rightRot(AVLTreeNode *y) {
    AVLTreeNode *x = y->left;
    AVLTreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLTreeNode *AVLTree::leftRot(AVLTreeNode *x) {
    AVLTreeNode *y = x->right;
    AVLTreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLTreeNode *AVLTree::insert(AVLTreeNode *node, const string &key, Polynomial &pol) {
    if (!node) return new AVLTreeNode(key, pol);

    if (key < node->key) {
        node->left = insert(node->left, key, pol);
    } else if (key > node->key) {
        node->right = insert(node->right, key, pol);
    } else {
        node->pol = pol;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceTr(node);

    if (balance > 1 && key < node->left->key) {
        return rightRot(node);
    }
    if (balance < -1 && key > node->right->key) {
        return leftRot(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = leftRot(node->left);
        return rightRot(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRot(node->right);
        return leftRot(node);
    }

    return node;
}

AVLTreeNode *AVLTree::minNode(AVLTreeNode *node) {
    AVLTreeNode *current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

AVLTreeNode *AVLTree::remove(AVLTreeNode *node, const string &key) {
    if (!node) return node;

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if (!node->left || !node->right) {
            AVLTreeNode *temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLTreeNode *temp = minNode(node->right);
            node->key = temp->key;
            node->pol = temp->pol;
            node->right = remove(node->right, temp->key);
        }
    }

    if (!node) return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = balanceTr(node);

    if (balance > 1 && balanceTr(node->left) >= 0) {
        return rightRot(node);
    }
    if (balance > 1 && balanceTr(node->left) < 0) {
        node->left = leftRot(node->left);
        return rightRot(node);
    }
    if (balance < -1 && balanceTr(node->right) <= 0) {
        return leftRot(node);
    }
    if (balance < -1 && balanceTr(node->right) > 0) {
        node->right = rightRot(node->right);
        return leftRot(node);
    }

    return node;
}

AVLTreeNode *AVLTree::find(AVLTreeNode *node, const string &key) {
    while (node != nullptr && key != node->key) {
        if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

void AVLTree::print(AVLTreeNode *node) {
    if (node != nullptr) {
        print(node->left);
        cout << node->key << ": ";
        node->pol.print();
        cout << endl;
        print(node->right);
    }
}

void AVLTree::addPol(const std::string &key, Polynomial &pol) {
    root = insert(root, key, pol);
}

void AVLTree::removePol(const string &key) {
    root = remove(root, key);
}

Polynomial *AVLTree::findPol(const string &key) {
    AVLTreeNode *node = find(root, key);
    if (node != nullptr) {
        return &node->pol;
    } else {
        return nullptr;
    }
}

void AVLTree::print() {
    print(root);
}

void deleteTree(AVLTreeNode *node) {
    if (node == nullptr)
        return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}


AVLTree::~AVLTree() {
    deleteTree(root);
}
