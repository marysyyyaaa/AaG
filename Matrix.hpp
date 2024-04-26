#pragma once

#include <iostream>
#include <iomanip>
#include <vector>

template<typename T>
class Matrix {
public:
    Matrix() : rows(0), cols(0) {}

    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(std::vector<std::vector<T>>(rows, std::vector<T>(cols))) {}

    Matrix(const std::vector<std::vector<T>>& v) : data(v) {
        rows = v.size();
        if (rows > 0) {
            cols = v[0].size();
            for (size_t i = 1; i < rows; ++i) {
                if (v[i].size() != cols) {
                    throw std::invalid_argument("All rows must have the same number of columns");
                }
            }
        }
        else {
            cols = 0;
        }
    }

    Matrix(const Matrix<T>& other) : rows(other.rows), cols(other.cols), data(other.data) {}

    Matrix<T>& operator=(const Matrix<T>& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
        }
        return *this;
    }

    T& operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[i][j];
    }

    const T& operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[i][j];
    }

    size_t get_rows() const {
        return rows;
    }

    size_t get_cols() const {
        return cols;
    }

    bool operator==(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            return false;
        }
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] != other.data[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix<T>& other) const {
        return !(*this == other);
    }

    Matrix<T> operator*(const T& x) const {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] * x;
            }
        }
        return result;
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
        }
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator-() const {
        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = -data[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Number of columns in the first matrix must be equal to the number of rows in the second matrix for matrix multiplication");
        }
        Matrix<T> result(rows, other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                for (size_t k = 0; k < cols; ++k) {
                    result(i, j) += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix<T> transpose() const {
        Matrix<T> result(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(j, i) = data[i][j];
            }
        }
        return result;
    }

    Matrix<T> submatrix(size_t row, size_t col, size_t subRows, size_t subCols) const {
        if (row + subRows > rows || col + subCols > cols) {
            throw std::out_of_range("Submatrix dimensions exceed the original matrix dimensions");
        }
        Matrix<T> result(subRows, subCols);
        for (size_t i = 0; i < subRows; ++i) {
            for (size_t j = 0; j < subCols; ++j) {
                result(i, j) = data[row + i][col + j];
            }
        }
        return result;
    }

    static Matrix<T> eye(size_t n) {
        Matrix<T> result(n, n);
        for (size_t i = 0; i < n; ++i) {
            result(i, i) = static_cast<T>(1);
        }
        return result;
    }

    static Matrix<T> zeros(size_t rows, size_t cols) {
        return Matrix<T>(rows, cols);
    }

    Matrix<T> horizontal_concatenate(const Matrix<T>& other) const {
        if (rows != other.rows) {
            throw std::invalid_argument("Matrices must have the same number of rows for horizontal concatenation");
        }
        Matrix<T> result(rows, cols + other.cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j];
            }
            for (size_t j = 0; j < other.cols; ++j) {
                result(i, cols + j) = other.data[i][j];
            }
        }
        return result;
    }

    Matrix<T> vertical_concatenate(const Matrix<T>& other) const {
        if (cols != other.cols) {
            throw std::invalid_argument("Matrices must have the same number of columns for vertical concatenation");
        }
        Matrix<T> result(rows + other.rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(i, j) = data[i][j];
            }
        }
        for (size_t i = 0; i < other.rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result(rows + i, j) = other.data[i][j];
            }
        }
        return result;
    }

    // «Красивый» вывод матрицы
    template <typename Tstream>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<Tstream>& m);

private:
    size_t rows;                      // количество строк
    size_t cols;                      // количество столбцов
    std::vector<std::vector<T>> data; // данные матрицы
};

template <typename Tstream>
std::ostream& operator<<(std::ostream& out, const Matrix<Tstream>& m) {
    const int MAX_NUM_DIGITS = 5;
    out << std::endl;
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            out << std::setw(MAX_NUM_DIGITS) << m(i, j) << " ";
        }
        out << std::endl;
    }
    return out;
}