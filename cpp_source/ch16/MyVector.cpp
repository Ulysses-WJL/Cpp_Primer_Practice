#include "MyVector.h"
#include <iostream>

template <typename T>
MyVector<T>::MyVector(int size) : size(size) {
    data = new T[size];
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] data;
}

// 显式实例化定义（在这里实际生成代码）
template class MyVector<int>;
template int add<int>(int, int);