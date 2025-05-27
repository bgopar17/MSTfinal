#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <memory>
#include <limits>
#include "test.cpp"

using namespace std;

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