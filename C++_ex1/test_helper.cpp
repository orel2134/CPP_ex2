#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "helpers.hpp"

// Test Queue
TEST_CASE("Queue - basic operations") {
    Queue q(3);
    CHECK(q.isEmpty());

    q.push(1);
    q.push(2);
    q.push(3);

    CHECK_FALSE(q.isEmpty());
    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);
    CHECK(q.pop() == 3);
    CHECK(q.pop() == -1);  // underflow
}

TEST_CASE("Queue - Overflow behavior") {
    Queue q(3);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4); // לא ייכנס כי העומק מלא
    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);
    CHECK(q.pop() == 3);
    CHECK(q.pop() == -1); // התור ריק
}

TEST_CASE("Queue - Push after pop") {
    Queue q(2);
    q.push(5);
    q.push(10);
    CHECK(q.pop() == 5);
    q.push(15); 
    CHECK(q.pop() == 10);
    CHECK(q.pop() == 15);
    CHECK(q.pop() == -1);
}

TEST_CASE("Queue - Empty immediately after creation") {
    Queue q(5);
    CHECK(q.isEmpty());
}

TEST_CASE("Queue - Push after full and multiple pops") {
    Queue q(3);
    q.push(10);
    q.push(20);
    q.push(30);
    CHECK(q.pop() == 10);
    q.push(40);  // its can be becuse we deleted place
    CHECK(q.pop() == 20);
    CHECK(q.pop() == 30);
    CHECK(q.pop() == 40);
    CHECK(q.pop() == -1);  // empty queue
}



























///////////////////////////////////////

// Test DisjointSet
TEST_CASE("DisjointSet - basic union/find") {
    DisjointSet ds(5);

    CHECK(ds.find(0) == 0);
    CHECK(ds.find(1) == 1);

    ds.unite(0, 1);
    CHECK(ds.find(0) == ds.find(1));

    ds.unite(1, 2);
    CHECK(ds.find(2) == ds.find(0));

    CHECK(ds.find(3) != ds.find(0));
    ds.unite(3, 0);
    CHECK(ds.find(3) == ds.find(2));
}




TEST_CASE("DisjointSet - Find returns self for new elements") {
    DisjointSet ds(4);
    for (int i = 0; i < 4; i++) {
        CHECK(ds.find(i) == i);
    }
}

TEST_CASE("DisjointSet - Unite two sets and test find") {
    DisjointSet ds(4);
    ds.unite(0, 1);
    CHECK(ds.find(0) == ds.find(1)); // אמורים להיות באותו קבוצה
    ds.unite(2, 3);
    CHECK(ds.find(2) == ds.find(3));
}

TEST_CASE("DisjointSet - Unite multiple sets") {
    DisjointSet ds(6);
    ds.unite(0, 1);
    ds.unite(1, 2);
    ds.unite(2, 3);
    CHECK(ds.find(0) == ds.find(3));
    CHECK(ds.find(1) == ds.find(2));
}

TEST_CASE("DisjointSet - Rank optimization works (no cycles)") {
    DisjointSet ds(3);
    ds.unite(0, 1);
    ds.unite(1, 2);
    CHECK(ds.find(0) == ds.find(2));
    CHECK(ds.find(1) == ds.find(2));
}
//////////


TEST_CASE("DisjointSet - multiple find compressions") {
    DisjointSet ds(5);
    ds.unite(0, 1);
    ds.unite(1, 2);
    ds.unite(2, 3);
    int root = ds.find(3);
    CHECK(ds.find(0) == root);
    CHECK(ds.find(1) == root);
    CHECK(ds.find(2) == root);
    CHECK(ds.find(3) == root);
}

TEST_CASE("DisjointSet - no union if already in same set") {
    DisjointSet ds(3);
    ds.unite(0, 1);
    int rootBefore = ds.find(1);
    ds.unite(0, 1);
    int rootAfter = ds.find(1);
    CHECK(rootBefore == rootAfter);
}

TEST_CASE("DisjointSet - all elements into one set") {
    DisjointSet ds(6);
    for (int i = 0; i < 5; i++) {
        ds.unite(i, i+1);
    }
    int root = ds.find(0);
    for (int i = 1; i < 6; i++) {
        CHECK(ds.find(i) == root);
    }
}
