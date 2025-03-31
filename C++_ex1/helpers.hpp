#ifndef HELPERS_HPP
#define HELPERS_HPP

class Queue {
private:
    int* arr;
    int front, rear, size, capacity;
public:
    Queue(int cap);
    ~Queue();
    bool isEmpty();
    void push(int val);
    int pop();
};

class DisjointSet {
private:
    int* parent;
    int* rank;
    int size;
public:
    DisjointSet(int n);
    ~DisjointSet();
    int find(int u);
    void unite(int u, int v);
};

#endif // HELPERS_HPP
