#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.hpp"
#include "algorithms.hpp"

using namespace graph;

// ------------------------ BFS ------------------------
TEST_CASE("BFS Algorithm - Basic Cases") {
    Graph g1(0);
    CHECK(Algorithms::bfs(g1, 0).getNumVertices() == 0);

    Graph g2(1);
    Graph bfsTree2 = Algorithms::bfs(g2, 0);
    CHECK(bfsTree2.getNumVertices() == 1);

    Graph g3(3);
    g3.addEdge(0, 1, 1);
    g3.addEdge(1, 2, 1);
    Graph bfsTree3 = Algorithms::bfs(g3, 0);
    CHECK(bfsTree3.isEdge(0, 1));
    CHECK(bfsTree3.isEdge(1, 2));
    CHECK_FALSE(bfsTree3.isEdge(0, 2));
}

TEST_CASE("BFS Algorithm - Large Graph & Edge Cases") {
    Graph g4(10);
    g4.addEdge(0, 1);
    g4.addEdge(1, 2);
    g4.addEdge(2, 3);
    g4.addEdge(3, 4);
    g4.addEdge(4, 5);
    Graph bfsTree4 = Algorithms::bfs(g4, 0);
    CHECK(bfsTree4.isEdge(0, 1));
    CHECK(bfsTree4.isEdge(1, 2));
    CHECK(bfsTree4.isEdge(2, 3));

    Graph g5(6);
    g5.addEdge(0, 1);
    g5.addEdge(1, 2);
    g5.addEdge(3, 4);
    Graph bfsTree5 = Algorithms::bfs(g5, 0);
    CHECK_FALSE(bfsTree5.isEdge(3, 4));
}

// ------------------------ DFS ------------------------
TEST_CASE("DFS Algorithm - Basic Cases") {
    Graph g1(0);
    CHECK(Algorithms::dfs(g1, 0).getNumVertices() == 0);

    Graph g2(1);
    Graph dfsTree2 = Algorithms::dfs(g2, 0);
    CHECK(dfsTree2.getNumVertices() == 1);

    Graph g3(3);
    g3.addEdge(0, 1, 1);
    g3.addEdge(1, 2, 1);
    Graph dfsTree3 = Algorithms::dfs(g3, 0);
    CHECK(dfsTree3.isEdge(0, 1));
    CHECK(dfsTree3.isEdge(1, 2));
    CHECK_FALSE(dfsTree3.isEdge(0, 2));
}

TEST_CASE("DFS Algorithm - Edge Cases") {
    Graph g4(4);
    g4.addEdge(0, 1);
    g4.addEdge(1, 2);
    g4.addEdge(2, 3);
    g4.addEdge(3, 0);
    Graph dfsTree4 = Algorithms::dfs(g4, 0);
    CHECK(dfsTree4.isEdge(0, 1));
    CHECK(dfsTree4.isEdge(1, 2));
}

// ------------------------ Dijkstra ------------------------
TEST_CASE("Dijkstra Algorithm - Basic Cases") {
    Graph g1(0);
    CHECK(Algorithms::dijkstra(g1, 0).getNumVertices() == 0);

    Graph g2(1);
    Graph dijkstraTree2 = Algorithms::dijkstra(g2, 0);
    CHECK(dijkstraTree2.getNumVertices() == 1);

    Graph g3(3);
    g3.addEdge(0, 1, 2);
    g3.addEdge(1, 2, 3);
    Graph dijkstraTree3 = Algorithms::dijkstra(g3, 0);
    CHECK(dijkstraTree3.isEdge(0, 1));
    CHECK(dijkstraTree3.isEdge(1, 2));
    CHECK_FALSE(dijkstraTree3.isEdge(0, 2));
}

TEST_CASE("Dijkstra Algorithm - Edge Cases") {
    Graph g4(5);
    g4.addEdge(0, 1, 10);
    g4.addEdge(1, 2, 1);
    g4.addEdge(2, 3, 5);
    g4.addEdge(3, 4, 100);
    Graph dijkstraTree4 = Algorithms::dijkstra(g4, 0);
    CHECK_FALSE(dijkstraTree4.isEdge(0, 4));

    Graph g5(3);
    g5.addEdge(0, 1, 5);
    g5.addEdge(1, 2, 10);
    Graph dijkstraTree5 = Algorithms::dijkstra(g5, 0);
    CHECK(dijkstraTree5.isEdge(0, 1));
}

// ------------------------ Prim ------------------------
TEST_CASE("Prim Algorithm - Basic Cases") {
    Graph g1(0);
    CHECK(Algorithms::prim(g1).getNumVertices() == 0);

    Graph g2(1);
    Graph primTree2 = Algorithms::prim(g2);
    CHECK(primTree2.getNumVertices() == 1);

    Graph g3(3);
    g3.addEdge(0, 1, 1);
    g3.addEdge(1, 2, 2);
    g3.addEdge(0, 2, 3);
    Graph primTree3 = Algorithms::prim(g3);
    CHECK_FALSE(primTree3.isEdge(0, 2));
}

TEST_CASE("Prim Algorithm - Edge Cases") {
    Graph g4(5);
    g4.addEdge(0, 1, 10);
    g4.addEdge(1, 2, 20);
    g4.addEdge(2, 3, 30);
    g4.addEdge(3, 4, 40);
    Graph primTree4 = Algorithms::prim(g4);
    CHECK_FALSE(primTree4.isEdge(0, 4));

    Graph g5(6);
    g5.addEdge(0, 1, 1);
    g5.addEdge(2, 3, 5);
    CHECK_THROWS(Algorithms::prim(g5));
}

// ------------------------ Kruskal ------------------------
TEST_CASE("Kruskal Algorithm - Basic Cases") {
    Graph g1(0);
    CHECK(Algorithms::kruskal(g1).getNumVertices() == 0);

    Graph g2(1);
    Graph kruskalTree2 = Algorithms::kruskal(g2);
    CHECK(kruskalTree2.getNumVertices() == 1);

    Graph g3(4);
    g3.addEdge(0, 1, 1);
    g3.addEdge(1, 2, 2);
    g3.addEdge(2, 3, 3);
    g3.addEdge(0, 3, 10);
    Graph kruskalTree3 = Algorithms::kruskal(g3);
    CHECK_FALSE(kruskalTree3.isEdge(0, 3));
}

TEST_CASE("Kruskal Algorithm - Edge Cases") {
    Graph g5(6);
    g5.addEdge(0, 1, 1);
    g5.addEdge(2, 3, 5);
    Graph kruskalTree5 = Algorithms::kruskal(g5);
    CHECK(kruskalTree5.isEdge(0, 1));  
    CHECK(kruskalTree5.isEdge(2, 3));  
}

// ------------------------ Print Example ------------------------
TEST_CASE("Visual Print of BFS Tree") {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    Graph tree = Algorithms::bfs(g, 0);

    std::cout << "\nBFS Tree rooted at 0:\n";
    tree.printGraph(0); // 
}
