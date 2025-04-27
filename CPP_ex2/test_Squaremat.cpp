השיחה נפתחה. הודעה אחת נקראה.

דילוג לתוכן
שימוש ב-Gmail עם קוראי מסך
1 מתוך 4,800
cpp_ex2‏
דואר נכנס

אוראל <orel2744@gmail.com‏>
קבצים מצורפים
1:18 (לפני 49 דקות)
אני


 4 קבצים מצורפים
  •  נסרקו על ידי Gmail
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"
#include <sstream>
using namespace MyMath;

/////////////////////////// טסטים שלך ///////////////////////////

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

/////////////////////////// טסטים מתקדמים שהוספתי ///////////////////////////

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

TEST_CASE("Multiple addition assignment") {
    SquareMat A(2);
    A.set(0, 0, 1); A.set(0, 1, 1);
    A.set(1, 0, 1); A.set(1, 1, 1);

    A += A;
    A += A;
    CHECK(A.get(0, 0) == 4);
}

TEST_CASE("Division by very small number") {
    SquareMat A(2);
    A.set(0, 0, 1e-10); A.set(0, 1, 1e-10);
    A.set(1, 0, 1e-10); A.set(1, 1, 1e-10);

    SquareMat result = A / 1e-5;
    CHECK(result.get(0, 0) == doctest::Approx(1e-5));
}

TEST_CASE("Indexing operator [] - out of bounds access") {
    SquareMat A(2);
    CHECK_THROWS_AS(A[-1][0] = 5, std::invalid_argument);
    CHECK_THROWS_AS(A[2][1] = 5, std::invalid_argument);
}

/////////////////////////// בדיקות חריגה מיוחדות ///////////////////////////

TEST_CASE("Set and get with invalid indices") {
    SquareMat A(2);
    CHECK_THROWS_AS(A.set(-1, 0, 5), std::invalid_argument);
    CHECK_THROWS_AS(A.get(2, 1), std::invalid_argument);
}

TEST_CASE("Constructor with size 0 or negative") {
    CHECK_THROWS_AS(SquareMat(0), std::invalid_argument);
    CHECK_THROWS_AS(SquareMat(-5), std::invalid_argument);
}

TEST_CASE("Determinant on non-2x2 matrix") {
    SquareMat A(3);
    CHECK_THROWS_AS(!A, std::logic_error);
}


/////////////////////////// טסטים לפונקציות החסרות ///////////////////////////
//////////////////////////////////////////////////////////////////////////////


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

//////////////////////////////////////////////////////////////////////////////
/////////////////////////// טסטים לפעולות השמה מורכבות //////////////////////
//////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////
