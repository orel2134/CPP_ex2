#include "graph.hpp"
#include <iostream>

namespace graph {

// Constructor: Initializes an adjacency matrix with `vertices` nodes
Graph::Graph(size_t vertices) : numVertices(vertices) {
    adjacencyMatrix = new int*[numVertices];
    for (size_t i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = new int[numVertices];
        for (size_t j = 0; j < numVertices; j++) {
            adjacencyMatrix[i][j] = (i == j) ? 0 : INT_MAX; // No edge by default
        }
    }
}

// Destructor: Releases allocated memory
Graph::~Graph() {
    if (adjacencyMatrix) {
        for (size_t i = 0; i < numVertices; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
}

// Adds an edge between `src` and `dest` with a given weight
void Graph::addEdge(int src, int dest, int weight) {
    if (src >= numVertices || dest >= numVertices) {
        throw std::out_of_range("Invalid vertex index");
    }
    if (weight <= 0) {
        throw std::invalid_argument("Edge weight must be positive");
    }
    adjacencyMatrix[src][dest] = weight;
    adjacencyMatrix[dest][src] = weight; // Undirected graph
}

// Removes an edge between `src` and `dest`
void Graph::removeEdge(int src, int dest) {
    if (src >= numVertices || dest >= numVertices) {
        throw std::out_of_range("Invalid vertex index");
    }
    if (adjacencyMatrix[src][dest] == INT_MAX) {
        throw std::runtime_error("Edge does not exist");
    }
    adjacencyMatrix[src][dest] = INT_MAX;
    adjacencyMatrix[dest][src] = INT_MAX;
}

// Prints the tree in a hierarchical format from a root
void Graph::printGraph(int root, int level, bool* visited) const {
    bool isTopLevel = false;
    if (!visited) {
        visited = new bool[numVertices]();
        isTopLevel = true;
    }

    visited[root] = true;

    for (int i = 0; i < level; ++i) std::cout << "  ";
    std::cout << root << std::endl;

    for (int v = 0; v < numVertices; v++) {
        if (isEdge(root, v) && !visited[v]) {
            printGraph(v, level + 1, visited);
        }
    }

    if (isTopLevel) {
        delete[] visited;
    }
}

// Returns the number of vertices in the graph
size_t Graph::getNumVertices() const {
    return numVertices;
}

// Checks if there is an edge between two nodes
bool Graph::isEdge(int u, int v) const {
    if (u >= numVertices || v >= numVertices) {
        throw std::out_of_range("Invalid vertex index");
    }
    return adjacencyMatrix[u][v] != INT_MAX;
}

// Returns the weight of an edge between two nodes
int Graph::weight(int u, int v) const {
    if (u >= numVertices || v >= numVertices) {
        throw std::out_of_range("Invalid vertex index");
    }
    return adjacencyMatrix[u][v];
}

// Returns the adjacency matrix
int** Graph::getGraph() const {
    return adjacencyMatrix;
}

} // namespace graph
