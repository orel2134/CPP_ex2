/*
 * Graph implementation using adjacency list
 * orel2744@gmail.com
 *
 */

 #include "graph.hpp"
 #include <stdexcept>
 #include <iostream>
 #include <climits>
 
 namespace graph {
 
 // Constructor
 Graph::Graph(size_t vertices) : numVertices(vertices) {
     adjList = new Edge*[numVertices];
     for (size_t i = 0; i < numVertices; i++) {
         adjList[i] = nullptr;
     }
 }
 
 // Destructor
 Graph::~Graph() {
     clearEdges();
     delete[] adjList;
 }
 
 // Helper function to clear all edges
 void Graph::clearEdges() {
     for (size_t i = 0; i < numVertices; i++) {
         Edge* current = adjList[i];
         while (current != nullptr) {
             Edge* temp = current;
             current = current->next;
             delete temp;
         }
         adjList[i] = nullptr;
     }
 }
 
 // Copy constructor
 Graph::Graph(const Graph& other) : numVertices(other.numVertices) {
     adjList = new Edge*[numVertices];
     for (size_t i = 0; i < numVertices; i++) {
         adjList[i] = nullptr;
         Edge* otherCurrent = other.adjList[i];
         Edge** current = &adjList[i];
         
         while (otherCurrent != nullptr) {
             *current = new Edge(otherCurrent->dest, otherCurrent->weight);
             current = &((*current)->next);
             otherCurrent = otherCurrent->next;
         }
     }
 }
 
 // Assignment operator
 Graph& Graph::operator=(const Graph& other) {
     if (this != &other) {
         clearEdges();
         delete[] adjList;
         
         numVertices = other.numVertices;
         adjList = new Edge*[numVertices];
         
         for (size_t i = 0; i < numVertices; i++) {
             adjList[i] = nullptr;
             Edge* otherCurrent = other.adjList[i];
             Edge** current = &adjList[i];
             
             while (otherCurrent != nullptr) {
                 *current = new Edge(otherCurrent->dest, otherCurrent->weight);
                 current = &((*current)->next);
                 otherCurrent = otherCurrent->next;
             }
         }
     }
     return *this;
 }
 
 // Helper function to find an edge
 Graph::Edge* Graph::findEdge(int src, int dest) const {
     if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
         throw std::out_of_range("Invalid vertex index");
     }
     
     Edge* current = adjList[src];
     while (current != nullptr && current->dest != dest) {
         current = current->next;
     }
     return current;
 }
 
 // Add edge
 void Graph::addEdge(int src, int dest, int weight) {
     if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
         throw std::out_of_range("Invalid vertex index");
     }
     if (weight == 0) {
         throw std::invalid_argument("Edge weight must be non-zero");
     }
     if (src == dest) {
         throw std::invalid_argument("Self loops are not allowed");
     }
     if (isEdge(src, dest)) {
         throw std::runtime_error("Edge already exists between vertices");
     }
     
     // Add edge from src to dest
     Edge* newEdge = new Edge(dest, weight);
     newEdge->next = adjList[src];
     adjList[src] = newEdge;
     
     // Add edge from dest to src (undirected graph)
     newEdge = new Edge(src, weight);
     newEdge->next = adjList[dest];
     adjList[dest] = newEdge;
 }
 
 // Remove edge
 void Graph::removeEdge(int src, int dest) {
     if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
         throw std::out_of_range("Invalid vertex index");
     }
     if (!isEdge(src, dest)) {
         throw std::runtime_error("Edge does not exist");
     }
     
     // Remove edge from src to dest
     Edge* current = adjList[src];
     Edge* prev = nullptr;
     while (current != nullptr && current->dest != dest) {
         prev = current;
         current = current->next;
     }
     
     if (prev == nullptr) {
         adjList[src] = current->next;
     } else {
         prev->next = current->next;
     }
     delete current;
     
     // Remove edge from dest to src
     current = adjList[dest];
     prev = nullptr;
     while (current != nullptr && current->dest != src) {
         prev = current;
         current = current->next;
     }
     
     if (prev == nullptr) {
         adjList[dest] = current->next;
     } else {
         prev->next = current->next;
     }
     delete current;
 }
 
 // Print graph
 void Graph::printGraph() const {
     for (size_t i = 0; i < numVertices; i++) {
         std::cout << "Vertex " << i << ": ";
         Edge* current = adjList[i];
         while (current != nullptr) {
             std::cout << "(" << current->dest << ", " << current->weight << ") ";
             current = current->next;
         }
         std::cout << std::endl;
     }
 }
 
 // Print graph from root
 void Graph::printGraph(int root, int level, bool* visited) const {
     if (root < 0 || root >= numVertices) {
         throw std::out_of_range("Invalid vertex index");
     }
 
     bool isTopLevel = false;
     if (!visited) {
         visited = new bool[numVertices]();
         isTopLevel = true;
     }
 
     visited[root] = true;
     
     for (int i = 0; i < level; ++i) std::cout << "  ";
     std::cout << root << std::endl;
 
     Edge* current = adjList[root];
     while (current != nullptr) {
         if (!visited[current->dest]) {
             printGraph(current->dest, level + 1, visited);
         }
         current = current->next;
     }
 
     if (isTopLevel) {
         delete[] visited;
     }
 }
 
 // Get number of vertices
 size_t Graph::getNumVertices() const {
     return numVertices;
 }
 
 // Check if edge exists
 bool Graph::isEdge(int u, int v) const {
     try {
         return findEdge(u, v) != nullptr;
     } catch (const std::out_of_range& e) {
         throw;
     }
 }
 
 // Get edge weight
 int Graph::weight(int u, int v) const {
     Edge* edge = findEdge(u, v);
     if (edge == nullptr) {
         throw std::runtime_error("Edge does not exist");
     }
     return edge->weight;
 }
 
 } // namespace graph