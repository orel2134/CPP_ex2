//orel2744@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.hpp"

using namespace graph;

TEST_CASE("Graph - Constructor and getNumVertices") {
    Graph g(5);
    CHECK(g.getNumVertices() == 5);
}

TEST_CASE("Graph - Add and check edge") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    CHECK(g.isEdge(0, 1));
    CHECK(g.isEdge(1, 0));  // symmetry in undirected graph
    CHECK(g.weight(0, 1) == 10);
    CHECK(g.weight(1, 0) == 10);
}

TEST_CASE("Graph - Add edge with invalid indices") {
    Graph g(3);
    CHECK_THROWS_AS(g.addEdge(3, 1, 5), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(1, 3, 5), std::out_of_range);
    CHECK_THROWS_AS(g.addEdge(0, 2, 0), std::invalid_argument); // zero weight not allowed
}

TEST_CASE("Graph - Remove edge") {
    Graph g(4);
    g.addEdge(0, 2, 8);
    g.removeEdge(0, 2);
    CHECK_FALSE(g.isEdge(0, 2));
    CHECK_FALSE(g.isEdge(2, 0));
}

TEST_CASE("Graph - Remove non-existent edge") {
    Graph g(2);
    CHECK_THROWS_AS(g.removeEdge(0, 1), std::runtime_error);
    CHECK_THROWS_AS(g.removeEdge(5, 1), std::out_of_range);
}

TEST_CASE("Graph - isEdge with invalid indices") {
    Graph g(3);
    CHECK_THROWS_AS(g.isEdge(3, 1), std::out_of_range);
    CHECK_THROWS_AS(g.isEdge(1, 3), std::out_of_range);
}

TEST_CASE("Graph - weight with invalid indices") {
    Graph g(2);
    CHECK_THROWS_AS(g.weight(2, 1), std::out_of_range);
    CHECK_THROWS_AS(g.weight(1, 2), std::out_of_range);
}

TEST_CASE("Adjacency List Structure Tests") {
    Graph g(4);
    
    // Test empty graph
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            CHECK_FALSE(g.isEdge(i, j));
        }
    }

    // Add multiple edges from same source
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 3);
    g.addEdge(0, 3, 4);
    
    // Verify edges and weights
    CHECK(g.isEdge(0, 1));
    CHECK(g.isEdge(0, 2));
    CHECK(g.isEdge(0, 3));
    CHECK(g.weight(0, 1) == 2);
    CHECK(g.weight(0, 2) == 3);
    CHECK(g.weight(0, 3) == 4);
    
    // Test edge removal in adjacency list
    g.removeEdge(0, 2);
    CHECK_FALSE(g.isEdge(0, 2));
    CHECK(g.isEdge(0, 1));  // Other edges should remain
    CHECK(g.isEdge(0, 3));
}

TEST_CASE("Graph Symmetry in Adjacency List") {
    Graph g(3);
    
    // Test adding edges
    g.addEdge(0, 1, 5);
    CHECK(g.isEdge(0, 1));
    CHECK(g.isEdge(1, 0));  // Check symmetry
    CHECK(g.weight(0, 1) == 5);
    CHECK(g.weight(1, 0) == 5);  // Check weight symmetry
    
    // Add more edges
    g.addEdge(1, 2, 3);
    CHECK(g.isEdge(1, 2));
    CHECK(g.isEdge(2, 1));
    CHECK(g.weight(1, 2) == 3);
    CHECK(g.weight(2, 1) == 3);
    
    // Test removal symmetry
    g.removeEdge(0, 1);
    CHECK_FALSE(g.isEdge(0, 1));
    CHECK_FALSE(g.isEdge(1, 0));
    
    // Other edges should remain
    CHECK(g.isEdge(1, 2));
    CHECK(g.isEdge(2, 1));
}

TEST_CASE("Complex Adjacency List Operations") {
    Graph g(5);
    
    // Create a more complex graph structure
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 5);
    g.addEdge(4, 0, 6);  // Create a cycle
    
    // Verify all edges and weights
    CHECK(g.isEdge(0, 1));
    CHECK(g.weight(0, 1) == 2);
    CHECK(g.isEdge(1, 2));
    CHECK(g.weight(1, 2) == 3);
    CHECK(g.isEdge(2, 3));
    CHECK(g.weight(2, 3) == 4);
    CHECK(g.isEdge(3, 4));
    CHECK(g.weight(3, 4) == 5);
    CHECK(g.isEdge(4, 0));
    CHECK(g.weight(4, 0) == 6);
    
    // Test removing edges from cycle
    g.removeEdge(2, 3);
    CHECK_FALSE(g.isEdge(2, 3));
    CHECK_FALSE(g.isEdge(3, 2));
    CHECK(g.isEdge(3, 4));  // Adjacent edges should remain
    CHECK(g.isEdge(1, 2));
}

TEST_CASE("Duplicate Edge Handling") {
    Graph g(4);
    
    // Add initial edge
    g.addEdge(0, 1, 5);
    
    // Try to add duplicate edge - should throw
    CHECK_THROWS_WITH(g.addEdge(0, 1, 10), "Edge already exists between vertices");
    CHECK_THROWS_WITH(g.addEdge(1, 0, 10), "Edge already exists between vertices");
    
    // Verify original edge weight remains unchanged
    CHECK(g.weight(0, 1) == 5);
    CHECK(g.weight(1, 0) == 5);
}

TEST_CASE("Edge Count and Density Tests") {
    Graph g(4);
    
    // Add edges and verify count
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);
    
    // Count edges (remember each edge is counted twice in undirected graph)
    int edgeCount = 0;
    for(size_t i = 0; i < g.getNumVertices(); i++) {
        for(size_t j = 0; j < g.getNumVertices(); j++) {
            if(g.isEdge(i, j)) edgeCount++;
        }
    }
    CHECK(edgeCount == 6);  // 3 edges * 2 (due to undirected nature)
}

TEST_CASE("Edge Weight Updates and Validation") {
    Graph g(3);
    
    // Try to add edge with zero weight
    CHECK_THROWS_WITH(g.addEdge(0, 1, 0), "Edge weight must be non-zero");
    
    // Add valid edge and verify
    g.addEdge(0, 1, 5);
    CHECK(g.weight(0, 1) == 5);
    CHECK(g.weight(1, 0) == 5);
}

TEST_CASE("Graph - Print (visual check only)") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 3, 1);

    std::cout << "\n--- Printing Graph Structure ---\n";
    g.printGraph(0);  // visual output test
    std::cout << "--------------------------------\n";
}

TEST_CASE("Isolated Vertices Test") {
    Graph g(5);
    
    // Add edge only between two vertices
    g.addEdge(1, 3, 2);
    
    // Check that other vertices are isolated
    CHECK_FALSE(g.isEdge(0, 1));
    CHECK_FALSE(g.isEdge(0, 2));
    CHECK_FALSE(g.isEdge(0, 3));
    CHECK_FALSE(g.isEdge(0, 4));
    CHECK_FALSE(g.isEdge(2, 4));
    
    // Verify the only edge that exists
    CHECK(g.isEdge(1, 3));
    CHECK(g.isEdge(3, 1));
    CHECK(g.weight(1, 3) == 2);
}

TEST_CASE("Self-Loop Prevention") {
    Graph g(3);
    
    // Attempt to create self-loop
    CHECK_THROWS_WITH(g.addEdge(1, 1, 5), "Self loops are not allowed");
}

TEST_CASE("Complete Graph Tests") {
    Graph g(4);
    
    // Create a complete graph
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 1);
    
    // Verify all possible edges exist
    for(size_t i = 0; i < g.getNumVertices(); i++) {
        for(size_t j = i + 1; j < g.getNumVertices(); j++) {
            CHECK(g.isEdge(i, j));
            CHECK(g.isEdge(j, i));
        }
    }
}

TEST_CASE("Large Graph Edge Management") {
    const size_t size = 100;
    Graph g(size);
    
    // Add edges to create a chain
    for(size_t i = 0; i < size-1; i++) {
        g.addEdge(i, i+1, 1);
    }
    
    // Verify chain structure
    for(size_t i = 0; i < size-1; i++) {
        CHECK(g.isEdge(i, i+1));
        CHECK(g.isEdge(i+1, i));
        CHECK(g.weight(i, i+1) == 1);
    }
}