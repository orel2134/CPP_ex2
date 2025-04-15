#include <iostream>
#include "SquareMat.hpp"

using namespace std;
using namespace MyMath;

void fillMatrix(SquareMat& mat, double base = 1) {
    int n = mat.getSize();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            mat.set(i, j, base + i * n + j);
}

void menu() {
    cout << "\nChoose an operator to apply:\n";
    cout << "1. Addition (A + B)\n";
    cout << "2. Subtraction (A - B)\n";
    cout << "3. Matrix Multiplication (A * B)\n";
    cout << "4. Scalar Multiplication (A * scalar)\n";
    cout << "5. Scalar Multiplication (scalar * A)\n";
    cout << "6. Element-wise Multiplication (A % B)\n";
    cout << "7. Modulo with scalar (A % scalar)\n";
    cout << "8. Division by scalar (A / scalar)\n";
    cout << "9. Unary Minus (-A)\n";
    cout << "10. Exponentiation (A ^ exponent)\n";
    cout << "11. Pre-Increment (++A)\n";
    cout << "12. Post-Increment (A++)\n";
    cout << "13. Pre-Decrement (--A)\n";
    cout << "14. Post-Decrement (A--)\n";
    cout << "15. Transpose (~A)\n";
    cout << "16. Determinant (!A)\n";
    cout << "17. A == B\n";
    cout << "18. A > B\n";
    cout << "19. Set A[0][1] = 99\n";
    cout << "0. Exit\n";
}

int main() {
    int n = 2;
    SquareMat A(n), B(n);
    fillMatrix(A, 1);
    fillMatrix(B, 10);

    int choice;
    do {
        menu();
        cout << "Enter your choice: ";
        cin >> choice;

        cout << "\nMatrix A:\n" << A;
        if (choice <= 3 || choice == 6)
            cout << "\nMatrix B:\n" << B;

        try {
            SquareMat result(n);
            switch (choice) {
                case 1: result = A + B; break;
                case 2: result = A - B; break;
                case 3: result = A * B; break;
                case 4: result = A * 2.0; break;
                case 5: result = 2.0 * A; break;
                case 6: result = A % B; break;
                case 7: result = A % 3; break;
                case 8: result = A / 2.0; break;
                case 9: result = -A; break;
                case 10: {
                    int exp;
                    cout << "Enter a non-negative exponent: ";
                    cin >> exp;
                    result = A ^ exp;
                    break;
                }
                case 11: ++A; result = A; break;
                case 12: result = A++; break;
                case 13: --A; result = A; break;
                case 14: result = A--; break;
                case 15: result = ~A; break;
                case 16: cout << "Determinant of A: " << !A << endl; continue;
                case 17: cout << (A == B ? "A == B" : "A != B") << endl; continue;
                case 18: cout << (A > B ? "A > B" : "A <= B") << endl; continue;
                case 19: A[0][1] = 99; result = A; break;
                case 0: cout << "Exiting...\n"; return 0;
                default: cout << "Invalid choice.\n"; continue;
            }

            cout << "\nResult:\n" << result;
        } catch (const exception& ex) {
            cout << "Error: " << ex.what() << endl;
        }

    } while (true);

    return 0;
}
