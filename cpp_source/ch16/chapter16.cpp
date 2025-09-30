//
// Created by w30065676 on 2025/9/29.
//
#include <array>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <memory>
#include "../ch08/Sales_Data.h"
#include "Blob.h"

using std::cout;
using std::cin;
using std::endl;


// Templates are the foundation for generic programming in C++

//Function Templates
template <typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    // if (std::less<T>(v1, v2)) return -1;
    // if (std::less<T>(v2, v1)) return 1;
    return 0;
}

template <typename T>
T foo(T* p) {
    T tmp = *p;
    return tmp;
}


/*Nontype Template Parameters 非类型模板参数
 * 在模板中使用常量值const expressions作为参数，这些参数在实例化模板时指定, 在编译时需要被确定。
 * 非类型模板参数可以是整数类型、枚举类型、指针类型或引用类型，但不能是浮点类型。
 */
template <typename T, int Size>
class Array {
    T data[Size];
public:
    T& operator[](int index) { return data[index]; }
    int size() const { return Size; }
};

template<unsigned N, unsigned M>
int compare(const char (&p1)[N], const char (&p2)[M]) {
    return strcmp(p1, p2);
}

void test_nonetype_template_parameters() {
    Array<int, 10> intArry;
    intArry[2] = 10;
    cout << compare("hello", "hi") << endl;
}

// 定义时code没有生成，使用模板时才生成
// 函数模板和类模板成员函数的定义通常放在头文件中。


// void q_16_3() {
//     Sales_Data s1("a", 12, 2.5);
//     Sales_Data s2{"b", 10, 22.5};
//     // build 时， error: no matching function for call to 'std::less<double>::less(const double&, const double&)'
//     // error: no match for 'operator<'
//     compare(s1, s2);
// }

template <typename Iterator, typename Value>
Iterator my_find(Iterator first, Iterator last, Value value) {
    for (;first != last && *first != value; ++first);
    return first;
}

void q_16_4() {
    std::vector<int> ivec{1, 2, 3, 4, 5, 6};
    std::list<std::string> slist{"a", "b", "foo", "bar"};
    auto iter = my_find(ivec.cbegin(), ivec.cend(), 5);
    if (iter != ivec.cend())
        cout << "find:" << *iter << endl;
    else
        cout << "not find" << endl;

    auto iter2 = my_find(slist.cbegin(), slist.cend(), "fcc");
    if (iter2 != slist.cend())
        cout << "find:" << *iter2<< endl;
    else
        cout << "not find" << endl;

}

template <typename Array>
void print(const Array& arr) {
    for (auto const &item : arr) {
        cout << item << " ";
    }
    cout << endl;
}

void q_16_5() {
    const int ivec[10] = {1, 2, 3, 4, 5, 6};
    const std::string s[5] = {"a", "b", "foo", "bar"};
    print(ivec);
    print(s);
}

template <typename Array, size_t N>
Array* my_begin(Array (&arr)[N]) {
    return arr;
}

template <typename Array, size_t N>
Array* my_end(Array (&arr)[N]) {
    return arr+N;
}


void q_16_6() {
    const int ivec[] = {1, 2, 3, 4, 5, 6};
    const std::string s[5] = {"a", "b", "foo", "bar"};
    cout << "begin: " << *std::begin(ivec) << endl;
    cout << "end: " << *(std::end(ivec) - 1) << endl;

    cout << "begin: " << *my_begin(ivec) << endl;
    cout << "end: " << *(my_end(ivec) - 1) << endl;

}

template <typename Array, size_t N>
constexpr size_t get_size(const Array (&arr)[N]) {
    return N;
}

void q_16_7() {
    int ivec[10] = {1, 2, 3, 4, 5, 6};
    cout << "array size: " << get_size(ivec) << endl;
}

// Instantiating a Class Template
void test_class_template() {
    Blob<int> ia;
    Blob<int> ia2 = {0, 1, 2, 3, 4};
    Blob<std::string> names = {"a", "b", "foo", "bar"};
}

int main(int argc, char **argv) {
    test_class_template();
    q_16_7();
    q_16_6();
    q_16_5();
    q_16_4();
    // q_16_3();
    test_nonetype_template_parameters();
    cout << compare(0.6, 0.5) << endl;
    cout << compare(10, 41) << endl;
    cout << compare(0, 0) << endl;
    int x = 124;
    int *p = &x;
    cout << foo(p) << endl;
    return 0;
}
