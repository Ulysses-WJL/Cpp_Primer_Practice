//
// Created by w30065676 on 2025/9/30.
//

#ifndef BLOB_H
#define BLOB_H
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>


// Class Template

// forward declarations needed for friend declarations in Blob
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);
template <typename T>
bool operator!=(const Blob<T>&, const Blob<T>&);

template <typename T>
class Blob {
    // add ‘<>’ after the class/function name
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T> &, const Blob<T> &);
    friend bool operator!=<T>(const Blob<T> &, const Blob<T> &);
public:
    typedef T value_type;
    /*
     * std::vector<T>::size_type 是一个依赖类型（dependent type），它依赖于模板参数 T。在模板中，编译器在实例化之前无法知道
     * std::vector<T>::size_type 是一个类型还是一个静态成员。因此，我们必须使用 typename 来告诉编译器这是一个类型。
     */
    // typedef typename std::vector<T>::size_type size_type;
    using size_type = typename std::vector<T>::size_type;
    // constructors
    Blob();
    Blob(std::initializer_list<T>);
    // Member Templates of Class Templates
    template <typename IT>
    Blob(IT b, IT e);
    // number of elements in the Blob
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and remove elements
    void push_back(const T &t) {data->push_back(t);}
    // move version; see § 13.6.3 (p. 548)
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    // element access
    T& back();
    T& operator[](size_type i); // defined in § 14.5 (p. 566)

    const T& back() const;
    const T& operator[](size_type i) const;

private:
    std::shared_ptr<std::vector<T>> data;
    // throws msg if data[i] isn’t valid
    void check(size_type i, const std::string &msg) const;
};

/*
 * 模板类，它的定义（包括所有成员函数的定义）
 * 通常需要放在头文件中，因为模板的编译需要完整的定义信息。
 */

template<typename T>
bool operator==(const Blob<T> &lhs, const Blob<T> &rhs) {
    return lhs.data == rhs.data;
}

template<typename T>
bool operator!=(const Blob<T> &lhs, const Blob<T> &rhs) {
    return !(lhs == rhs);
}

// 在类外定义成员函数
// template <typename T>
// ret-type Blob<T>::member-name(parm-list)
template<typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {

}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) :  data(std::make_shared<std::vector<T>>(il)) {

}

template<typename T>
template<typename IT>
Blob<T>::Blob(IT b, IT e) : data(std::make_shared<std::vector<T>>(b, e)){
}

template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

template<typename T>
T &Blob<T>::back() {
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T &Blob<T>::operator[](size_type i) {
    check(i, "out of range");
    return (*data)[i];
    // return data->at(i);
}

template<typename T>
const T & Blob<T>::back() const {
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
const T & Blob<T>::operator[](size_type i) const {
    check(i, "out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back() {
    check(0, "pop on empty Blob");
    data->pop_back();
}


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

#endif //BLOB_H
