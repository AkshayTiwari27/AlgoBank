#include "Graph.hpp"
#include <iostream>

using namespace std;

void Graph::addEdge(int u, int v, double amount) {
    adjList[u].push_back({v, amount});
}

void Graph::printGraph() {
    cout << "--- Transaction Graph ---" << endl;
    for (const auto& pair : adjList) {
        cout << "User " << pair.first << " has transacted with: " << endl;
        for (const auto& trans : pair.second) {
            cout << "  -> User " << trans.first << " ($" << trans.second << ")" << endl;
        }
    }
}