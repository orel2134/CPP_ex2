#ifndef SQUAREMAT_HPP
#define SQUAREMAT_HPP

#include <iostream>

namespace MyMath {

class SquareMat {
private:
    int size;
    double* data;
    void copyFrom(const SquareMat& other);
    double sum() const;
    double determinant2x2() const;

public:
    SquareMat(int n);
    ~SquareMat();
    SquareMat(const SquareMat& other);
    SquareMat& operator=(const SquareMat& other);

    void set(int i, int j, double value);
    double get(int i, int j) const;
    int getSize() const;

    double* operator[](int i);
    const double* operator[](int i) const;

    SquareMat operator~() const;

    bool operator==(const SquareMat& other) const;
    bool operator!=(const SquareMat& other) const;
    bool operator<(const SquareMat& other) const;
    bool operator>(const SquareMat& other) const;
    bool operator<=(const SquareMat& other) const;
    bool operator>=(const SquareMat& other) const;

    double operator!() const;

    SquareMat operator-() const;
    SquareMat operator+(const SquareMat& other) const;
    SquareMat operator-(const SquareMat& other) const;
    SquareMat operator*(const SquareMat& other) const;
    SquareMat operator*(double scalar) const;
    SquareMat operator%(const SquareMat& other) const;
    SquareMat operator%(int scalar) const;
    SquareMat operator/(double scalar) const;
    SquareMat operator^(int exponent) const;

    SquareMat& operator+=(const SquareMat& other);
    SquareMat& operator-=(const SquareMat& other);
    SquareMat& operator*=(const SquareMat& other);
    SquareMat& operator*=(double scalar);
    SquareMat& operator/=(double scalar);
    SquareMat& operator%=(const SquareMat& other);
    SquareMat& operator%=(int scalar);

    SquareMat& operator++();      // Pre-increment
    SquareMat operator++(int);    // Post-increment
    SquareMat& operator--();      // Pre-decrement
    SquareMat operator--(int);    // Post-decrement

    friend SquareMat operator*(double scalar, const SquareMat& mat);
    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);
};

} // namespace MyMath

#endif // SQUAREMAT_HPP
