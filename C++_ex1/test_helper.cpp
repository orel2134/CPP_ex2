
#include "helpers.hpp"
# include "helpers.cpp"
#include "doctest.h"


//test for implemant of Queue

TEST_CASE("Queue - Basic Operations") {
    Queue q(5);
    CHECK(q.isEmpty());

    q.push(10);
    q.push(20);
    q.push(30);
    CHECK_FALSE(q.isEmpty());

    CHECK(q.pop() == 10);
    CHECK(q.pop() == 20);
    CHECK(q.pop() == 30);
    CHECK(q.pop() == -1); // Attempt to pop from empty queue
}



// test for DisjointSet

TEST_CASE("DisjointSet - Union-Find Operations") {
    DisjointSet ds(5);

    // Initially, each node is its own parent
    CHECK(ds.find(0) == 0);
    CHECK(ds.find(1) == 1);

    // Unite some sets
    ds.unite(0, 1);
    CHECK(ds.find(0) == ds.find(1));

    ds.unite(2, 3);
    CHECK(ds.find(2) == ds.find(3));

    // Ensure they are still separated
    CHECK(ds.find(0) != ds.find(2));

    // Unite the sets together
    ds.unite(1, 2);
    CHECK(ds.find(0) == ds.find(3)); // Now all 0-3 should be connected
}



