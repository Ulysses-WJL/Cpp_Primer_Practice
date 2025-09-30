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
template <typename T>
class Blob {
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
private:
    std::shared_ptr<std::vector<T>> data;
    // throws msg if data[i] isn’t valid
    void check(size_type i, const std::string &msg) const;
};

/*
 * 模板类，它的定义（包括所有成员函数的定义）
 * 通常需要放在头文件中，因为模板的编译需要完整的定义信息。
 */

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
void Blob<T>::pop_back() {
    check(0, "pop on empty Blob");
    data->pop_back();
}
#endif //BLOB_H
