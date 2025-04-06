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

TEST_CASE("Graph - Adjacency Matrix Access") {
    Graph g(2);
    g.addEdge(0, 1, 4);
    int** mat = g.getGraph();
    CHECK(mat[0][1] == 4);
    CHECK(mat[1][0] == 4);
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
