//
// Created by bruce on 2025/10/26.
//

#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

#include "delete.hpp"

template <typename, typename>
class unique_pointer;
template <typename T, typename D>
void swap(unique_pointer<T, D>&, unique_pointer<T, D>&);

template <typename T, typename D = wjl::Delete>
class unique_pointer {
    friend void swap<T, D>(unique_pointer<T, D>&, unique_pointer<T, D>&);
public:
    // 不支持copy 和 assignment
    unique_pointer(const unique_pointer&) = delete;
    unique_pointer& operator=(const unique_pointer&) = delete;

    unique_pointer() = default;

    explicit unique_pointer(T *pointer): ptr(pointer) {}

    // move ctor
    unique_pointer(unique_pointer &&rhs) noexcept: ptr(rhs.ptr) {rhs.ptr = nullptr;};

    // move assignment
    unique_pointer& operator=(unique_pointer &&rhs) noexcept;

    // nullptr assignment
    unique_pointer& operator=(std::nullptr_t n) noexcept;

    // *, -> bool
    T& operator*() const {return *ptr;};
    T* operator->() const {return & this->operator*();};
    operator bool() const { return ptr != nullptr; };

    // get , reset , release, swap
    T* get() const { return ptr; };
    void swap(unique_pointer &other) {::swap(*this, other);};
    void reset() noexcept {deleter(ptr); ptr = nullptr;};
    void reset(T *pointer) {deleter(ptr); ptr = pointer;};

    T * release();

    ~unique_pointer() {deleter(ptr);};

private:
    T *ptr = nullptr;
    D deleter = D();
};

template <typename T, typename D>
void swap(unique_pointer<T, D>&lhs, unique_pointer<T, D>&rhs) {
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}

template<typename T, typename D>
unique_pointer<T, D> & unique_pointer<T, D>::operator=(unique_pointer &&rhs) noexcept {
    if (this->ptr != rhs.ptr) {
        deleter(ptr);
        ptr = nullptr;
        ::swap(*this, rhs);
    }
    return *this;
}

template<typename T, typename D>
unique_pointer<T, D> & unique_pointer<T, D>::operator=(std::nullptr_t n) noexcept {
    if (n == nullptr) {
        deleter(ptr);
        ptr = nullptr;
    }
    return *this;
}

// 放弃对指针的控制权，返回指针，并将u置空。
template<typename T, typename D>
T * unique_pointer<T, D>::release() {
    T *ret = ptr;
    ptr = nullptr;
    return ret;
}


#endif //UNIQUE_POINTER_H
