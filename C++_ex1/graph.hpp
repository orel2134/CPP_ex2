//orel2744@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>
#include <climits>

namespace graph {

class Graph {
private:
    struct Edge {
        int dest;           // destination vertex
        int weight;         // edge weight
        Edge* next;         // pointer to next edge in list
        
        Edge(int d, int w) : dest(d), weight(w), next(nullptr) {}
    };
    
    Edge** adjList;         // array of linked lists
    size_t numVertices;     // number of vertices in graph

    // Helper function to find an edge
    Edge* findEdge(int src, int dest) const;
    // Helper function to clear all edges
    void clearEdges();

public:
    // Constructor: Initializes an empty adjacency list
    Graph(size_t vertices);
    
    // Destructor: Frees allocated memory
    ~Graph();
    
    // Copy constructor to prevent shallow copying
    Graph(const Graph& other);
    
    // Assignment operator
    Graph& operator=(const Graph& other);

    // Adds an edge between two vertices with a given weight (default = 1)
    void addEdge(int src, int dest, int weight = 1);

    // Removes an edge between two vertices
    void removeEdge(int src, int dest);

    // Prints the adjacency list
    void printGraph() const;

    // Print graph from root in hierarchical format
    void printGraph(int root, int level = 0, bool* visited = nullptr) const;

    // Returns the number of vertices in the graph
    size_t getNumVertices() const;

    // Returns whether an edge exists between two vertices
    bool isEdge(int u, int v) const;

    // Returns the weight of an edge
    int weight(int u, int v) const;
};

} // namespace graph

#endif // GRAPH_HPP