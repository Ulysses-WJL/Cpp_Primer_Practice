#ifndef MYVECTOR_H
#define MYVECTOR_H

template <typename T>
class MyVector {
private:
    T* data;
    int size;
public:
    MyVector(int size);
    ~MyVector();
    // ... 其他方法
};

template <typename T>
T add(T a, T b) {
    return a + b;
}

// 显式实例化声明（告诉编译器这些实例会在别处定义）
extern template class MyVector<int>;
extern template int add<int>(int, int);

#endif // MYVECTOR_H