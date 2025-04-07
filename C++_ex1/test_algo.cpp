//orel2744@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.hpp"
#include "algorithms.hpp"
#include "helpers.hpp"


using namespace graph;

// ///////////////////// BFS ///////////
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

TEST_CASE("BFS - Disconnected Components") {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    Graph bfsTree = Algorithms::bfs(g, 0);
    CHECK(bfsTree.isEdge(0, 1));
    CHECK(bfsTree.isEdge(1, 2));
    CHECK_FALSE(bfsTree.isEdge(3, 4));
}

TEST_CASE("BFS - Full Connected Graph") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    Graph bfsTree = Algorithms::bfs(g, 0);
    CHECK(bfsTree.isEdge(0, 1));
    CHECK(bfsTree.isEdge(0, 2));
    CHECK(bfsTree.isEdge(0, 3));// all vertices add directly from the root
}

////////////////
TEST_CASE("BFS - Tree structure correctness (layered)") {
    Graph g(6);
    // BFS should go: 0 -> 1,2 -> 3
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3); //two ways to 3, BFS should take the first to arrive in order.

    Graph bfsTree = Algorithms::bfs(g, 0);

    // 0 -> 1 and 0 -> 2 must be taken first (layer 1)
    CHECK(bfsTree.isEdge(0, 1));
    CHECK(bfsTree.isEdge(0, 2));

    // node 3 can only be connected through one of the two: either 1 or 2
    // we just verify that one of them was picked, and not both
    bool has1to3 = bfsTree.isEdge(1, 3);
    bool has2to3 = bfsTree.isEdge(2, 3);
    CHECK((has1to3 != has2to3)); // exactly one path should exist
}




TEST_CASE("BFS - Star topology") {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 3);
    g.addEdge(0, 4);
    g.addEdge(0, 5);

    Graph bfsTree = Algorithms::bfs(g, 0);

    for (int i = 1; i < 6; ++i) {
        CHECK(bfsTree.isEdge(0, i));
    }
}



/////////////





// ///////////////////// DFS ///////////
TEST_CASE("DFS Algorithm - Basic Cases") {
    Graph g1(0);
    CHECK_THROWS_WITH(Algorithms::dfs(g1, 0), "Invalid vertex index");

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

TEST_CASE("DFS - Deep Chain with Back Edge") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    Graph dfsTree = Algorithms::dfs(g, 0);
    CHECK(dfsTree.isEdge(0, 1));
    CHECK(dfsTree.isEdge(1, 2));
    CHECK(dfsTree.isEdge(2, 3));
    CHECK(dfsTree.isEdge(3, 4));
}

TEST_CASE("DFS Algorithm - Branching") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    Graph dfsTree = Algorithms::dfs(g, 0);
    CHECK(dfsTree.isEdge(0, 1));
    CHECK(dfsTree.isEdge(1, 3));
    CHECK(dfsTree.isEdge(0, 2));
    CHECK(dfsTree.isEdge(2, 4));
    CHECK_FALSE(dfsTree.isEdge(0, 3));
    CHECK_FALSE(dfsTree.isEdge(1, 2));
    CHECK_FALSE(dfsTree.isEdge(1, 4));
}

TEST_CASE("DFS Algorithm - Edge Cases") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 0);
    Graph dfsTree = Algorithms::dfs(g, 0);
    CHECK(dfsTree.isEdge(0, 1));
    CHECK(dfsTree.isEdge(1, 2));
}

//  disconnected DFS graph
TEST_CASE("DFS - disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(2, 3);  // Separate component
    Graph tree = Algorithms::dfs(g, 0);
    CHECK(tree.isEdge(0, 1));
    CHECK_FALSE(tree.isEdge(2, 3));
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





TEST_CASE("Dijkstra should throw on negative weight") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, -4); // Invalid for Dijkstra

    CHECK_THROWS_WITH(Algorithms::dijkstra(g, 0), "Dijkstra cannot handle negative edge weights");
}

/////////////////////////
TEST_CASE("Dijkstra - Result tree has no cycles") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 1);
    g.addEdge(3, 4, 4);
    g.addEdge(0, 4, 100); // לא ייכנס בגלל משקל גבוה

    Graph result = Algorithms::dijkstra(g, 0);

    // Use Disjoint Set to detect cycles
    int n = result.getNumVertices();
    REQUIRE(n > 0);
    DisjointSet ds(n);
    bool hasCycle = false;

    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            if (result.isEdge(u, v)) {
                if (ds.find(u) == ds.find(v)) {
                    hasCycle = true;
                } else {
                    ds.unite(u, v);
                }
            }
        }
    }

    CHECK_FALSE(hasCycle);
}





/////////////////



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




///////////
TEST_CASE("Prim with Negative Weights") {
    Graph g(4);
    g.addEdge(0, 1, -2);
    g.addEdge(1, 2, 4);
    g.addEdge(2, 3, -1);
    g.addEdge(0, 3, 3);

    Graph primTree = Algorithms::prim(g);

    // Prim should still select the minimum weight edges (even if negative)
    CHECK(primTree.isEdge(0, 1)); // -2
    CHECK(primTree.isEdge(2, 3)); // -1
    // the third edge could be 1-2 or 0-3 depending on internal priority, so we allow both:
    CHECK((primTree.isEdge(1, 2) || primTree.isEdge(0, 3)));
}



TEST_CASE("Prim throws on disconnected graph") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 1); // Component disconnected from 0 and 1

    CHECK_THROWS_WITH(Algorithms::prim(g), "Graph is not connected");
}


//////////

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




///////////

TEST_CASE("Kruskal with Negative Weights") {
    Graph g(4);
    g.addEdge(0, 1, -2);
    g.addEdge(1, 2, 4);
    g.addEdge(2, 3, -1);
    g.addEdge(0, 3, 3);

    Graph kruskalTree = Algorithms::kruskal(g);

    CHECK(kruskalTree.isEdge(0, 1)); // -2
    CHECK(kruskalTree.isEdge(2, 3)); // -1
    CHECK(kruskalTree.isEdge(0, 3)); // 3 was added
    CHECK_FALSE(kruskalTree.isEdge(1, 2)); // not included (would cause cycle)
}



//////////

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










