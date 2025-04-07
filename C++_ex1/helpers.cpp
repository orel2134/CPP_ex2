//orel2744@gmail.com

#include "helpers.hpp"

// Queue
Queue::Queue(int cap) : capacity(cap), front(0), rear(-1), size(0) {
    arr = new int[cap];
}
Queue::~Queue() { delete[] arr; }
bool Queue::isEmpty() { return size == 0; }
void Queue::push(int val) {
    if (size < capacity) arr[++rear] = val, size++;
}
int Queue::pop() {
    if (isEmpty()) return -1;
    int val = arr[front++];
    size--;
    return val;
}

// Disjoint Set
DisjointSet::DisjointSet(int n) : size(n) {
    parent = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; i++) parent[i] = i, rank[i] = 0;
}
DisjointSet::~DisjointSet() {
    delete[] parent;
    delete[] rank;
}
int DisjointSet::find(int u) {
    if (parent[u] != u) parent[u] = find(parent[u]);
    return parent[u];
}
void DisjointSet::unite(int u, int v) {
    int rootU = find(u), rootV = find(v);
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) parent[rootV] = rootU;
        else if (rank[rootU] < rank[rootV]) parent[rootU] = rootV;
        else parent[rootV] = rootU, rank[rootU]++;
    }
}
