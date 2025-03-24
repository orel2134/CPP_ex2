#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "graph.hpp"

namespace graph {

class Algorithms {
public:
    static Graph bfs(const Graph& g, int start);
    static Graph dfs(const Graph& g, int start);
    static Graph dijkstra(const Graph& g, int src);
    static Graph prim(const Graph& g);
    static Graph kruskal(const Graph& g);
};

} // namespace graph

#endif // ALGORITHMS_HPP
