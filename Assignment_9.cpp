//============================================================================
// Name        : Assignment_9.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : AVL Tree
//============================================================================
#include <bits/stdc++.h>
using namespace std;

class Node {
    int key ;
    string value ;
    int height = 1 ;
    Node* left = nullptr ;
    Node* right = nullptr ;
    friend class AVLTree;
};

class AVLTree {

    Node* root = nullptr ;

    int getBalanceFactor(Node* node){
        if(node == nullptr){
            return 0;
        }
        return nodeHeight(node->left) - nodeHeight(node->right);
    }

    int nodeHeight(Node *node) {
        if(node == nullptr){
            return 0;
        }
        return node->height;
    }

    void updateHeight(Node* node){
        node->height = 1 + max(nodeHeight(node->left),nodeHeight(node->right));
    }

    Node* LLRotation(Node *node) {
        Node *newRoot = node->left;
        newRoot->right = node;
        node->left = nullptr;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    Node* RRRotation( Node *node ) {
        Node *newRoot = node->right;
        newRoot->left = node;
        node->right = nullptr;

        updateHeight( node );
        updateHeight( newRoot );

        return newRoot;
    }

    Node* RLRotation( Node* node ) {
        node -> right = LLRotation( node -> right ) ;
        return RRRotation( node ) ;
    }

    Node* LRRotation( Node* node ) {
        node -> left = RRRotation( node -> left ) ;
        return LLRotation( node ) ;
    }

    Node* balance( Node* node ) {
        if(getBalanceFactor(node) == 2 ) {
            if(getBalanceFactor(node->left) < 0 )
                node = LRRotation( node ) ;
            else
                node = LLRotation( node ) ;
        }
        else if(getBalanceFactor(node) == -2 )  {
            if(getBalanceFactor(node->right) > 0 )
                node =RLRotation( node ) ;
            else
                node = RRRotation( node ) ;
        }
        updateHeight( node ) ;
        return node ;
    }

    void iinorder( Node *root ) {
        if( root == nullptr )
            return;
        iinorder( root->left );
        cout<< root->key <<" ";
        iinorder( root->right );
    }

    Node* insertSubTree( Node* curr , int key , string value ) {

        if( curr == nullptr ) {
            Node* newNode = new Node() ;
            newNode -> key = key ;
            newNode -> value = value ;
            return newNode ;
        }

        if( curr -> key > key ) {
            curr -> left = insertSubTree( curr -> left , key , value ) ;
        }
        else if( curr -> key < key ) {
            curr -> right = insertSubTree( curr -> right , key , value ) ;
        }
        else {
            curr -> value = value ;
            return curr ;
        }
        return balance( curr ) ;
    }
public:

    void insert( int key, string value ) {
        root = insertSubTree( root, key, value);
    }

    void inorder() {
        cout<< "\nInorder: " <<endl;
        iinorder( root );
        cout<<endl;
    }

    Node* search( int key ) {
        Node *curr = root;
        while( curr != nullptr ) {
            if( key > curr->key )
                curr = curr->right;
            else if( key < curr->key )
                curr = curr->left;
            else
                return curr;
        }
        return nullptr;
    }
};

int main() {
    AVLTree tree;

    tree.insert(100, "1");
    tree.insert(50, "2");
    tree.insert(150, "3");
    tree.insert(25, "4");
    tree.insert(75, "5");
    tree.insert(125, "6");

    tree.inorder();

    tree.insert(175, "7");
    tree.insert(65, "8");
    tree.insert(85, "9");

    tree.inorder();

    return 0;
}
