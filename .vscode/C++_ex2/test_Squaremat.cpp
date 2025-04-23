#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"
using namespace MyMath;

TEST_CASE("Addition operator +") {
    SquareMat A(2), B(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    B.set(0, 0, 5); B.set(0, 1, 6);
    B.set(1, 0, 7); B.set(1, 1, 8);
    SquareMat result = A + B;
    CHECK(result.get(0, 0) == 6);
    CHECK(result.get(0, 1) == 8);
    CHECK(result.get(1, 0) == 10);
    CHECK(result.get(1, 1) == 12);
}
//

TEST_CASE("Subtraction operator -") {
    SquareMat A(2), B(2);
    A.set(0, 0, 5); A.set(0, 1, 6);
    A.set(1, 0, 7); A.set(1, 1, 8);
    B.set(0, 0, 1); B.set(0, 1, 2);
    B.set(1, 0, 3); B.set(1, 1, 4);
    SquareMat result = A - B;
    CHECK(result.get(0, 0) == 4);
    CHECK(result.get(0, 1) == 4);
    CHECK(result.get(1, 0) == 4);
    CHECK(result.get(1, 1) == 4);
}

TEST_CASE("Scalar multiplication (mat * scalar)") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    SquareMat result = A * 2;
    CHECK(result.get(0, 0) == 2);
    CHECK(result.get(0, 1) == 4);
    CHECK(result.get(1, 0) == 6);
    CHECK(result.get(1, 1) == 8);
}

TEST_CASE("Scalar multiplication (scalar * mat)") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    SquareMat result = 2 * A;
    CHECK(result.get(0, 0) == 2);
    CHECK(result.get(0, 1) == 4);
    CHECK(result.get(1, 0) == 6);
    CHECK(result.get(1, 1) == 8);
}

TEST_CASE("Matrix multiplication") {
    SquareMat A(2), B(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    B.set(0, 0, 2); B.set(0, 1, 0);
    B.set(1, 0, 1); B.set(1, 1, 2);
    SquareMat result = A * B;
    CHECK(result.get(0, 0) == 4);
    CHECK(result.get(0, 1) == 4);
    CHECK(result.get(1, 0) == 10);
    CHECK(result.get(1, 1) == 8);
}

TEST_CASE("Equality operator ==") {
    SquareMat A(2), B(2);
    A.set(0, 0, 2); A.set(0, 1, 2);
    A.set(1, 0, 2); A.set(1, 1, 4);
    B.set(0, 0, 1); B.set(0, 1, 2);
    B.set(1, 0, 3); B.set(1, 1, 4);
    CHECK(A == B);
}

TEST_CASE("Inequality operator !=") {
    SquareMat A(2), B(2);
    A.set(0, 0, 1); A.set(0, 1, 1);
    A.set(1, 0, 1); A.set(1, 1, 1);
    B.set(0, 0, 2); B.set(0, 1, 2);
    B.set(1, 0, 2); B.set(1, 1, 2);
    CHECK(A != B);
}

TEST_CASE("Determinant operator !") {
    SquareMat A(2);
    A.set(0, 0, 4); A.set(0, 1, 6);
    A.set(1, 0, 3); A.set(1, 1, 8);
    CHECK((!A) == (4*8 - 6*3));
}

TEST_CASE("Exponentiation operator ^") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 1);
    A.set(1, 0, 1); A.set(1, 1, 0);
    SquareMat result = A ^ 2;
    CHECK(result.get(0, 0) == 2);
    CHECK(result.get(0, 1) == 1);
    CHECK(result.get(1, 0) == 1);
    CHECK(result.get(1, 1) == 1);
}
