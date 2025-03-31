#include "algorithms.hpp"
#include "graph.hpp"
#include "helpers.hpp"
#include <iostream>
#include <stdexcept>

using namespace graph;


// ------------------------ BFS ------------------------
Graph Algorithms::bfs(const Graph& g, int src) {
    int n = g.getNumVertices();
    Graph tree(n);
    bool* visited = new bool[n]();
    Queue q(n);

    visited[src] = true;
    q.push(src);

    while (!q.isEmpty()) {
        int u = q.pop();
        for (int v = 0; v < n; v++) {
            if (g.isEdge(u, v) && !visited[v]) {
                visited[v] = true;
                q.push(v);
                tree.addEdge(u, v);
            }
        }
    }
    delete[] visited;
    return tree;
}

// ------------------------ DFS ------------------------
Graph Algorithms::dfs(const Graph& g, int src) {
    int n = g.getNumVertices();
    
    //Handling the case where the starting code is invalid or the graph is empty
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
            for (int v = 0; v < n; v++) {
                if (g.isEdge(u, v) && !visited[v]) {
                    stack[++top] = v;
                    tree.addEdge(u, v);
                }
            }
        }
    }

    delete[] visited;
    delete[] stack;
    return tree;
}


// ------------------------ Dijkstra ------------------------
Graph Algorithms::dijkstra(const Graph& g, int src) {
    int n = g.getNumVertices();

    // בדיקה לצלעות עם משקל שלילי
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

    for (int i = 0; i < n; i++) dist[i] = INT_MAX, parent[i] = -1;
    dist[src] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;

        if (dist[u] == INT_MAX) break;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (g.isEdge(u, v) && dist[u] + g.weight(u, v) < dist[v]) {
                dist[v] = dist[u] + g.weight(u, v);
                parent[v] = u;
            }
        }
    }

    for (int v = 0; v < n; v++)
        if (parent[v] != -1) tree.addEdge(parent[v], v, g.weight(parent[v], v));

    delete[] dist;
    delete[] parent;
    delete[] visited;
    return tree;
}

// ------------------------ Prim ------------------------
Graph Algorithms::prim(const Graph& g) {
    int n = g.getNumVertices();
    Graph mst(n);
    bool* inMST = new bool[n]();
    int* parent = new int[n];
    int* key = new int[n];
    for (int i = 0; i < n; i++) key[i] = INT_MAX, parent[i] = -1;
    key[0] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;

        if (u == -1) throw std::runtime_error("Graph is not connected");
        inMST[u] = true;

        for (int v = 0; v < n; v++) {
            if (g.isEdge(u, v) && !inMST[v] && g.weight(u, v) < key[v]) {
                key[v] = g.weight(u, v);
                parent[v] = u;
            }
        }
    }

    for (int v = 1; v < n; v++) mst.addEdge(parent[v], v, g.weight(parent[v], v));
    delete[] inMST;
    delete[] parent;
    delete[] key;
    return mst;
}

// ------------------------ Kruskal ------------------------
/**
 * Constructs a Minimum Spanning Tree (MST) using Kruskal's algorithm.
 * Supports negative edge weights. Assumes the input graph is undirected.
 *
 * @param g - The input graph
 * @return A graph representing the MST
 */
// ------------------------ Kruskal ------------------------
// ------------------------ Kruskal ------------------------
Graph Algorithms::kruskal(const Graph& g) {
    int n = g.getNumVertices();
    Graph mst(n);
    DisjointSet ds(n);

    // Edge struct for internal use
    struct Edge {
        int u, v, weight;
    };

    // Allocate array to store all possible edges (upper triangle of matrix)
    Edge* edges = new Edge[n * n];
    int edgeCount = 0;

    // Step 1: Collect edges (including negative weights)
    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g.isEdge(u, v)) {
                edges[edgeCount++] = {u, v, g.weight(u, v)};
            }
        }
    }
    // Step 2: Bubble sort edges by weight (including negative)
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Step 3: Kruskal - add edges if no cycle is formed
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
