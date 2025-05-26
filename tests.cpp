#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory>
#include <limits>

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

class Graph {
private: 
    struct Vertex{
        int id;
        vector<Edge> edges; // List of edges connected to this vertex
        Vertex (it i) : id(i){}
    };

    vector<shared_ptr<Vertex>> vertices; // List of vertices in the graph

public:
    Graph(int size) {
        for (int i = 0; i < size; ++i) 
            vertices.push_back(make_shared<Vertex>(i));
    }

    void addEdge(int u, int v, double w) {
        vertices[u]->edges.emplace_back(u, v, w);
        vertices[v]->edges.emplace_back(v, u, w); 
    }
}