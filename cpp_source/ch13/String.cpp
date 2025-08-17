#include <iostream>
#include "String.h"

#include <algorithm>

std::pair<char *, char *> String::alloc_n_copy(const char *b, const char *e) {
    auto p = alloc.allocate(e - b);
    return {p, std::uninitialized_copy(b, e, p)};
}

void String::range_initializer(const char *b, const char *e) {
    auto new_data = alloc_n_copy(b, e);
    elements = new_data.first;
    end = new_data.second;
}


String::String(const char *s) {
    char *s1 = const_cast<char *>(s);
    while (*s1)
        ++s1;
    // s1 指向 null terminator
    range_initializer(s, ++s1);  // s1指向null terminator后一个
    std::cout << "const char * constructor" << std::endl;
}

String::String(const String &rhs) {
    range_initializer(rhs.elements, rhs.end);
    std::cout << "copy constructor" << std::endl;
}

// q_13_49
// move construct
// lhs的成员都用move 改为rhs的； rhs的成员再清除
String::String(String &&rhs) noexcept : elements(rhs.elements), end(rhs.end) {
    std::cout << "move constructor" << std::endl;
    rhs.elements = rhs.end = nullptr;
}

String & String::operator=(String &&rhs) noexcept {
    std::cout << "move assignment" << std::endl;
    if (this != &rhs) {
        free();
        elements = rhs.elements;
        end = rhs.end;
        rhs.elements = rhs.end = nullptr;
    }
    return *this;
}

void String::free() {
    if (elements) {
        std::for_each(elements, end, [this](char &c){alloc.destroy(&c);});
        alloc.deallocate(elements, end - elements);
    }
}

String::~String() {
    free();
}

String &String::operator=(const String &rhs) {
    auto new_data = alloc_n_copy(rhs.elements, rhs.end);
    free();
    elements = new_data.first;
    end = new_data.second;
    std::cout << "copy-assignment" << std::endl;
    return *this;
}

