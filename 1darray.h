#include "dtypes.h"
#include <stdexcept>

class OneDArray {
public:
    OneDArray(unsigned char* data, DType dtype, size_t length, size_t stride = 1)
        : _data(data), _dtype(dtype), _length(length), _stride(stride) {}
    const size_t length() { return _length; };

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
        return *reinterpret_cast<T*>(_data + start_idx);
    }

private:
    unsigned char* _data;
    DType  _dtype;
    size_t _length;
    size_t _stride;
};
