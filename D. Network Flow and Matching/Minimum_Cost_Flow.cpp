/*
Minimum Cost Flow Algorithm (20 points)
An extension of network flow considers costs associated with edges. Design an
algorithm (e.g., Edmonds-Karp) to find the minimum cost flow from a source to a sink
in a network. Briefly explain how the algorithm modifies the Ford-Fulkerson approach
to consider costs.

Sample Output:  Network: (source: A, sink: D)
                A -> B (cost: 1, capacity: 3)
                B -> D (cost: 2, capacity: 2)
                A -> C (cost: 3, capacity: 4)
                C -> D (cost: 1, capacity: 7)   
                Minimum cost flow: 6 (Path: A-B-D with cost 3)

Time Complexity:    Best Case:
                    Average Case:
                    Worst Case:
*/

#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

#define V 4

// Data structure to store graph edges
struct Edge {
    int u, v, capacity, cost;
};

// Using breadthFirstSearch as a searching algorithm to find the augmenting path
bool breadthFirstSearch(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    vector<bool> visited(V, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == t) {
                    // Found the augmenting path
                    return true;
                }
            }
        }
    }

    // No augmenting path found
    return false;
}

// Implementing the Minimum Cost Flow Algorithm based on Edmonds-Karp approach
int minCostFlow(vector<Edge>& edges, int s, int t) {
    vector<vector<int>> rGraph(V, vector<int>(V, 0));

    // Build residual graph
    for (auto& edge : edges) {
        rGraph[edge.u][edge.v] = edge.capacity;
    }

    int maxFlow = 0;
    int minCost = 0;

    // Augment the flow while there is a path from source to sink
    while (true) {
        vector<int> parent(V, -1);
        if (!breadthFirstSearch(rGraph, s, t, parent)) {
            // No augmenting path found, terminate the loop
            break;
        }

        int pathFlow = INT_MAX;
        // Find minimum residual capacity of the edges along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        // Update residual capacities of the edges along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        // Add path flow to overall flow
        maxFlow += pathFlow;

        // Update minimum cost
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            for (auto& edge : edges) {
                if (edge.u == u && edge.v == v) {
                    minCost += pathFlow * edge.cost;
                    break;
                }
            }
        }
    }

    return minCost;
}

int main() {
    vector<Edge> edges = {
        {0, 1, 3, 1},  // A -> B
        {1, 3, 2, 2},  // B -> D
        {0, 2, 4, 3},  // A -> C
        {2, 3, 7, 1}   // C -> D
    };

    int source = 0, sink = 3;

    int minCost = minCostFlow(edges, source, sink);

    cout << "Minimum cost flow: " << minCost << endl;

    return 0;
}
