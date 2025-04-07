//orel2744@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "helpers.hpp"

TEST_CASE("Queue Operations") {
    Queue q(3);
    
    CHECK(q.isEmpty());
    
    q.push(1);
    q.push(2);
    q.push(3);
    CHECK_FALSE(q.isEmpty());
    
    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);
    CHECK(q.pop() == 3);
    CHECK(q.isEmpty());
}

TEST_CASE("Queue Overflow") {
    Queue q(2);
    q.push(1);
    q.push(2);
    q.push(3);  // Should not be added
    
    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);
    CHECK(q.pop() == -1);  // Queue is empty
}

TEST_CASE("DisjointSet Operations") {
    DisjointSet ds(5);
    
    // Initially, each element should be in its own set
    CHECK(ds.find(0) == 0);
    CHECK(ds.find(1) == 1);
    CHECK(ds.find(2) == 2);
    
    // Test unions
    ds.unite(0, 1);
    CHECK(ds.find(0) == ds.find(1));
    
    ds.unite(2, 3);
    CHECK(ds.find(2) == ds.find(3));
    
    ds.unite(0, 2);
    CHECK(ds.find(0) == ds.find(2));
    CHECK(ds.find(1) == ds.find(3));
    
    // Element 4 should still be in its own set
    CHECK(ds.find(4) == 4);
}

TEST_CASE("DisjointSet Path Compression") {
    DisjointSet ds(5);
    
    ds.unite(0, 1);
    ds.unite(1, 2);
    ds.unite(2, 3);
    
    // After path compression, all elements should point to the same root
    int root = ds.find(3);
    CHECK(ds.find(0) == root);
    CHECK(ds.find(1) == root);
    CHECK(ds.find(2) == root);
    CHECK(ds.find(3) == root);
}