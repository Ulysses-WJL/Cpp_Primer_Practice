//
// Created by w30065676 on 2025/10/13.
//

#ifndef VEC_H
#define VEC_H
#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
class Vec {

public:
    // 在类外部定义， 可以被多个类共享或在测试中独立使用
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vec<U>& v);
    Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(std::initializer_list<T>);
    Vec(const Vec &);
    // Move constructors and move assignment operators that cannot throw exceptions
    // should be marked as noexcept
    // 1. 避免异常处理开销:
    // 2. 使移动语义更有效 std::vector 和其他 STL 容器在实现时会优先使用移动构造函数。
    // 如果移动构造函数是 noexcept 的，容器在扩展或重新分配内存时会更倾向于使用移动而不是复制。
    //
    Vec(Vec &&) noexcept;
    Vec &operator=(const Vec &);
    Vec &operator=(Vec &&) noexcept;
    Vec &operator=(std::initializer_list<T>);
    const T& operator[](int) const;
    T& operator[](int);
    ~Vec();

    void push_back(const T &);
    void push_back(T &&);
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    T *begin() const {return elements;}
    T *end() const {return first_free;}
private:
    static std::allocator<T> alloc;  // 使用allocator 分配内存
    // allocate space and copy a given range of elements.
    std::pair<T*, T*> alloc_n_copy(const T * , const T *);
    // 当first_free == cap, 即没有足够的空间添加新元素时，重新allocate
    void chk_n_alloc() {if (size() == capacity()) reallocate();}
    // destroy the elements and free the space
    void free();
    // get more space and copy the existing elements
    void reallocate();
    T *elements;  // pointer to the first element in the array
    T *first_free;  // pointer to the first free element in the array
    T *cap;  // pointer to one past the end of the array
};

// 对于静态成员 Vec::alloc，需要在类定义之外提供其定义
template<typename T>
std::allocator<T> Vec<T>::alloc;

template<typename T>
std::ostream& operator<<(std::ostream&, const Vec<T>&);

template<typename T>
void Vec<T>::push_back(const T &s) {
    std::cout << "call copy version" << std::endl;
    chk_n_alloc();  // 先check是否有足够空间
    // 使用 allocator 构建
    alloc.construct(first_free++, s);
}

template<typename T>
void Vec<T>::push_back(T &&rhs) {
    std::cout << "call move version" << std::endl;
    chk_n_alloc();
    // move 返回rvalue reference，使用move constructor
    alloc.construct(first_free++, std::move(rhs));
}

template<typename T>
std::pair<T *, T *>
Vec<T>::alloc_n_copy(const T *b, const T *e) {
    // 分配空间保存给定范围中的元素
    auto p_data = alloc.allocate(e - b);
    // 目标区域未初始化的情况，通过拷贝构造函数在目标位置构造对象。
    // 第一个指向分配的内存空间的起始， 第二个指向one element past the last constructed element
    return {p_data, std::uninitialized_copy(b, e, p_data)};
}
template<typename T>
void Vec<T>::free() {
    // 销毁所有elements， 重新分配内存
    // if (elements) {
    //     for (auto p = first_free; p != elements; ) {
    //         // 倒序释放已constructed的元素 elements -> first_free -> cap
    //         alloc.destroy(--p);
    //     }
    //     alloc.deallocate(elements, cap-elements);
    // }
    // 13.43: for_each 版
    if (elements) {
        // capture list 中添加 this， 允许lambda函数访问Vec的member
        std::for_each(elements, first_free, [this](T &rhs){alloc.destroy(&rhs);});
        alloc.deallocate(elements, cap-elements);
    }
}

template<typename T>
Vec<T>::Vec(std::initializer_list<T> il) {
    auto new_data = alloc_n_copy(il.begin(), il.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

// copy constructor
template<typename T>
Vec<T>::Vec(const Vec &s) {
    // 分配对应数量的内存 构造
    auto new_data = alloc_n_copy(s.begin(), s.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
    std::cout << "copy constructor" << std::endl;
}

// move constructor
template<typename T>
Vec<T>::Vec(Vec &&s) noexcept: elements(s.elements), first_free(s.first_free), cap(s.cap) {
    // moved-from object will be destroyed
    s.elements = s.first_free = s.cap = nullptr;
    std::cout << "move constructor" << std::endl;
}

// destructor
template<typename T>
Vec<T>::~Vec() {
    free();
}

// copy assignment
template<typename T>
Vec<T> &Vec<T>::operator=(const Vec &rhs) {
    // 调用alloc_n_copy分配空间以容纳与rhs中一样多的元素
    std::cout << "copy assignment" << std::endl;
    auto new_data = alloc_n_copy(rhs.begin(), rhs.end());
    // 先调用alloc_n_copy, 再free 以防 self-assignment
    free();
    elements = new_data.first;
    first_free = cap = new_data.second;
    return *this;
}

// move assignment
template<typename T>
Vec<T> & Vec<T>::operator=(Vec &&rhs) noexcept {
    std::cout << "move assignment" << std::endl;
    if (this != &rhs) {
        // free existing elements
        free();
        // take over resources from rhs
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        // leave rhs in a destructible state
        // rhs 的状态和default-initialized 相同
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

template<typename T>
Vec<T> & Vec<T>::operator=(std::initializer_list<T> il) {
    std::cout << "initializer list assignment" << std::endl;
    auto new_data = alloc_n_copy(il.begin(), il.end());
    free();
    elements = new_data.first;
    first_free = cap = new_data.second;
    return *this;
}

template<typename T>
const T & Vec<T>::operator[](int i) const {
    return elements[i];
}

template<typename T>
T & Vec<T>::operator[](int i) {
    return *(elements + i);
}

// void Vec::reallocate() {
//     std::cout << "call reallocate" << std::endl;
//     // 分配2倍的空间
//     auto new_capacity = size() ? 2 * size() : 1;
//     // 分配对应memory
//     auto new_data = alloc.allocate(new_capacity);
//
//     auto dest = new_data;  // points to the next free position in the new array
//     auto elem = elements;  // points to the next element in the old array
//     for (size_t i = 0; i != size(); ++i) {
//         // 使用 move
//         alloc.construct(dest++, std::move(*elem++));
//     }
//     free();  // 释放旧的
//     elements = new_data;
//     first_free = dest;  // dest 目前是one past the last constructed element
//     cap = elements + new_capacity;
// }

template<typename T>
void Vec<T>::reallocate() {
    std::cout << "call reallocate" << std::endl;
    // 分配2倍的空间
    auto new_capacity = size() ? 2 * size() : 1;
    // 分配对应memory
    auto first = alloc.allocate(new_capacity);

    // 使用 move
    auto last = std::uninitialized_copy( // rvalue reference传进来就使用move constructor
        std::make_move_iterator(begin()),  // move iterator adaptor,
        std::make_move_iterator(end()), // iterator 的derefernce 操作返回的是rvalue reference
        first);
    free();  // 释放旧的
    elements = first;
    first_free = last;  // dest 目前是one past the last constructed element
    cap = elements + new_capacity;
}

template<typename T>
std::ostream & operator<<(std::ostream &os, const Vec<T> &sv) {
    for (auto &s: sv) {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    return os;
}
#endif //VEC_H
