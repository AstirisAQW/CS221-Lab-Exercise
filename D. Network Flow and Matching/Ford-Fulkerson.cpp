/*
Ford-Fulkerson Algorithm (20 points)
Given a directed network with capacities on edges, a source vertex, and a sink vertex,
implement the Ford-Fulkerson algorithm to find the maximum flow from the source to
the sink. Briefly explain the concept of an augmenting path and how it is used to
increase flow iteratively.

Sample Output: 
Network: (source: A, sink: D)
A -> B (capacity: 3)
B -> D (capacity: 2)
A -> C (capacity: 4)
C -> D (capacity: 7)

Maximum flow: 5 (Augmenting paths: A-B-D, A-C-D)

Time Complexity:    Best Case: O(maximum_flow * Edge)
                    Average Case: O(Vertices * Edge * maximum_flow) 
                    Worst Case: O(maximum_flow * Edge)
*/

#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
using namespace std;

#define V 4

// Using breadthFirstSearch as a searching algorithm to find the augmenting path
bool breadthFirstSearch(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));
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

// Implementing the Ford-Fulkerson algorithm
int fordFulkerson(int graph[V][V], int s, int t) {
    int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates residual capacity of edge from i to j
    for (int u = 0; u < V; u++)
        for (int v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V];  // This array is filled by breadthFirstSearch and to store path
    int max_flow = 0;  // There is no flow initially

    // Augment the flow while there is a path from source to sink
    while (breadthFirstSearch(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along the path
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // update residual capacities of the edges and reverse edges along the path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow; // Corrected: Update reverse edge capacity
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    int graph[V][V] = { {0, 3, 4, 0},
                        {0, 0, 0, 2},
                        {0, 0, 0, 7},
                        {0, 0, 0, 0}
                      };

    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 3);
    return 0;
}
