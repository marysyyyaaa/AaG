#pragma once
#include "Matrix.hpp"
#include "Fp.hpp"

template<int p>
class HammingCode {
public:
    HammingCode(size_t m) : m(m) {
        generate_matrices();
    }

private:
    size_t n;    // Количество символов в кодовом слове
    size_t k;    // Количество информационных символов
    size_t m;    // Количество проверочных символов
    Matrix<Fp<p>> H; // Проверочная матрица
    Matrix<Fp<p>> G; // Порождающая матрица

    void generate_matrices() {
        // Генерация порождающей матрицы G
        size_t r = m;
        n = pow(2, r) - 1;
        k = n - r;

        G = Matrix<Fp<p>>(k, n);
        for (size_t i = 0; i < k; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (j < k) {
                    G(i, j) = Fp<p>((1 << (k - 1 - j)) & i);
                }
                else {
                    G(i, j) = Fp<p>((1 << (n - 1 - j)) & i);
                }
            }
        }

        // Генерация проверочной матрицы H
        H = Matrix<Fp<p>>(r, n);
        for (size_t i = 0; i < r; ++i) {
            for (size_t j = 0; j < n; ++j) {
                H(i, j) = Fp<p>((1 << (r - 1 - i)) & (j + 1) ? 1 : 0);
            }
        }
    }
};