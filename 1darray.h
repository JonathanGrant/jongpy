#include "dtypes.h"
#include <stdexcept>
#include <memory>

class OneDArray {
public:
    OneDArray(std::unique_ptr<unsigned char[]> data, DType dtype, size_t length, size_t stride = 1)
        : _data(std::move(data)), _dtype(dtype), _length(length), _stride(stride) {}
    OneDArray(const unsigned char* data, DType dtype, size_t length, size_t stride = 1)
        : _data(std::make_unique<unsigned char[]>(stride * dtype.size() * length)), _dtype(dtype), _length(length), _stride(stride) {
        std::copy(data, data + stride * dtype.size() * length, _data.get());
    }

    OneDArray(const OneDArray& other); // TODO: Use SIMD and loop unrolling

    const DType dtype() { return _dtype; };
    const size_t length() { return _length; };
    const size_t stride() { return _stride; };

    template<typename T>
    T& operator[](size_t idx) const {
        return getElement<T>(idx);
    }
    template<typename T>
    const T& operator[](size_t idx) const {
        return getElement<T>(idx);
    }

    template<typename T>
    T& getElement(size_t idx) const {
        // Check for out of bounds
        if (idx >= _length) {
            throw std::invalid_argument("Index out of bounds.");
        }
        size_t byte_stride = _stride * _dtype.size();
        size_t start_idx = idx * byte_stride;
        return *reinterpret_cast<T*>(_data.get() + start_idx);
    }

private:
    std::unique_ptr<unsigned char[]> _data;
    DType  _dtype;
    size_t _length;
    size_t _stride;
};
