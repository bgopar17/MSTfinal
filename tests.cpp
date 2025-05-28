#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory>
#include <limits>
#include "catch.hpp"



using namespace std;
// Function to find the maximum sum of non-adjacent elements in a vector

struct Edge {
    int source, destination;// Source and destination vertices of the edge
    double weight; // Weight of the edge

    Edge(int s,int d, double w): source(s), destination(d), weight(w) {}
    // Overloading the less than operator for priority queue comparison

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class Graph { // Class representing a graph using an adjacency list
private: 
    struct Vertex{
        int id;
        vector<Edge> edges; // List of edges connected to this vertex
        Vertex (int i) : id(i){}
    };

    vector<shared_ptr<Vertex>> vertices; // List of vertices in the graph

public:
    Graph(int size) {
        for (int i = 0; i < size; ++i) 
            vertices.push_back(make_shared<Vertex>(i));
    }

    void addEdge(int u, int v, double w) { // Function to add an edge between vertices u and v with weight w
        vertices[u]->edges.emplace_back(u, v, w);
        vertices[v]->edges.emplace_back(v, u, w); 
    }


vector<Edge> findMST(){ // Function to find the Minimum Spanning Tree (MST) using Prim's algorithm
    int n = vertices.size();
    vector<bool> inMST(n, false); // Track vertices included in the MST
    vector<double> key(n, numeric_limits<double>::max()); // Key values to pick minimum weight edge
    vector<int> parent(n, -1); // Parent array to store the MST structure
    key[0] = 0;

    using pii = pair<double, int>; // Pair to store key and vertex index
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0,0});

    while(!pq.empty()) { // While there are vertices to process
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        for (auto& e : vertices[u]->edges) {// Iterate through all edges connected to vertex u
            int v = e.destination;
            double w = e.weight;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    vector<Edge> mst; // Store the edges of the MST
    for (int v = 1; v < n; ++v) { // Start from vertex 1 as vertex 0 is the root
        if (parent[v] != -1) 
            mst.emplace_back(parent[v], v, key[v]);
    }
    return mst;
}
};

int main() {
    Graph g(9);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 5, 4);
    g.addEdge(2, 8, 2);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    auto mst = g.findMST();
    double totalWeight = 0;

    for (const auto& e : mst) {
        cout << e.source << " - " << e.destination << " (Weight: " << e.weight << ")\n";
        totalWeight += e.weight;
    }

    cout << "Total weight of MST: " << totalWeight << endl;
    return 0;
}