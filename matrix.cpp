#include <vector>
#include <stdexcept>
#include "matrix.h"

Matrix& Matrix::add(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Dimensions mismatch");
    }

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            (*this)(i, j) += other(i, j);
        }
    }

    return *this;
}

Matrix& Matrix::log() {
    for (float& x : data_) {
        x = std::log(x);
    }
    return *this;
}
