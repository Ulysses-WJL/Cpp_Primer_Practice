#include "StrVec.h"

#include <algorithm>
#include <iostream>

void StrVec::push_back(const std::string &s) {
    chk_n_alloc();  // 先check是否有足够空间
    // 使用 allocator 构建
    alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    // 分配空间保存给定范围中的元素
    auto p_data = alloc.allocate(e - b);
    // 目标区域未初始化的情况，通过拷贝构造函数在目标位置构造对象。
    // 第一个指向分配的内存空间的起始， 第二个指向one element past the last constructed element
    return {p_data, std::uninitialized_copy(b, e, p_data)};
}

void StrVec::free() {
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
        // capture list 中添加 this， 允许lambda函数访问StrVec的member
        std::for_each(elements, first_free, [this](std::string &rhs){alloc.destroy(&rhs);});
        alloc.deallocate(elements, cap-elements);
    }
}

StrVec::StrVec(std::initializer_list<std::string> il) {
    auto new_data = alloc_n_copy(il.begin(), il.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

// copy constructor
StrVec::StrVec(const StrVec &s) {
    // 分配对应数量的内存 构造
    auto new_data = alloc_n_copy(s.begin(), s.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

// move constructor
StrVec::StrVec(StrVec &&s) noexcept: elements(s.elements), first_free(s.first_free), cap(s.cap) {
    // moved-from object will be destroyed
    s.elements = s.first_free = s.cap = nullptr;
}

// destructor
StrVec::~StrVec() {
    free();
}

// copy assignment
StrVec &StrVec::operator=(const StrVec &rhs) {
    // 调用alloc_n_copy分配空间以容纳与rhs中一样多的元素
    auto new_data = alloc_n_copy(rhs.begin(), rhs.end());
    // 先调用alloc_n_copy, 再free 以防 self-assignment
    free();
    elements = new_data.first;
    first_free = cap = new_data.second;
    return *this;
}

// move assignment
StrVec & StrVec::operator=(StrVec &&rhs) noexcept {
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

void StrVec::reallocate() {
    std::cout << "call reallocate" << std::endl;
    // 分配2倍的空间
    auto new_capacity = size() ? 2 * size() : 1;
    // 分配对应memory
    auto new_data = alloc.allocate(new_capacity);

    auto dest = new_data;  // points to the next free position in the new array
    auto elem = elements;  // points to the next element in the old array
    for (size_t i = 0; i != size(); ++i) {
        // 使用 move
        alloc.construct(dest++, std::move(*elem++));
    }
    free();  // 释放旧的
    elements = new_data;
    first_free = dest;  // dest 目前是one past the last constructed element
    cap = elements + new_capacity;
}
