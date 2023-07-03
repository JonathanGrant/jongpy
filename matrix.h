#include <vector>
#include <stdexcept>

class Matrix {
public:
    Matrix(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), strides_{cols, 1}, data_(rows * cols) {}

    float& operator()(size_t i, size_t j) {
        return data_[i * strides_[0] + j * strides_[1]];
    }

    float operator()(size_t i, size_t j) const {
        return data_[i * strides_[0] + j * strides_[1]];
    }

    size_t rows() const { return rows_; }
    size_t cols() const { return cols_; }

    Matrix& add(const Matrix& other);
    Matrix& log();

private:
    size_t rows_, cols_;
    std::vector<size_t> strides_;
    std::vector<float> data_;
};