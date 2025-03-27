#include "graph.hpp"

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

// Prints the adjacency matrix
void Graph::printGraph() const {
    if (numVertices == 0) {
        std::cout << "Graph is empty." << std::endl;
        return;
    }

    for (size_t i = 0; i < numVertices; i++) {
        std::cout << i << ": ";
        for (size_t j = 0; j < numVertices; j++) {
            if (adjacencyMatrix[i][j] != INT_MAX) {
                std::cout << "(" << j << ", " << adjacencyMatrix[i][j] << ") ";
            }
        }
        std::cout << std::endl;
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
