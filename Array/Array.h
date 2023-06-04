#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

/**
 * Proxy struct that represents array.
 * We encapsulate array itself because
 * Size can be 0.
 * @tparam Type data type
 * @tparam Size array size
 */
template<class Type, size_t Size>
struct ArrayProxy {
    using Elements = Type[Size];
};

// Zero-length array specialization with
// no Elements field. So that zero-length Array
// cannot be created.
// We should not have ability to access
// elements in an empty array.
template<class Type>
struct ArrayProxy<Type, 0> {
    [[noreturn]]
    inline constexpr Type &operator[](size_t) const {
        throw std::length_error("Cannot access zero-length array");
    }

    inline constexpr explicit operator Type *() const noexcept {
        return nullptr;
    }
};

/**
 * Container with type T and fixed size N.
 * In general, same to std::array.
 * @tparam T data type
 * @tparam N array length
 */
template<class T, size_t N>
struct Array {
    using value_type = T;

    using reference = value_type &;
    using const_reference = const value_type &;

    using pointer = value_type *;
    using const_pointer = const value_type *;

    using iterator = value_type *;
    using const_iterator = const value_type *;

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    pointer data() noexcept {
        return array_;
    }

    const_pointer data() const noexcept {
        return array_;
    }

    constexpr iterator begin() const noexcept {
        return iterator(data());
    }

    constexpr const_iterator cbegin() const noexcept {
        return const_iterator(data());
    }

    constexpr iterator end() const noexcept {
        return iterator(data() + N);
    }

    constexpr const_iterator cend() const noexcept {
        return const_iterator(data() + N);
    }

    constexpr reverse_iterator rbegin() const noexcept {
        return reverse_iterator(end());
    }

    constexpr const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(end());
    }

    constexpr reverse_iterator rend() const noexcept {
        return reverse_iterator(begin());
    }

    constexpr const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(begin());
    }

    void fill(const value_type &v) noexcept {
        std::fill_n(begin(), N, v);
    }

    [[nodiscard]]
    constexpr size_type size() const noexcept {
        return N;
    }

    [[nodiscard]]
    constexpr bool empty() const noexcept {
        return size() == 0;
    }

    constexpr reference operator[](size_type i) noexcept {
        return array_[i];
    }

    constexpr const_reference operator[](size_type i) const noexcept {
        return array_[i];
    }

    constexpr reference at(size_type i) {
        return i >= N ? throw std::out_of_range("Out of range access") : array_[i];
    }

    constexpr const_reference at(size_type i) const {
        return i >= N ? throw std::out_of_range("Out of range access") : array_[i];
    }

    constexpr reference front() noexcept {
        return array_[0];
    }

    constexpr const_reference front() const noexcept {
        return array_[0];
    }

    constexpr reference back() noexcept {
        return array_[N - 1];
    }

    constexpr const_reference back() const noexcept {
        return array_[N - 1];
    }

    constexpr bool operator==(const Array &other) const noexcept {
        return std::equal(cbegin(), cend(), other.cbegin());
    }

private:
    // We use Elements field from ArrayProxy.
    // If N = 0 array couldn't be created
    // because Elements field is not specified
    // in ArrayProxy.
    ArrayProxy<T, N>::Elements array_;
};


#endif //ARRAY_ARRAY_H
