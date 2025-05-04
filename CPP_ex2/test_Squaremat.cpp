#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"
#include <sstream>
using namespace MyMath;

// Test the addition operator: ensures element-wise matrix addition works correctly

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

// Test the unary minus operator: checks that all matrix values are correctly update
TEST_CASE("Unary minus operator -A") {
    SquareMat A(2);
    A.set(0, 0, -1); A.set(0, 1, 2);
    A.set(1, 0, -3); A.set(1, 1, 4);
    SquareMat result = -A;
    CHECK(result.get(0, 0) == 1);
    CHECK(result.get(0, 1) == -2);
    CHECK(result.get(1, 0) == 3);
    CHECK(result.get(1, 1) == -4);
}

TEST_CASE("Copy constructor") {
    SquareMat A(2);
    A.set(0, 0, 5); A.set(0, 1, 6);
    A.set(1, 0, 7); A.set(1, 1, 8);
    SquareMat B = A;
    CHECK(B.get(0, 0) == 5);
    CHECK(B.get(0, 1) == 6);
    CHECK(B.get(1, 0) == 7);
    CHECK(B.get(1, 1) == 8);
}

// Test the copy constructor: verifies deep copy behavior by comparing original and copied matrices
TEST_CASE("Assignment operator") {
    SquareMat A(2);
    A.set(0, 0, 3); A.set(0, 1, 4);
    A.set(1, 0, 5); A.set(1, 1, 6);
    SquareMat B(2);
    B = A;
    CHECK(B.get(0, 0) == 3);
    CHECK(B.get(0, 1) == 4);
    CHECK(B.get(1, 0) == 5);
    CHECK(B.get(1, 1) == 6);
}

// Test the assignment operator: ensures proper copying of content and no memory leaks or shallow copy

TEST_CASE("Comparison operators <, <=, >, >=") {
    SquareMat A(2), B(2);
    A.set(0, 0, 1); A.set(0, 1, 1);
    A.set(1, 0, 1); A.set(1, 1, 1);
    B.set(0, 0, 2); B.set(0, 1, 2);
    B.set(1, 0, 2); B.set(1, 1, 2);
    CHECK(A < B);
    CHECK(A <= B);
    CHECK_FALSE(A > B);
    CHECK_FALSE(A >= B);
    CHECK(B > A);
    CHECK(B >= A);
    CHECK_FALSE(B < A);
    CHECK_FALSE(B <= A);
}

// Test the pre-decrement operator (--A): checks that all elements are decremented before returning
TEST_CASE("Pre-decrement operator --A") {
    SquareMat A(2);
    A.set(0, 0, 3); A.set(0, 1, 3);
    A.set(1, 0, 3); A.set(1, 1, 3);
    SquareMat& result = --A;
    CHECK(result.get(0, 0) == 2);
    CHECK(result.get(0, 1) == 2);
    CHECK(result.get(1, 0) == 2);
    CHECK(result.get(1, 1) == 2);
}

// Test the post-decrement operator (A--): ensures values are returned before being decremented
TEST_CASE("Post-decrement operator A--") {
    SquareMat A(2);
    A.set(0, 0, 3); A.set(0, 1, 3);
    A.set(1, 0, 3); A.set(1, 1, 3);
    SquareMat result = A--;
    CHECK(result.get(0, 0) == 3);
    CHECK(result.get(0, 1) == 3);
    CHECK(result.get(1, 0) == 3);
    CHECK(result.get(1, 1) == 3);
    CHECK(A.get(0, 0) == 2);
    CHECK(A.get(0, 1) == 2);
    CHECK(A.get(1, 0) == 2);
    CHECK(A.get(1, 1) == 2);
}

// Test matrix exponentiation operator (^): verifies powers 0, 1, 2, and 5 produce correct results
// Power 0 should return identity matrix, power 1 returns the matrix itself, and higher powers apply repeated multiplication
TEST_CASE("Matrix exponentiation - powers 0, 1, 2, 5") {
    SquareMat A(2);
    A.set(0, 0, 2); A.set(0, 1, 0);
    A.set(1, 0, 0); A.set(1, 1, 2);

    SquareMat A0 = A ^ 0;
    CHECK(A0.get(0, 0) == 1);
    CHECK(A0.get(0, 1) == 0);
    CHECK(A0.get(1, 0) == 0);
    CHECK(A0.get(1, 1) == 1);

    SquareMat A1 = A ^ 1;
    CHECK(A1.get(0, 0) == 2);

    SquareMat A2 = A ^ 2;
    CHECK(A2.get(0, 0) == 4);

    SquareMat A5 = A ^ 5;
    CHECK(A5.get(0, 0) == 32);
}
// Test consecutive post-increment, pre-increment, post-decrement and pre-decrement operators
// Validates that values in the matrix update correctly with each operation, preserving expected arithmetic behavior
TEST_CASE("Multiple increment and decrement") {
    SquareMat A(2);
    A.set(0, 0, 5); A.set(0, 1, 5);
    A.set(1, 0, 5); A.set(1, 1, 5);

    A++;
    ++A;
    CHECK(A.get(0, 0) == 7);

    A--;
    --A;
    CHECK(A.get(0, 0) == 5);
}

// Test compound addition assignment: verifies that repeated use of the += operator accumulates values correctly.
// A starts with all ones. After A += A (twice), values should double twice: 1 → 2 → 4.
TEST_CASE("Multiple addition assignment") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 1);
    A.set(1, 0, 1); A.set(1, 1, 1);

    A += A;
    A += A;
    CHECK(A.get(0, 0) == 4);
}

// Test division by very small scalar: ensures numerical stability and accuracy using floating-point arithmetic.
// Dividing tiny values (1e-10) by 1e-5 should produce values close to 1e-5, verified using Approx.
TEST_CASE("Division by very small number") {
    SquareMat A(2);
    A.set(0, 0, 1e-10); A.set(0, 1, 1e-10);
    A.set(1, 0, 1e-10); A.set(1, 1, 1e-10);

    SquareMat result = A / 1e-5;
    CHECK(result.get(0, 0) == doctest::Approx(1e-5));
}

// Test out-of-bounds access using indexing operator []: ensures bounds checking throws exceptions.
// Attempts to access A[-1][0] and A[2][1] on a 2x2 matrix should throw std::invalid_argument.
TEST_CASE("Indexing operator [] - out of bounds access") {
    SquareMat A(2);
    CHECK_THROWS_AS(A[-1][0] = 5, std::invalid_argument);
    CHECK_THROWS_AS(A[2][1] = 5, std::invalid_argument);
}

/////////////////////////// Special  throw exception checks///////////////////////////

// Test invalid indices in set/get methods: ensures bounds checking works correctly for manual accessors.
// Attempts to access out-of-bounds indices using set() and get() should throw std::invalid_argument.
TEST_CASE("Set and get with invalid indices") {
    SquareMat A(2);
    CHECK_THROWS_AS(A.set(-1, 0, 5), std::invalid_argument);
    CHECK_THROWS_AS(A.get(2, 1), std::invalid_argument);
}

// Test constructor with illegal sizes: ensures that matrix cannot be constructed with non-positive dimensions.
// Creating a matrix of size 0 or negative should throw std::invalid_argument
TEST_CASE("Constructor with size 0 or negative") {
    CHECK_THROWS_AS(SquareMat(0), std::invalid_argument);
    CHECK_THROWS_AS(SquareMat(-5), std::invalid_argument);
}

// Test determinant operator on non-2x2 matrix: ensures proper exception is thrown for unsupported sizes.
// The determinant is only defined for 2x2 matrices; calling it on a 3x3 should throw std::logic_error.
TEST_CASE("Determinant on non-2x2 matrix") {
    SquareMat A(3);
    CHECK_THROWS_AS(!A, std::logic_error);
}


// Test the transpose operator: verifies that the matrix is transposed correctly,
// swapping rows with columns.

TEST_CASE("Transpose operator ~") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    SquareMat B = ~A;
    CHECK(B.get(0, 0) == 1);
    CHECK(B.get(0, 1) == 3);
    CHECK(B.get(1, 0) == 2);
    CHECK(B.get(1, 1) == 4);
}

// Test element-wise multiplication operator (A % B): checks that each element
// in the resulting matrix is the product of the corresponding elements in A and B

TEST_CASE("Element-wise multiplication (A % B)") {
    SquareMat A(2), B(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    B.set(0, 0, 5); B.set(0, 1, 6);
    B.set(1, 0, 7); B.set(1, 1, 8);
    SquareMat C = A % B;
    CHECK(C.get(0, 0) == 5);
    CHECK(C.get(0, 1) == 12);
    CHECK(C.get(1, 0) == 21);
    CHECK(C.get(1, 1) == 32);
}

// Test modulo operation with scalar: verifies that each element in the matrix A
// is correctly modulo-divided by the scalar (e.g., A[i][j] % scalar).

TEST_CASE("Modulo by scalar (A % scalar)") {
    SquareMat A(2);
    A.set(0, 0, 10); A.set(0, 1, 20);
    A.set(1, 0, 30); A.set(1, 1, 40);
    SquareMat B = A % 7;
    CHECK(B.get(0, 0) == 3);
    CHECK(B.get(0, 1) == 6);
    CHECK(B.get(1, 0) == 2);
    CHECK(B.get(1, 1) == 5);
}

// Test division of matrix by scalar: ensures each element of the matrix is divided
// correctly by the scalar and floating-point division is handled as expected.
TEST_CASE("Division by scalar (A / scalar)") {
    SquareMat A(2);
    A.set(0, 0, 8); A.set(0, 1, 16);
    A.set(1, 0, 24); A.set(1, 1, 32);
    SquareMat B = A / 8;
    CHECK(B.get(0, 0) == 1);
    CHECK(B.get(0, 1) == 2);
    CHECK(B.get(1, 0) == 3);
    CHECK(B.get(1, 1) == 4);
}


//////////////////// Tests for complex operations///////////////

// Test compound assignment operator +=: verifies element-wise addition is performed in-place.
// After A += B, each element A[i][j] should equal A[i][j] + B[i][j].
TEST_CASE("Compound assignment operator +=") {
    SquareMat A(2), B(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    B.set(0, 0, 5); B.set(0, 1, 6);
    B.set(1, 0, 7); B.set(1, 1, 8);
    A += B;
    CHECK(A.get(0, 0) == 6);
    CHECK(A.get(0, 1) == 8);
    CHECK(A.get(1, 0) == 10);
    CHECK(A.get(1, 1) == 12);
}

// Test compound assignment operator -=: ensures element-wise subtraction is performed in-place.
// After A -= B, each element A[i][j] should equal A[i][j] - B[i][j].
TEST_CASE("Compound assignment operator -=") {
    SquareMat A(2), B(2);
    A.set(0, 0, 5); A.set(0, 1, 6);
    A.set(1, 0, 7); A.set(1, 1, 8);
    B.set(0, 0, 1); B.set(0, 1, 2);
    B.set(1, 0, 3); B.set(1, 1, 4);
    A -= B;
    CHECK(A.get(0, 0) == 4);
    CHECK(A.get(0, 1) == 4);
    CHECK(A.get(1, 0) == 4);
    CHECK(A.get(1, 1) == 4);
}

// Test compound assignment operator *= for matrix multiplication: verifies that A is updated
// with the matrix product A * B using the standard matrix multiplication rules.

TEST_CASE("Compound assignment operator *= (matrix multiplication)") {
    SquareMat A(2), B(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    B.set(0, 0, 0); B.set(0, 1, 1);
    B.set(1, 0, 1); B.set(1, 1, 0);
    A *= B;
    CHECK(A.get(0, 0) == 2);
    CHECK(A.get(0, 1) == 1);
    CHECK(A.get(1, 0) == 4);
    CHECK(A.get(1, 1) == 3);
}

// Test compound assignment operator /= with scalar: confirms that A is divided element-wise
// by a scalar and each result is stored back in A.
TEST_CASE("Compound assignment operator /= (scalar division)") {
    SquareMat A(2);
    A.set(0, 0, 8); A.set(0, 1, 16);
    A.set(1, 0, 24); A.set(1, 1, 32);
    A /= 8;
    CHECK(A.get(0, 0) == 1);
    CHECK(A.get(0, 1) == 2);
    CHECK(A.get(1, 0) == 3);
    CHECK(A.get(1, 1) == 4);
}

// Test compound assignment operator %= (scalar modulo): ensures that each element is replaced by its modulo result.
TEST_CASE("Compound assignment operator %= (scalar modulo)") {
    SquareMat A(2);
    A.set(0, 0, 10); A.set(0, 1, 20);
    A.set(1, 0, 30); A.set(1, 1, 40);
    A %= 7;
    CHECK(A.get(0, 0) == 3);
    CHECK(A.get(0, 1) == 6);
    CHECK(A.get(1, 0) == 2);
    CHECK(A.get(1, 1) == 5);
}
// Test compound scalar multiplication operator (*= double): verifies that each element is multiplied by a scalar.

TEST_CASE("Compound scalar multiplication (*= double)") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    A *= 3;
    CHECK(A.get(0, 0) == 3);
    CHECK(A.get(0, 1) == 6);
    CHECK(A.get(1, 0) == 9);
    CHECK(A.get(1, 1) == 12);
}

// Test output stream operator <<: ensures matrix values are printed correctly as a string
TEST_CASE("Output stream operator << prints matrix") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    std::ostringstream oss;
    oss << A;
    std::string output = oss.str();
    CHECK(output.find("1") != std::string::npos);
    CHECK(output.find("4") != std::string::npos);
}

// Test equality and inequality operators: compares matrices based on total value sum or structure
TEST_CASE("Equality and inequality operators ==, !=") {
    SquareMat A(2), B(2), C(2);
    A.set(0,0,1); A.set(0,1,2); A.set(1,0,3); A.set(1,1,4); // sum = 10
    B.set(0,0,4); B.set(0,1,3); B.set(1,0,2); B.set(1,1,1); // sum = 10
    C.set(0,0,0); C.set(0,1,0); C.set(1,0,0); C.set(1,1,0); // sum = 0

    CHECK(A == B);
    CHECK_FALSE(A != B);
    CHECK(A != C);
    CHECK_FALSE(A == C);
}

// Test determinant operator (!): verifies calculation of 2x2 matrix determinant (ad - bc)
TEST_CASE("Determinant operator ! (2x2 matrix)") {
    SquareMat A(2);
    A.set(0,0,1); A.set(0,1,2);
    A.set(1,0,3); A.set(1,1,4);
    // det = (1*4 - 2*3) = -2
    double det = !A;
    CHECK(det == -2);
}

// Test [][] operator for read/write access: ensures correct access and mutation via double indexing
TEST_CASE("Element access with [][] operator (read and write)") {
    SquareMat A(2);
    A[0][1] = 42;
    CHECK(A[0][1] == 42);
    A[1][0] = -7;
    CHECK(A[1][0] == -7);
}


// Test transpose operator on asymmetric matrix: verifies rows become columns and vice versa

TEST_CASE("Transpose operator ~ with asymmetry") {
    SquareMat A(2);
    A.set(0,0,1); A.set(0,1,9);
    A.set(1,0,3); A.set(1,1,4);
    SquareMat B = ~A;
    CHECK(B.get(0,1) == 3);
    CHECK(B.get(1,0) == 9);
}

// Test exponentiation operator ^ with power 3: ensures repeated matrix multiplication is correct

TEST_CASE("Exponentiation to 3") {
    SquareMat A(2);
    A.set(0,0,2); A.set(0,1,1);
    A.set(1,0,1); A.set(1,1,2);
    SquareMat B = A ^ 3;
    CHECK(B.get(0,0) == 14);
    CHECK(B.get(1,1) == 14);
}

// Test comparison operators with equal sum: verifies logic when matrix values differ but sums are equal

TEST_CASE("Comparison operators with equal sum") {
    SquareMat A(2), B(2);
    A.set(0,0,5); A.set(0,1,0);
    A.set(1,0,0); A.set(1,1,5);
    B.set(0,0,2); B.set(0,1,3);
    B.set(1,0,4); B.set(1,1,1);
    CHECK(A == B);
    CHECK_FALSE(A < B);
    CHECK_FALSE(A > B);
}

// Test division operator / with non-integer result: ensures floating point division works correctly

TEST_CASE("Division by scalar produces non-integer values") {
    SquareMat A(2);
    A.set(0,0,5); A.set(0,1,10);
    A.set(1,0,15); A.set(1,1,20);
    SquareMat B = A / 2.0;
    CHECK(B.get(0,0) == doctest::Approx(2.5));
    CHECK(B.get(1,1) == doctest::Approx(10.0));
}
// Test modulo operator % with negative values: checks normalization of modulo result for negative numbers

TEST_CASE("Modulo by scalar with negative numbers") {
    SquareMat A(2);
    A.set(0,0,-5); A.set(0,1,-12);
    A.set(1,0,7); A.set(1,1,14);
    SquareMat B = A % 5;
    CHECK(B.get(0,0) == 0);    // ((-5 % 5) + 5) % 5 = 0
    CHECK(B.get(0,1) == 3);    // ((-12 % 5) + 5) % 5 = 3
    CHECK(B.get(1,0) == 2);
    CHECK(B.get(1,1) == 4);
}



// Test modulo operator % with decimal values: ensures precision handling in non-integer inputs

TEST_CASE("Matrix with decimal values and scalar modulo") {
    SquareMat A(2);
    A.set(0, 0, -4.9); A.set(0, 1, 3.7);
    A.set(1, 0, 12.3); A.set(1, 1, -9.6);
    SquareMat B = A % 5;
    CHECK(B.get(0, 0) == 1);
    CHECK(B.get(0, 1) == 3);
    CHECK(B.get(1, 0) == 2);
    CHECK(B.get(1, 1) == 1);

}

// Test scalar multiplication from left side: ensures that multiplication works symmetrically (double * matrix)

TEST_CASE("Scalar multiplication from the left (double * matrix)") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 2);
    A.set(1, 0, 3); A.set(1, 1, 4);
    SquareMat B = 2.0 * A;
    CHECK(B.get(0, 0) == 2);
    CHECK(B.get(0, 1) == 4);
    CHECK(B.get(1, 0) == 6);
    CHECK(B.get(1, 1) == 8);
}