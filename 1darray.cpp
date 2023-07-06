#include "1darray.h"


OneDArray::OneDArray(const OneDArray& other) 
    : _dtype(other._dtype), _length(other._length), _stride(other._stride) {
    // Calculate total bytes
    size_t total_bytes = _stride * _dtype.size() * _length;

    // Allocate new array on the heap
    _data = std::make_unique<unsigned char[]>(total_bytes);

    // Copy data from the other object
    std::copy(other._data.get(), other._data.get() + total_bytes, _data.get());
}

OneDArray& OneDArray::operator=(const OneDArray& other) {
    if (this != &other) {
        _dtype = other._dtype;
        _length = other._length;
        _stride = other._stride;

        // Calculate total bytes
        size_t total_bytes = _stride * _dtype.size() * _length;

        // Allocate new array on the heap
        _data = std::make_unique<unsigned char[]>(total_bytes);

        // Copy data from the other object
        std::copy(other._data.get(), other._data.get() + total_bytes, _data.get());
    }
    return *this;
}

void OneDArray::resize(size_t new_length) {
    std::unique_ptr<unsigned char[]> new_data = std::make_unique<unsigned char[]>(_stride * _dtype.size() * new_length);
    std::copy(_data.get(), _data.get() + std::min(_length, new_length) * _stride * _dtype.size(), new_data.get());
    _data = std::move(new_data);
    _length = new_length;
}
