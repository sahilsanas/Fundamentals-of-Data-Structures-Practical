//============================================================================
// Name        : Assignment_3.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Threaded Binary Tree 
//============================================================================
#include <iostream>
using namespace std;

class Node {
public:
    int info;
    Node* left;
    Node* right;
    bool lthread;
    bool rthread;

    Node(int value) : info(value), left(nullptr), right(nullptr), lthread(true), rthread(true) {}
};

class ThreadedBinaryTree {
private:
    Node* root;

    Node* caseA(Node* par, Node* ptr) {
        if (par == nullptr) {
            root = nullptr;
        } else if (par->left == ptr) {
            par->left = ptr->left;
            par->lthread = true;
        } else {
            par->right = ptr->right;
            par->rthread = true;
        }
        delete ptr;
        return root;
    }

    Node* caseB(Node* par, Node* ptr) {
        Node* child = nullptr;
        if (ptr->lthread == false)
            child = ptr->left;
        else
            child = ptr->right;

        if (par == nullptr) {
            root = child;
        } else if (par->left == ptr) {
            par->left = child;
            par->lthread = false;
        } else {
            par->right = child;
            par->rthread = false;
        }
        delete ptr;
        return root;
    }

    Node* caseC(Node* par, Node* ptr) {
        Node* successorParent = ptr;
        Node* successor = ptr->right;

        while (successor->lthread == false) {
            successorParent = successor;
            successor = successor->left;
        }

        ptr->info = successor->info;

        if (successor->lthread == true && successor->rthread == true) {
            caseA(successorParent, successor);
        } else {
            caseB(successorParent, successor);
        }

        return root;
    }

public:

    ThreadedBinaryTree() : root(nullptr) {}

    void insert(int ikey) {
        Node* ptr = root;
        Node* par = nullptr;

        while (ptr != nullptr) {

            if (ikey == ptr->info) {
                cout << "Duplicate Key!" << endl;
                return;
            }
            par = ptr;

            if (ikey < ptr->info) {
                if (ptr->lthread == false)
                    ptr = ptr->left;
                else
                    break;
            }

            else {
                if (ptr->rthread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        Node* tmp = new Node(ikey);

        if (par == nullptr) {
            root = tmp;
            tmp->left = nullptr;
            tmp->right = nullptr;
        }

        else if (ikey < par->info) {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false;
            par->left = tmp;
        }

        else {
            tmp->left = par;
            tmp->right = par->right;
            par->rthread = false;
            par->right = tmp;
        }
    }

    Node* delThreadedBST(int dkey) {
        Node* par = nullptr;
        Node* ptr = root;
        bool found = false;

        while (ptr != nullptr) {
            if (dkey == ptr->info) {
                found = true;
                break;
            }
            par = ptr;
            if (dkey < ptr->info) {
                if (ptr->lthread == false)
                    ptr = ptr->left;
                else
                    break;
            } else {
                if (ptr->rthread == false)
                    ptr = ptr->right;
                else
                    break;
            }
        }

        if (!found) {
            cout << "Node " << dkey << " not present in tree\n";
            return root;
        }

        if (ptr->lthread == false && ptr->rthread == false) {
            root = caseC(par, ptr);
        } else if (ptr->lthread == false || ptr->rthread == false) {
            root = caseB(par, ptr);
        } else {
            root = caseA(par, ptr);
        }

        return root;
    }

    void inorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        Node* ptr = root;
        while (ptr->lthread == false)
            ptr = ptr->left;

        while (ptr != nullptr) {
            cout << ptr->info << " ";
            ptr = inorderSuccessor(ptr);
        }
        cout << endl;
    }

    void preorder() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }

        Node* ptr = root;
        while (ptr != nullptr) {
            cout << ptr->info << " ";

            if (ptr->lthread == false)
                ptr = ptr->left;
            else if (ptr->rthread == false)
                ptr = ptr->right;
            else {
                while (ptr != nullptr && ptr->rthread == true)
                    ptr = ptr->right;
                if (ptr != nullptr)
                    ptr = ptr->right;
            }
        }
        cout << endl;
    }

    Node* inorderSuccessor(Node* ptr) {
        if (ptr->rthread == true)
            return ptr->right;

        ptr = ptr->right;
        while (ptr->lthread == false)
            ptr = ptr->left;

        return ptr;
    }
};

int main() {
    ThreadedBinaryTree tbt;

    tbt.insert(25);
    tbt.insert(15);
    tbt.insert(35);
    tbt.insert(10);
    tbt.insert(20);
    tbt.insert(30);
    tbt.insert(40);

    cout << "Inorder traversal before deletion: ";
    tbt.inorder();

    tbt.delThreadedBST(15);

    cout << "Inorder traversal after deletion: ";
    tbt.inorder();

    cout << "Preorder traversal: ";
    tbt.preorder();

    return 0;
}

