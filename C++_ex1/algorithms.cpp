#include "algorithms.hpp"
#include "graph.hpp"
#include "helpers.hpp"
#include <iostream>
#include <stdexcept>

using namespace graph;

// BFS implementation using adjacency list
Graph Algorithms::bfs(const Graph& g, int src) {
    int n = g.getNumVertices();
    Graph tree(n);
    bool* visited = new bool[n]();
    Queue q(n);

    visited[src] = true;
    q.push(src);

    while (!q.isEmpty()) {
        int u = q.pop();
        // Iterate through all neighbors of u
        for (int v = 0; v < n; v++) {
            if (g.isEdge(u, v) && !visited[v]) {
                visited[v] = true;
                q.push(v);
                tree.addEdge(u, v, g.weight(u, v));
            }
        }
    }
    delete[] visited;
    return tree;
}

// DFS implementation using adjacency list
Graph Algorithms::dfs(const Graph& g, int src) {
    int n = g.getNumVertices();
    
    if (src < 0 || src >= n) {
        throw std::invalid_argument("Invalid vertex index");
    }

    Graph tree(n);
    bool* visited = new bool[n]();
    int* stack = new int[n];
    int top = -1;

    stack[++top] = src;

    while (top >= 0) {
        int u = stack[top--];
        if (!visited[u]) {
            visited[u] = true;
            // Iterate through all neighbors of u in reverse order
            for (int v = n-1; v >= 0; v--) {
                if (g.isEdge(u, v) && !visited[v]) {
                    stack[++top] = v;
                    tree.addEdge(u, v, g.weight(u, v));
                }
            }
        }
    }

    delete[] visited;
    delete[] stack;
    return tree;
}

///////////////////////////////////

// Dijkstra's algorithm implementation using adjacency list
Graph Algorithms::dijkstra(const Graph& g, int src) {
    int n = g.getNumVertices();

    // Check for negative weights
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (g.isEdge(u, v) && g.weight(u, v) < 0) {
                throw std::invalid_argument("Dijkstra cannot handle negative edge weights");
            }
        }
    }

    Graph tree(n);
    int* dist = new int[n];
    int* parent = new int[n];
    bool* visited = new bool[n]();

    // Initialize distances
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }
    dist[src] = 0;

    // Main loop
    for (int count = 0; count < n; count++) {
        // Find minimum distance vertex
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }

        if (u == -1 || dist[u] == INT_MAX) break;
        visited[u] = true;

        // Update distances of adjacent vertices
        for (int v = 0; v < n; v++) {
            if (g.isEdge(u, v) && !visited[v]) {
                int newDist = dist[u] + g.weight(u, v);
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    parent[v] = u;
                }
            }
        }
    }

  // Construct the result tree without cycles using Union-Find
DisjointSet ds(n);

for (int v = 0; v < n; v++) {
    if (parent[v] != -1) {
        int u = parent[v];
        if (ds.find(u) != ds.find(v)) {
            tree.addEdge(u, v, g.weight(u, v));
            ds.unite(u, v);
        }
    }
}

delete[] dist;
delete[] parent;
delete[] visited;
return tree;
}
////////////////////////////////////////////

Graph Algorithms::prim(const Graph& g) {
    int n = g.getNumVertices();
    Graph mst(n);
    bool* inMST = new bool[n]();
    int* key = new int[n];
    int* parent = new int[n];

    // Initialize keys and parents
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }
    key[0] = 0; // Start from vertex 0

    for (int count = 0; count < n; count++) {
        // Find the vertex u not in MST with the minimum key
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        // If no valid vertex found (disconnected graph)
        if (u == -1 || key[u] == INT_MAX) {
            delete[] inMST;
            delete[] key;
            delete[] parent;
            throw std::runtime_error("Graph is not connected");
        }

        inMST[u] = true;

        // Update keys and parents of adjacent vertices
        for (int v = 0; v < n; v++) {
            if (g.isEdge(u, v) && !inMST[v] && g.weight(u, v) < key[v]) {
                key[v] = g.weight(u, v);
                parent[v] = u;
            }
        }
    }

    // Build the MST
for (int v = 1; v < n; v++) {
    if (parent[v] != -1) {
        mst.addEdge(parent[v], v, g.weight(parent[v], v));
    }
}

// Validation: Check if the MST is connected
int edgeCount = 0;
for (int u = 0; u < n; u++) {
    for (int v = u + 1; v < n; v++) {
        if (mst.isEdge(u, v)) {
            edgeCount++;
        }
    }
}
if (edgeCount < n - 1) {
    delete[] inMST;
    delete[] key;
    delete[] parent;
    throw std::runtime_error("Graph is not connected");
}

delete[] inMST;
delete[] key;
delete[] parent;
return mst;
}



// Kruskal's algorithm implementation using adjacency list
Graph Algorithms::kruskal(const Graph& g) {
    int n = g.getNumVertices();
    Graph mst(n);
    DisjointSet ds(n);

    // Edge structure for sorting
    struct Edge {
        int u, v, weight;
    };

    // Collect all edges
    Edge* edges = new Edge[n * n];  // Maximum possible edges
    int edgeCount = 0;

    // Collect edges from adjacency list
    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g.isEdge(u, v)) {
                edges[edgeCount++] = {u, v, g.weight(u, v)};
            }
        }
    }

    // Sort edges by weight (using bubble sort)
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Process edges in sorted order
    for (int i = 0; i < edgeCount; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (ds.find(u) != ds.find(v)) {
            ds.unite(u, v);
            mst.addEdge(u, v, edges[i].weight);
        }
    }

    delete[] edges;
    return mst;
}