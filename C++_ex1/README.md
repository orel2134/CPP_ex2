# Graph Algorithms in C++

This project implements a set of classical **graph algorithms** in C++ using adjacency matrices and custom helper classes, **without using STL**.

##  Project Structure
C++_ex1/ │ ├── graph.hpp / graph.cpp # Graph data structure and related methods ├── algorithms.hpp / algorithms.cpp # Implementations of BFS, DFS, Dijkstra, Prim, Kruskal ├── helpers.hpp / helpers.cpp # Custom Queue and DisjointSet classes │ ├── test_algo.cpp # Unit tests for algorithms ├── test_graph.cpp # Unit tests for Graph class ├── test_helper.cpp # Unit tests for helpers ├── main.cpp # Optional main file │ ├── doctest.h # Unit testing framework ├── Makefile # Build system for compiling and running tests └── README.md # Project documentation

---

## ⚙️ Compilation & Build

Use the provided `Makefile` to compile the project and run tests.

### Build everything:

```bash
make all
make clean
make run_algo_tests
make run_graph_tests
make run_helper_tests
🧠 Algorithms Implemented
✔️ BFS (Breadth-First Search)
Implemented with a custom Queue class.

Builds a BFS tree from a given source vertex.

✔️ DFS (Depth-First Search)
Uses a manual stack to simulate recursion.

Builds a DFS tree from a source vertex.

✔️ Dijkstra
Finds shortest paths from a source node (no negative weights).

Builds a shortest-path tree using a parent array.

Ensures no cycles using Union-Find (Disjoint Set).

✔️ Prim’s Algorithm
Builds a Minimum Spanning Tree (MST) from any connected graph.

Uses arrays to track keys and parent relationships.

✔️ Kruskal’s Algorithm
Builds MST by sorting all edges and applying Union-Find.

Supports graphs with disconnected components and negative weights.

🧩 Helper Classes
Queue
Circular queue implementation with fixed size.

Used in BFS traversal.

DisjointSet
Union-Find with path compression and union by rank.

Used in Kruskal and Dijkstra (for cycle prevention).

 Testing with doctest
The project uses doctest, a lightweight C++ unit-testing framework.

Each test file is standalone and runs using:

bash
Copy
Edit
./test_algo      # or test_graph, test_helper
 Requirements
C++17 or higher

No use of STL containers like vector, queue, priority_queue

All memory is managed manually using new[] and delete[]

