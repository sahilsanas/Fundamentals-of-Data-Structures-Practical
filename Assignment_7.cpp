//============================================================================
// Name        : Assignment_7.cpp
// Author      : Sahil Sanas
// Version     :
// Copyright   : Your copyright notice
// Description : Prims Algorithm
//============================================================================
#include<bits/stdc++.h>
using namespace std;

class Graph {

    int **adjMatrix;
    int V;
    int E;
    map<string, int> cityMap;
    map<int, string> invCityMap;

    void add(string u, string v, int dist) {
        adjMatrix[cityMap[u]][cityMap[v]] = dist;
        adjMatrix[cityMap[v]][cityMap[u]] = dist;
    }

    int minKey(int key[], bool mst[]) {
        int min = INT_MAX, minIndex, i;

        for (i = 0; i < V; i++)
            if (mst[i] == 0 && key[i] < min) {
                min = key[i];
                minIndex = i;
            }
        return minIndex;
    }

    public:

    Graph() {
        cout << "Enter number of Vertices: ";
        cin >> V;
        cout << "Enter number of edges: ";
        cin >> E;

        adjMatrix = new int*[V];
        for (int i = 0; i < V; i++) {
            adjMatrix[i] = new int[V];
            for (int j = 0; j < V; j++)
                adjMatrix[i][j] = 0;
        }

        cout << "Add cities in order: " << endl;
        for (int i = 0; i < V; i++) {
            string city;
            cin >> city;
            cityMap.insert(pair<string, int>(city, i));
            invCityMap.insert(pair<int, string>(i, city));
        }

        cout << "Add the " << E << " edges" << endl;

        for (int i = 0; i < E; i++) {
            string u, v;
            int d;
            cout << "City 1: ";
            cin >> u;
            cout << "City 2: ";
            cin >> v;
            cout << "Distance: ";
            cin >> d;
            add(u, v, d);
        }
    }

    void prim(Graph g) {
        int n = g.V;
        int parent[n];
        int key[n];
        bool mst[n];
        for (int i = 0; i < n; i++) {
            key[i] = INT_MAX;
            mst[i] = 0;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < n - 1; count++) {
            int u = minKey(key, mst);
            mst[u] = 1;

            for (int v = 0; v < n; v++) {
                if (g.adjMatrix[u][v] && mst[v] == 0 && g.adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = g.adjMatrix[u][v];
                }
            }
        }

        cout << "MST of given graph is: \n" << endl;
        cout << "\nEdge \t Weight\n";
        for (int i = 1; i < n; i++) {
            cout << invCityMap[parent[i]] << " <-> " << invCityMap[i] << " \t " << g.adjMatrix[i][parent[i]] << endl;
            
        }
    }
};

int main() {

    Graph g;
    g.prim(g);

    return 0;
}
