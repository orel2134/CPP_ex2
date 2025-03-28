#include "algorithms.hpp"
#include "graph.hpp"
#include <iostream>

using namespace graph;

// ------------------------ Queue for BFS (No STL) ------------------------
class Queue {
private:
    int* arr;
    int front, rear, size, capacity;
public:
    Queue(int cap) : capacity(cap), front(0), rear(-1), size(0) {
        arr = new int[cap];
    }
    ~Queue() { delete[] arr; }
    bool isEmpty() { return size == 0; }
    void push(int val) {
        if (size < capacity) arr[++rear] = val, size++;
    }
    int pop() {
        if (isEmpty()) return -1;
        int val = arr[front++];
        size--;
        return val;
    }
};

// ------------------------ Disjoint Set (for Kruskal) ------------------------
class DisjointSet {
private:
    int* parent;
    int* rank;
    int size;
public:
    DisjointSet(int n) : size(n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) parent[i] = i, rank[i] = 0;
    }
    ~DisjointSet() { delete[] parent; delete[] rank; }
    int find(int u) {
        if (parent[u] != u) parent[u] = find(parent[u]); // Path compression
        return parent[u];
    }
    void unite(int u, int v) {
        int rootU = find(u), rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
            else if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
            else parent[rootV] = rootU, rank[rootU]++;
        }
    }
};

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
                tree.addEdge(u, v); // Edge in BFS tree
            }
        }
    }
    delete[] visited;
    return tree;
}

// ------------------------ DFS ------------------------
Graph Algorithms::dfs(const Graph& g, int src) {
    int n = g.getNumVertices();
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
Graph Algorithms::kruskal(const Graph& g) {
    int n = g.getNumVertices();
    Graph mst(n);
    DisjointSet ds(n);

    struct Edge {
        int u, v, weight;
    };

    Edge* edges = new Edge[n * n];
    int edgeCount = 0;

    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (g.isEdge(u, v)) {
                edges[edgeCount++] = {u, v, g.weight(u, v)};
            }
        }
    }

    // Sort edges by weight (bubble sort)
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    int edgesInMST = 0;
    for (int i = 0; i < edgeCount && edgesInMST < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        if (ds.find(u) != ds.find(v)) {
            ds.unite(u, v);
            mst.addEdge(u, v, edges[i].weight);
            edgesInMST++;
        }
    }

    delete[] edges;
    return mst;
}
