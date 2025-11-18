//============================================================================
// Name        : Assignment_1.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Binary Tree Operations
//============================================================================
#include <iostream>
using namespace std;

class treenode;

class Stack {
private:
    treenode** stackArray;
    int top;
    int capacity;

public:
    Stack(int size = 20) {
        stackArray = new treenode*[size];
        top = -1;
        capacity = size;
    }

    ~Stack() {
        delete[] stackArray;
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == capacity - 1;
    }

    void push(treenode* value) {
        if (isFull()) {
            cout<<"Stack overflow";
        }
        stackArray[++top] = value;
    }

    treenode* pop() {
        if (isEmpty()) {
            cout<<"Stack underflow";
        }
        return stackArray[top--];
    }

    treenode* peek() const {
        if (isEmpty()) {
            cout<<"Stack is empty";
        }
        return stackArray[top];
    }
};

class treenode {
private:
    int data;
    treenode* lchild;
    treenode* rchild;
public:
    treenode(int val = 0) : data(val), lchild(nullptr), rchild(nullptr) {}
    friend class tree;
};

class tree {
private:
    treenode* root;

public:
    tree() : root(nullptr) {}

    void create() {
        root = maketree();
    }

    void display() {
        int choice;
        cout << "\nSelect Traversal Method: \n";
        cout << "1. Recursive Traversal\n";
        cout << "2. Non-Recursive Traversal\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Recursive Preorder: ";
            preorderRecursive(root);
            cout << endl;
            cout << "Recursive Inorder: ";
            inorderRecursive(root);
            cout << endl;
            cout << "Recursive Postorder: ";
            postorderRecursive(root);
            cout << endl;
        } else if (choice == 2) {
            cout << "Non-Recursive Preorder: ";
            preorderNonRecursive(root);
            cout << endl;
            cout << "Non-Recursive Inorder: ";
            inorderNonRecursive(root);
            cout << endl;
            cout << "Non-Recursive Postorder: ";
            postorderNonRecursive(root);
            cout << endl;
        } else {
            cout << "Invalid choice!\n";
        }

        cout << "Number of leaf nodes: " << count_leaf(root) << endl;
        cout << "Number of internal nodes: " << count_internal(root) << endl;
    }

    void swapChildren() {
        swap_children(root);
        cout << "Tree after swapping left and right children at every node: ";
        inorderRecursive(root);
        cout << endl;
    }

    void findHeight() {
        cout << "Height of tree: " << height(root) << endl;
    }

    tree& operator=(const tree& other) {
        if (this != &other) {
            erase(root);
            root = copy(other.root);
        }
        return *this;
    }

    void eraseTreeRecursive() {
        erase(root);
        cout << "Tree erased recursively.\n";
    }

    void eraseTreeNonRecursive() {
        eraseNonRecursive(root);
        cout << "Tree erased non-recursively.\n";
    }

    treenode* getRoot() const {
        return root;
    }

    void inorderRecursive(treenode* t) const {
        if (t == nullptr) return;
        inorderRecursive(t->lchild);
        cout << t->data << " ";
        inorderRecursive(t->rchild);
    }

private:
    treenode* maketree() {
        int val;
        cout << "Enter node value (0 to stop): ";
        cin >> val;
        if (val == 0) return nullptr;
        treenode* newNode = new treenode(val);
        cout << "Enter left child of " << val << ": ";
        newNode->lchild = maketree();
        cout << "Enter right child of " << val << ": ";
        newNode->rchild = maketree();
        return newNode;
    }

    void preorderRecursive(treenode* t) const {
        if (t == nullptr) return;
        cout << t->data << " ";
        preorderRecursive(t->lchild);
        preorderRecursive(t->rchild);
    }

    void postorderRecursive(treenode* t) const {
        if (t == nullptr) return;
        postorderRecursive(t->lchild);
        postorderRecursive(t->rchild);
        cout << t->data << " ";
    }

    void preorderNonRecursive(treenode* t) const {
        if (t == nullptr) return;
        Stack s(50);
        s.push(t);
        while (!s.isEmpty()) {
            t = s.pop();
            cout << t->data << " ";
            if (t->rchild != nullptr) {
                s.push(t->rchild);
            }
            if (t->lchild != nullptr) {
                s.push(t->lchild);
            }
        }
    }

    void inorderNonRecursive(treenode* t) const {
        Stack s(50);
        while (t != nullptr || !s.isEmpty()) {
            while (t != nullptr) {
                s.push(t);
                t = t->lchild;
            }
            t = s.pop();
            cout << t->data << " ";
            t = t->rchild;
        }
    }

    void postorderNonRecursive(treenode* t) const {
        Stack s(50);
        treenode* prev = nullptr;
        do {
            while (t != nullptr) {
                s.push(t);
                t = t->lchild;
            }
            while (t == nullptr && !s.isEmpty()) {
                t = s.pop();
                if (t->rchild == nullptr || t->rchild == prev) {
                    cout << t->data << " ";
                    prev = t;
                    t = nullptr;
                } else {
                    s.push(t);
                    t = t->rchild;
                }
            }
        } while (!s.isEmpty());
    }

    int count_leaf(treenode* t) const {
        if (t == nullptr) return 0;
        if (t->lchild == nullptr && t->rchild == nullptr) return 1;
        return count_leaf(t->lchild) + count_leaf(t->rchild);
    }

    int count_internal(treenode* t) const {
        if (t == nullptr) return 0;
        if (t->lchild == nullptr && t->rchild == nullptr) return 0;
        return 1 + count_internal(t->lchild) + count_internal(t->rchild);
    }

    void swap_children(treenode* t) {
        if (t != nullptr) {
            swap(t->lchild, t->rchild);
            swap_children(t->lchild);
            swap_children(t->rchild);
        }
    }

    int height(treenode* t) const {
        if (t == nullptr) return 0;
        int leftHeight = height(t->lchild);
        int rightHeight = height(t->rchild);
        return 1 + max(leftHeight, rightHeight);
    }

    treenode* copy(treenode* t) const {
        if (t == nullptr) return nullptr;
        treenode* newNode = new treenode(t->data);
        newNode->lchild = copy(t->lchild);
        newNode->rchild = copy(t->rchild);
        return newNode;
    }

    void erase(treenode* &t) {
        if (t != nullptr) {
            erase(t->lchild);
            erase(t->rchild);
            delete t;
            t = nullptr;
        }
    }

    void eraseNonRecursive(treenode* &t) {
        if (t == nullptr) return;
        Stack s(50);
        s.push(t);
        while (!s.isEmpty()) {
            treenode* current = s.pop();
            if (current->rchild != nullptr) s.push(current->rchild);
            if (current->lchild != nullptr) s.push(current->lchild);
            delete current;
        }
        t = nullptr;
    }
};

int main() {
    tree t;
    tree t2;
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Create tree\n";
        cout << "2. Display tree and traversals\n";
        cout << "3. Swap left and right children\n";
        cout << "4. Find height of tree\n";
        cout << "5. Copy tree to another\n";
        cout << "6. Erase tree recursively\n";
        cout << "7. Erase tree non-recursively\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                t.create();
                break;
            case 2:
                t.display();
                break;
            case 3:
                t.swapChildren();
                break;
            case 4:
                t.findHeight();
                break;
            case 5:
                t2 = t;
                cout << "Copied tree inorder: ";
                t2.inorderRecursive(t2.getRoot());
                cout << endl;
                break;
            case 6:
                t.eraseTreeRecursive();
                break;
            case 7:
                t.eraseTreeNonRecursive();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
