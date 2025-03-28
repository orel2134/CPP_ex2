#include <iostream>
#include "graph.hpp"
#include "algorithms.hpp"

using namespace graph;

void printMenu() {
    std::cout << "\nGraph Algorithms Menu:\n";
    std::cout << "1. Run BFS\n";
    std::cout << "2. Run DFS\n";
    std::cout << "3. Run Dijkstra\n";
    std::cout << "4. Run Prim\n";
    std::cout << "5. Run Kruskal\n";
    std::cout << "6. Print Graph\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    int vertices, choice, src;

    std::cout << "Enter number of vertices in the graph: ";
    std::cin >> vertices;

    Graph graph(vertices);

    std::cout << "Enter number of edges: ";
    int edges;
    std::cin >> edges;

    std::cout << "Enter edges in format (src dest weight):\n";
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        std::cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    while (true) {
        printMenu();
        std::cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                std::cout << "Enter start vertex for BFS: ";
                std::cin >> src;
                Graph bfsTree = Algorithms::bfs(graph, src);
                std::cout << "BFS Tree:\n";
                bfsTree.printGraph();
                break;
            }
            case 2: {
                std::cout << "Enter start vertex for DFS: ";
                std::cin >> src;
                Graph dfsTree = Algorithms::dfs(graph, src);
                std::cout << "DFS Tree:\n";
                dfsTree.printGraph();
                break;
            }
            case 3: {
                std::cout << "Enter start vertex for Dijkstra: ";
                std::cin >> src;
                Graph dijkstraTree = Algorithms::dijkstra(graph, src);
                std::cout << "Dijkstra Tree:\n";
                dijkstraTree.printGraph();
                break;
            }
            case 4: {
                Graph primTree = Algorithms::prim(graph);
                std::cout << "Minimum Spanning Tree (Prim's Algorithm):\n";
                primTree.printGraph();
                break;
            }
            case 5: {
                Graph kruskalTree = Algorithms::kruskal(graph);
                std::cout << "Minimum Spanning Tree (Kruskal's Algorithm):\n";
                kruskalTree.printGraph();
                break;
            }
            case 6: {
                std::cout << "Current Graph:\n";
                graph.printGraph();
                break;
            }
            default:
                std::cout << "Invalid choice! Try again.\n";
        }
    }

    std::cout << "Exiting program...\n";
    return 0;
}
