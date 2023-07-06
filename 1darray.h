#include "dtypes.h"
#include <stdexcept>
#include <memory>
#include <iterator>
#include <cstdint>

class OneDArray {
public:
    OneDArray(std::unique_ptr<unsigned char[]> data, DType dtype, size_t length, size_t stride = 1)
        : _data(std::move(data)), _dtype(dtype), _length(length), _stride(stride) {}
    OneDArray(const unsigned char* data, DType dtype, size_t length, size_t stride = 1)
        : _data(std::make_unique<unsigned char[]>(stride * dtype.size() * length)), _dtype(dtype), _length(length), _stride(stride) {
        std::copy(data, data + stride * dtype.size() * length, _data.get());
    }

    OneDArray(const OneDArray& other);
    OneDArray& operator=(const OneDArray& other);

    const DType dtype() { return _dtype; };
    const size_t length() { return _length; };
    const size_t stride() { return _stride; };

    void resize(size_t new_length);

    //Iterator
    template<typename T>
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;
        using reference         = T&;

        Iterator(OneDArray* array, size_t idx = 0) : m_array(array), m_idx(idx) {}

        reference operator*() const { return m_array->template getElement<T>(m_idx); }
        pointer operator->() { return &m_array->template getElement<T>(m_idx); }
        Iterator& operator++() { m_idx++; return *this; }
        Iterator operator++(int) { Iterator tmp = *this; m_idx++; return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_idx == b.m_idx; }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_idx != b.m_idx; }

    private:
        OneDArray* m_array;
        size_t m_idx;
    };

    template<typename T>
    class ConstIterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = const T*;
        using reference         = const T&;

        ConstIterator(const OneDArray* array, size_t idx = 0) : m_array(array), m_idx(idx) {}

        reference operator*() const { return m_array->template getElement<T>(m_idx); }
        pointer operator->() { return &m_array->template getElement<T>(m_idx); }
        ConstIterator& operator++() { m_idx++; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; m_idx++; return tmp; }
        friend bool operator== (const ConstIterator& a, const ConstIterator& b) { return a.m_idx == b.m_idx; }
        friend bool operator!= (const ConstIterator& a, const ConstIterator& b) { return a.m_idx != b.m_idx; }

    private:
        const OneDArray* m_array;
        size_t m_idx;
    };

    template<typename T> Iterator<T> begin() { return Iterator<T>(this, 0); }
    template<typename T> Iterator<T> end() { return Iterator<T>(this, _length); }

    template<typename T> ConstIterator<T> begin() const { return ConstIterator<T>(this, 0); }
    template<typename T> ConstIterator<T> end() const { return ConstIterator<T>(this, _length); }

    template<typename T>
    T& getElement(size_t idx) {
        // Non-const version
        return const_cast<T&>(const_cast<const OneDArray*>(this)->getElement<T>(idx));
    }

    template<typename T>
    const T& getElement(size_t idx) const {
        // Const version
        if (idx >= _length) {
            throw std::out_of_range("Index out of bounds.");
        }
        size_t byte_stride = _stride * _dtype.size();
        size_t start_idx = idx * byte_stride;
        return *reinterpret_cast<const T*>(_data.get() + start_idx);
    }

private:
    std::unique_ptr<unsigned char[]> _data;
    DType  _dtype;
    size_t _length;
    size_t _stride;
};
