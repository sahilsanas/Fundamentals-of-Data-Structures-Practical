//============================================================================
// Name        : Assignment_8.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Optimal Binary Search Tree
//============================================================================
#include <bits/stdc++.h>
using namespace std;
#define MAX 20

class Node {
    int key;
    Node *left, *right;
    friend class OBST;

  public:    
    Node(int k = 0) {
        key = k;
        left = NULL;
        right = NULL;
    }
};

class OBST {
    double C[MAX][MAX];
    double W[MAX][MAX];
    int R[MAX][MAX];
    double q[MAX];
    double p[MAX];

    int n;
    int keys[MAX];
    Node *root;

  public:
    OBST() {
        root = NULL;
    }

    void Calculate_W_C_R() {
        double x;
        double min;
        int i, j, k, h, m;

        for (i = 0; i <= n; i++) {
            W[i][i] = q[i];
            for (j = i + 1; j <= n; j++)
                W[i][j] = W[i][j - 1] + p[j] + q[j];
        }

        for (i = 0; i <= n; i++)
            C[i][i] = W[i][i];
        for (i = 0; i <= n - 1; i++) {
            j = i + 1;
            C[i][j] = C[i][i] + C[j][j] + W[i][j];
            R[i][j] = j;
        }
        for (h = 2; h <= n; h++) {
            for (i = 0; i <= n - h; i++) {
                j = i + h;
                m = R[i][j - 1];
                min = C[i][m - 1] + C[m][j];
                for (k = m + 1; k <= R[i + 1][j]; k++) {
                    x = C[i][k - 1] + C[k][j];
                    if (x < min) {
                        m = k;
                        min = x;
                    }
                }
                C[i][j] = W[i][j] + min;
                R[i][j] = m;
            }
        }

        cout << "\nThe weight matrix W:\n";
        for (i = 0; i <= n; i++) {
            for (j = i; j <= n; j++)
                cout << W[i][j] << " ";
            cout << "\n";
        }

        cout << "\nThe cost matrix C:\n";
        for (i = 0; i <= n; i++) {
            for (j = i; j <= n; j++)
                cout << C[i][j] << " ";
            cout << "\n";
        }

        cout << "\nThe root matrix R:\n";
        for (i = 0; i <= n; i++) {
            for (j = i + 1; j <= n; j++)
                cout << R[i][j] << " ";
            cout << "\n";
        }
    }

    Node *Construct_OBST(int i, int j) {
        Node *p;

        if (i == j)
            p = NULL;
        else {
            p = new Node();
            p->key = keys[R[i][j]];
            p->left = Construct_OBST(i, R[i][j] - 1);
            p->right = Construct_OBST(R[i][j], j);
        }
        return p;
    }

    // Improved display function with better tree structure representation
    void display(Node *ROOT, int level = 0) {
        if (ROOT != NULL) {
            // Display the right subtree first (higher levels)
            display(ROOT->right, level + 1);

            // Print the current node with appropriate indentation for tree structure
            for (int i = 0; i < level; i++)
                cout << "   ";  // Indentation for each level
            cout << ROOT->key << endl;

            // Display the left subtree (lower levels)
            display(ROOT->left, level + 1);
        }
    }

    void obst() {
        Calculate_W_C_R();

        cout << "C[0] = " << C[0][n] << " W[0] = " << W[0][n] << endl;
        cout << "The Least cost is: \n" << C[0][n] << endl;
        root = Construct_OBST(0, n);
    }

    void inp() {
        cout << "Enter number of keys:";
        cin >> n;
        if (n <= 0) {
            cout << "Number of keys must be greater than 0." << endl;
            return;
        }

        cout << "Enter keys" << endl;
        for (int i = 1; i <= n; i++) {
            cin >> keys[i];
            cout << "Probability = ";
            cin >> p[i];
        }

        for (int i = 0; i <= n; i++) {
            cout << "q" << i << "= ";
            cin >> q[i];
        }
    }

    Node *get() {
        return root;
    }
};

int main() {
    int k;

    OBST tree;

    while (true) {
        cout << "1. Construct tree\n2. Display tree\n3. Exit\n";
        cin >> k;
        switch (k) {
        case 1:
            tree.inp();
            tree.obst();
            break;
        case 2:
            cout << "Displaying the Optimal Binary Search Tree:\n";
            tree.display(tree.get(), 0);
            break;
        case 3:
            return 0;
        }
    }
}
