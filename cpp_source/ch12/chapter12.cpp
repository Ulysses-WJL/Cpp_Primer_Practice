#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <new>
#include "StrBlob.h"

using std::cout; using std::endl; using std::cin;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::make_shared;
using std::vector;

void test_smart_ptr() {
    // it automatically deletes the object to which it points
    string *p0 = nullptr;
    shared_ptr<string> p1(new string("let's go"));  // 手动创建
    shared_ptr<vector<int>> p2;
    // 推荐方式 allocate and use dynamic memory
    shared_ptr<int> p3 = make_shared<int>(42);
    shared_ptr<string> p4 = make_shared<string>(10, 'a');
    auto p5 = make_shared<int>();
    auto q(p1);

    if (p1 && p1->empty())
        *p1 = "init!";
    cout << *p1 << endl;
    cout << "p5: " << *p5 << endl;
    cout << "Use count: " << p1.use_count() << endl;
}

void q_12_1() {
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
    }
    // b2 释放，b1中有4个

    cout << "size of b1: " << b1.size() << endl;

}

void test_new_delete() {
    // 使用new delete来直接管理内存，
    // new returns a pointer to the object it allocates
    // if allocation fails, new throws std::bad_alloc
    int *p = new int;  // unnamed , uninitialized int
    string *ps1 = new string;   // default initialized to the empty string
    string *ps2 = new string();  // value initialized to the empty string
    int *p2 = new int();  // value initialized to 0; *pi2 is 0

    vector<int> *pv = new vector<int>{1, 2, 3, 4, 5};

    auto p3 = new auto("string");  // auto推断时 必须使用 parentheses

    const int *pci = new const int(124);  // const 必须显式初始化
    const string *pcs = new const string;  // string类 隐式初始化

    int *pi = new (std::nothrow) int;  // if allocation fails, new returns a null pointer

    // p must point to a dynamically allocated object or be null
    delete p;  // p 变为 dangling pointer
    p = nullptr;   // 如果多个指针 指向相同的动态分配内存，其余指针仍是dangling pointer
    delete ps1;
    delete ps2;
    delete p2;
    delete p3;
    delete pci;
    delete pcs;
    delete pv;
    delete pi;

}

// // factory returns a pointer to a dynamically allocated object
// Foo* factory(T arg)
// {
//     // process arg as appropriate
//     return new Foo(arg); // caller is responsible for deleting this memory
// }
//
// void use_factory(T arg)
// {
//     Foo *p = factory(arg);
//     // use p but do not delete it
// } // p goes out of scope, but the memory to which p points is not freed!

shared_ptr<vector<int>> foo() {
    // return new vector<int>();
    return make_shared<vector<int>>();
}

shared_ptr<vector<int>>  use_foo() {
    auto pvec = foo();
    for (int i; cin >> i; ) {
        pvec->push_back(i);
    }
    return pvec;
}

void q_12_6() {
    auto pvec = use_foo();
    for (auto &item : *pvec) {
        cout << item << " ";
    }
    cout << endl;
    // delete pvec;
}

shared_ptr<int> clone(int p) {
    return shared_ptr<int> (new int(p));  // 显式转化
}

void test_shared_ptr_with_new() {
    shared_ptr<double> p1;
    shared_ptr<int> p2(new int(23));  // 使用new初始化
    // shared_ptr<int> p3 = new int(1024); // error: must use direct initialization
}

void process(shared_ptr<int> ptr) {
    cout << "original val: " << *ptr << endl;
    ++*ptr;
    cout << "new val: " << *ptr << endl;
}

void test_mix() {
    shared_ptr<int> p(new int(42));  // reference count is 1
    process(p);  // copying p increments its count; in process the reference count is 2
    int i = *p;  // reference count is 1

    int *x(new int(100));
    // process(x);  // error: cannot convert int* to shared_ptr<int>
    process(shared_ptr<int>(x));  // legal, but the memory will be deleted!
    int j = *x;  // undefined: x is a dangling pointer!
    cout << j << endl;

}

int main(int argc, char *argv[]) {
    test_mix();
    // q_12_6();
    q_12_1();
    test_smart_ptr();
    return 0;
}
