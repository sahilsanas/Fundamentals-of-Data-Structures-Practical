//============================================================================
// Name        : Assignment_2.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Binary Search Tree Operations
//============================================================================
#include <iostream>
using namespace std;

class TreeNode {
private:
    int data;
    TreeNode *lchild, *rchild;

public:
    TreeNode(int value) : data(value), lchild(nullptr), rchild(nullptr) {}
    friend class Tree;
};

class Tree {
public:
    TreeNode* root;

    Tree() : root(nullptr) {}

    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }
        if (value < node->data) {
            node->lchild = insert(node->lchild, value);
        } else {
            node->rchild = insert(node->rchild, value);
        }
        return node;
    }

    int longestPath(TreeNode* node) {
        if (node == nullptr) return 0;
        int leftPath = longestPath(node->lchild);
        int rightPath = longestPath(node->rchild);
        return max(leftPath, rightPath) + 1;
    }

    int findMin(TreeNode* node) {
        if (node == nullptr) {
            cout << "Tree is empty!" << endl;
            return -1;
        }
        while (node->lchild != nullptr) {
            node = node->lchild;
        }
        return node->data;
    }

    int findMax(TreeNode* node) {
        if (node == nullptr) {
            cout << "Tree is empty!" << endl;
            return -1;
        }
        while (node->rchild != nullptr) {
            node = node->rchild;
        }
        return node->data;
    }

    void inorder(TreeNode* node) {
        if (node == nullptr) return;
        inorder(node->lchild);
        cout << node->data << " ";
        inorder(node->rchild);
    }

    void swapChildren(TreeNode* node) {
        if (node == nullptr) return;
        swap(node->lchild, node->rchild);
        swapChildren(node->lchild);
        swapChildren(node->rchild);
    }

    TreeNode* search(TreeNode* node, int value) {
        if (node == nullptr || node->data == value) return node;
        if (value < node->data) return search(node->lchild, value);
        return search(node->rchild, value);
    }
};

int main() {
    Tree t;

    t.root = t.insert(t.root, 10);
    t.root = t.insert(t.root, 20);
    t.root = t.insert(t.root, 34);
    t.root = t.insert(t.root, 5);
    t.root = t.insert(t.root, 3);
    t.root = t.insert(t.root, 15);

    cout << "Inorder traversal after inserting 15: ";
    t.inorder(t.root);
    cout << endl;

    cout << "Longest path in the tree: " << t.longestPath(t.root) << endl;
    cout << "Minimum value in the tree: " << t.findMin(t.root) << endl;
    cout << "Maximum value in the tree: " << t.findMax(t.root) << endl;

    t.swapChildren(t.root);
    cout << "Inorder traversal after swapping children: ";
    t.inorder(t.root);
    cout << endl;

    TreeNode* result = t.search(t.root, 10);
    if (result != nullptr) {
        cout << "Value found in the tree." << endl;
    } else {
        cout << "Value not found in the tree." << endl;
    }

    return 0;
}

