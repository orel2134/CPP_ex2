#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>
#include <climits>

namespace graph {

class Graph {
private:
    int** adjacencyMatrix;  // Adjacency matrix representation
    size_t numVertices;     // Number of vertices

public:
    // Constructor: Initializes an empty adjacency matrix
    Graph(size_t vertices);

    // Destructor: Frees allocated memory
    ~Graph();

    // Adds an edge between two vertices with a given weight (default = 1)
    void addEdge(int src, int dest, int weight = 1);

    // Removes an edge between two vertices
    void removeEdge(int src, int dest);

    // Prints the adjacency matrix
    void printGraph() const;

    // Returns the number of vertices in the graph
    size_t getNumVertices() const;

    // Returns whether an edge exists between two vertices
    bool isEdge(int u, int v) const;

    // Returns the weight of an edge
    int weight(int u, int v) const;

    // Returns the adjacency matrix
    int** getGraph() const;
};

} // namespace graph

#endif // GRAPH_HPP
