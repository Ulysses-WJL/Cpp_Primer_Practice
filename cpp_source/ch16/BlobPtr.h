//
// Created by w30065676 on 2025/9/30.
//

#ifndef BLOBPTR_H
#define BLOBPTR_H
#include "Blob.h"

template <typename T>
class BlobPtr {
public:
    BlobPtr(): curr(0) { }
    BlobPtr(Blob<T> &a, size_t sz = 0):wptr(a.data), curr(sz) { }
    T& operator*() const
    { auto p = check(curr, "dereference past end");
        return (*p)[curr]; // (*p) is the vector to which this object points
    }
    // increment and decrement
    // 在class scope内 模板不需要参数
    BlobPtr& operator++(); // prefix operators
    BlobPtr& operator--();
    BlobPtr operator++(int);  // postfix 返回未执行操作的对象
    BlobPtr operator--(int);
private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr; // current position within the array
};

template<typename T>
BlobPtr<T> &BlobPtr<T>::operator++() {
    check(curr, "out of range");
    ++curr;
    return *this;
}

template<typename T>
BlobPtr<T> & BlobPtr<T>::operator--() {
    --curr;
    // if curr is zero, decrementing it will yield an invalid subscript
    check(curr, "index小于起始");
    return *this;
}

template<typename T>
BlobPtr<T>  BlobPtr<T>::operator++(int) {
    BlobPtr ret = *this;
    ++*this;
    return ret;
}

template<typename T>
BlobPtr<T>  BlobPtr<T>::operator--(int) {
    BlobPtr ret = *this;
    --*this;
    return ret;
}

template<typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret) {
        throw std::runtime_error("Unbound StrBlobPtr");
    }
    if (i >= ret->size()) {
        // StrBlob 没有这么多元素
        throw std::out_of_range(msg);
    }
    return ret;
}



#endif //BLOBPTR_H
