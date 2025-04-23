#include "SquareMat.hpp"
#include <stdexcept>
#include <iomanip>

namespace MyMath {

// Constructor
SquareMat::SquareMat(int n) : size(n) {
    if (n <= 0)
        throw std::invalid_argument("Size must be positive");
    data = new double[n * n];
    for (int i = 0; i < n * n; ++i)
        data[i] = 0;
}

// Destructor
SquareMat::~SquareMat() {
    delete[] data;
}

// Copy constructor
SquareMat::SquareMat(const SquareMat& other) {
    copyFrom(other);
}

// Assignment operator
SquareMat& SquareMat::operator=(const SquareMat& other) {
    if (this != &other) {
        delete[] data;
        copyFrom(other);
    }
    return *this;
}
// until here the rule of three

// Copy helper
void SquareMat::copyFrom(const SquareMat& other) {
    size = other.size;
    data = new double[size * size];
    for (int i = 0; i < size * size; ++i)
        data[i] = other.data[i];
}

// Compute sum of all elements
double SquareMat::sum() const {
    double total = 0;
    for (int i = 0; i < size * size; ++i)
        total += data[i];
    return total;
}

// Compute determinant for 2x2 matrix
double SquareMat::determinant2x2() const {
    if (size != 2)
        throw std::logic_error("Determinant only implemented for 2x2");
    return data[0]*data[3] - data[1]*data[2];
}

// Set value at (i,j)
void SquareMat::set(int i, int j, double value) {
    if (i < 0 || i >= size || j < 0 || j >= size)
        throw std::invalid_argument("Index out of bounds");
    data[i * size + j] = value;
}

// Get value at (i,j)
double SquareMat::get(int i, int j) const {
    if (i < 0 || i >= size || j < 0 || j >= size)
        throw std::invalid_argument("Index out of bounds");
    return data[i * size + j];
}

// Get matrix size
int SquareMat::getSize() const {
    return size;
}

// Indexing operator - non-const version
double* SquareMat::operator[](int i) {
    if (i < 0 || i >= size)
        throw std::invalid_argument("Row index out of bounds");
    return &data[i * size];
}

// Indexing operator - const version
const double* SquareMat::operator[](int i) const {
    if (i < 0 || i >= size)
        throw std::invalid_argument("Row index out of bounds");
    return &data[i * size];
}

// Transpose operator
SquareMat SquareMat::operator~() const {
    SquareMat trans(size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            trans.data[(j * size) + i] = data[(i * size) + j];
    return trans;
}

// Equality operator
bool SquareMat::operator==(const SquareMat& other) const {
    return size == other.size && sum() == other.sum();
}

// Inequality operator
bool SquareMat::operator!=(const SquareMat& other) const {
    return !(*this == other);
}

// Less-than comparison
bool SquareMat::operator<(const SquareMat& other) const {
    return sum() < other.sum();
}

// Greater-than comparison
bool SquareMat::operator>(const SquareMat& other) const {
    return sum() > other.sum();
}

// Less-than-or-equal comparison
bool SquareMat::operator<=(const SquareMat& other) const {
    return sum() <= other.sum();
}

// Greater-than-or-equal comparison
bool SquareMat::operator>=(const SquareMat& other) const {
    return sum() >= other.sum();
}

// Determinant operator (!)
double SquareMat::operator!() const {
    return determinant2x2();
}

// Unary minus
SquareMat SquareMat::operator-() const {
    SquareMat result(size);
    for (int i = 0; i < size * size; ++i)
        result.data[i] = -data[i];
    return result;
}

// Addition
SquareMat SquareMat::operator+(const SquareMat& other) const {
    if (size != other.size)
        throw std::invalid_argument("Matrix sizes must match for addition");
    SquareMat result(size);
    for (int i = 0; i < size * size; ++i)
        result.data[i] = data[i] + other.data[i];
    return result;
}

// Subtraction
SquareMat SquareMat::operator-(const SquareMat& other) const {
    if (size != other.size)
        throw std::invalid_argument("Matrix sizes must match for subtraction");
    SquareMat result(size);
    for (int i = 0; i < size * size; ++i)
        result.data[i] = data[i] - other.data[i];
    return result;
}

// Matrix multiplication
SquareMat SquareMat::operator*(const SquareMat& other) const {
    SquareMat result(size);//store the result squaremat
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            double sum = 0;
            for (int k = 0; k < size; ++k)
                sum += get(i, k) * other.get(k, j);
            result.set(i, j, sum);
        }
    return result;
}

// Scalar multiplication
SquareMat SquareMat::operator*(double scalar) const {
    SquareMat result(size);
    for (int i = 0; i < size * size; ++i)
        result.data[i] = data[i] * scalar;
    return result;
}

// Scalar multiplication (friend)
SquareMat operator*(double scalar, const SquareMat& mat) {
    return mat * scalar;
}

// Element-wise multiplication
SquareMat SquareMat::operator%(const SquareMat& other) const {
    SquareMat result(size);
    for (int i = 0; i < size * size; ++i)
        result.data[i] = data[i] * other.data[i];
    return result;
}

// Modulo with scalar
SquareMat SquareMat::operator%(int scalar) const {
    SquareMat result(size);
    for (int i = 0; i < size * size; ++i)
        result.data[i] = static_cast<int>(data[i]) % scalar;
    return result;
}

// Division by scalar
SquareMat SquareMat::operator/(double scalar) const {
    SquareMat result(size);
    for (int i = 0; i < size * size; ++i)
        result.data[i] = data[i] / scalar;
    return result;
}

// Matrix exponentiation
SquareMat SquareMat::operator^(int exponent) const {
    SquareMat result(size);
    for (int i = 0; i < size; ++i)
        result.set(i, i, 1);
    SquareMat base = *this;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = result * base;
        base = base * base;
        exponent /= 2;
    }
    return result;
}

// Compound addition
SquareMat& SquareMat::operator+=(const SquareMat& other) {
    *this = *this + other;
    return *this;
}

// Compound subtraction
SquareMat& SquareMat::operator-=(const SquareMat& other) {
    *this = *this - other;
    return *this;
}

// Compound matrix multiplication
SquareMat& SquareMat::operator*=(const SquareMat& other) {
    *this = *this * other;
    return *this;
}

// Compound scalar multiplication

SquareMat& SquareMat::operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
}

// Compound scalar division
SquareMat& SquareMat::operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
}

// Compound element-wise multiplication
SquareMat& SquareMat::operator%=(const SquareMat& other) {
    *this = *this % other;
    return *this;
}

// Compound modulo with scalar
SquareMat& SquareMat::operator%=(int scalar) {
    *this = *this % scalar;
    return *this;
}

// Pre-increment
SquareMat& SquareMat::operator++() {
    for (int i = 0; i < size * size; ++i)
        data[i] += 1;
    return *this;
}

// Post-increment
SquareMat SquareMat::operator++(int) {
    SquareMat temp = *this;
    ++(*this);
    return temp;
}

// Pre-decrement
SquareMat& SquareMat::operator--() {
    for (int i = 0; i < size * size; ++i)
        data[i] -= 1;
    return *this;
}

// Post-decrement
SquareMat SquareMat::operator--(int) {
    SquareMat temp = *this;
    --(*this);
    return temp;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const SquareMat& mat) {
    for (int i = 0; i < mat.size; ++i) {
        for (int j = 0; j < mat.size; ++j)
            os << std::setw(6) << mat.get(i, j) << " ";
        os << "\n";
    }
    return os;
}


} // namespace MyMath