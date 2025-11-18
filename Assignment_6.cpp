//============================================================================
// Name        : Assignment_6.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : DFS traversal (to check if graph is connected)
//============================================================================
#include <iostream>
using namespace std;

class Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
    friend class Graph;
};

class Graph {
    int v;
    Node** list;

    void dfs(int vertex, bool* visited) {
        visited[vertex] = true;
        Node* current = list[vertex];
        while (current != nullptr) {
            if (!visited[current->data]) {
                dfs(current->data, visited);
            }
            current = current->next;
        }
    }

public:
    Graph(int v) {
        this->v = v;
        list = new Node*[v];
        for (int i = 0; i < v; ++i) {
            list[i] = nullptr;
        }
    }

    void addEdge(int u, int v) {
        Node* newNode = new Node(v);
        newNode->next = list[u];
        list[u] = newNode;
    }

    void calculateDegrees() {
        for (int i = 0; i < v; ++i) {
            int inDeg = 0, outDeg = 0;
            Node* current = list[i];
            while (current != nullptr) {
                outDeg++;
                current = current->next;
            }
            for (int j = 0; j < v; ++j) {
                current = list[j];
                while (current != nullptr) {
                    if (current->data == i) {
                        inDeg++;
                        break;
                    }
                    current = current->next;
                }
            }
            cout << "City " << i << ": In-degree = " << inDeg << ", Out-degree = " << outDeg << endl;
        }
    }

    bool isConnected() {
        bool* visited = new bool[v]{ false };
        dfs(0, visited);
        for (int i = 0; i < v; ++i) {
            if (!visited[i]) {
                delete[] visited;
                return false;
            }
        }
        delete[] visited;
        return true;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    g.calculateDegrees();

    if (g.isConnected()) {
        cout << "The graph is connected." << endl;
    } else {
        cout << "The graph is not connected." << endl;
    }

    return 0;
}
