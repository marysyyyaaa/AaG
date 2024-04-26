#include <iostream>
#include "Matrix.hpp"
#include "Fp.hpp"
#include "HamingCode.hpp"

int main() {

    // Если нигде не вылетело ошибки, значит всё работает по кайфу)

    // Test 1: Test matrix assignment operator
    Matrix<Fp<2>> mat1(2, 2);
    Matrix<Fp<2>> mat2(2, 2);
    mat1 = mat2;
    std::cout << "Test 1 Done" << std::endl;

    // Test 2: Test accessing matrix element
    Matrix<Fp<2>> mat3(2, 2);
    Fp<2> element = mat3(1, 1);
    std::cout << "Test 2 Done" << std::endl;

    // Test 3: Test getting number of rows and columns
    Matrix<Fp<2>> mat4(3, 4);
    size_t rows = mat4.get_rows();
    size_t cols = mat4.get_cols();
    std::cout << "Test 3 Done" << std::endl;

    // Test 4: Test matrix comparison
    Matrix<Fp<2>> mat5(2, 2);
    Matrix<Fp<2>> mat6(2, 2);
    bool equal = (mat5 == mat6);
    std::cout << "Test 4 Done" << std::endl;

    // Test 5: Test matrix multiplication with scalar
    Matrix<Fp<2>> mat7(2, 2);
    Fp<2> scalar(3);
    Matrix<Fp<2>> result = mat7 * scalar;
    std::cout << "Test 5 Done" << std::endl;

    // Test 6: Test matrix addition
    Matrix<Fp<2>> mat8(2, 2);
    Matrix<Fp<2>> mat9(2, 2);
    Matrix<Fp<2>> sum = mat8 + mat9;
    std::cout << "Test 6 Done" << std::endl;

    // Test 7: Test matrix subtraction
    Matrix<Fp<2>> mat10(2, 2);
    Matrix<Fp<2>> mat11(2, 2);
    Matrix<Fp<2>> diff = mat10 - mat11;
    std::cout << "Test 7 Done" << std::endl;

    // Test 8: Test matrix negation
    Matrix<Fp<2>> mat12(2, 2);
    Matrix<Fp<2>> negated = -mat12;
    std::cout << "Test 8 Done" << std::endl;

    // Test 9: Test matrix multiplication
    Matrix<Fp<2>> mat13(2, 3);
    Matrix<Fp<2>> mat14(3, 2);
    Matrix<Fp<2>> product = mat13 * mat14;
    std::cout << "Test 9 Done" << std::endl;

    // Test 10: Test matrix transpose
    Matrix<Fp<2>> mat15(3, 2);
    Matrix<Fp<2>> transposed = mat15.transpose();
    std::cout << "Test 10 Done" << std::endl;

    // Test 11: Test matrix sum in Matrix class
    Matrix<Fp<2>> mat16(2, 2);
    Matrix<Fp<2>> mat17(2, 2);
    Matrix<Fp<2>> result1 = mat16 + mat17;
    std::cout << "Test 11 Done" << std::endl;

    // Test 12: Test matrix multiplication in Matrix class
    Matrix<Fp<2>> mat18(2, 3);
    Matrix<Fp<2>> mat19(3, 2);
    Matrix<Fp<2>> result2 = mat18 * mat19;
    std::cout << "Test 12 Done" << std::endl;

    // Test 13: Test matrix transpose in Matrix class
    Matrix<Fp<2>> mat20(2, 3);
    Matrix<Fp<2>> transposed1 = mat20.transpose();
    std::cout << "Test 13 Done" << std::endl;

    // Test 14: Test matrix multiplication with scalar in Matrix class
    Matrix<Fp<2>> mat21(2, 2);
    Fp<2> scalar1(3);
    Matrix<Fp<2>> result3 = mat21 * scalar1;
    std::cout << "Test 14 Done" << std::endl;

    // Test 15: Test HammingCode object creation with m = 1
    HammingCode<2> hammingCode1(1);
    std::cout << "Test 15 Done" << std::endl;

    // Test 16: Test HammingCode object creation with m = 2
    HammingCode<2> hammingCode2(2);
    std::cout << "Test 16 Done" << std::endl;

}
