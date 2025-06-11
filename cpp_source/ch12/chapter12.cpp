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

void test_unique_ptr() {
    // only one unique_ptr at a time can point to a given object
    unique_ptr<double> p1;
    unique_ptr<int> p2(new int(42)); // direct initialization
    unique_ptr<string> ps1(new string("GoGoGo"));
    // unique_ptr<string> ps2(ps1); // error: no copy for unique_ptr
    unique_ptr<string> ps3;
    // ps3 = ps1; // Rvalue reference to type unique_ptr<string> cannot bind to lvalue of type unique_ptr<string>

    p2 = nullptr;  // 释放p1指向的object，
    // ps1.release(): 放弃对ps1指向对象o的控制，返回一个指向o的指针，ps1为null
    // 现在ps4获得o的控制
    unique_ptr<string> ps4(ps1.release());
    cout << "value of ps4：" << *ps4 << endl;
    unique_ptr<string> ps5(new string("Hello!"));
    // transfers ownership from ps5 to ps4
    // 原先ps4指向的对象被销毁
    ps4.reset(ps5.release());
    // ps4.release(); // // WRONG: ps4 won’t free the memory and we’ve lost the pointer
    auto p = ps4.release();  // 没有使用智能指针，手动释放
    cout << "value of p：" << *p << endl;
    delete p;
}

unique_ptr<int> clone_unique(int p) {
    // return unique_ptr<int>(new int(p));
    unique_ptr<int> ret(new int(p));
    return ret;
}

void test_return_unique_ptr() {
    unique_ptr<int> p1(new int(42));
    unique_ptr<int> p2 = clone_unique(*p1);
    cout << *p1 << endl;
    cout << *p2 << endl;
}


void q_12_16() {
    unique_ptr<int> p1(new int(111));
    // unique_ptr<int> p2(p1);
//     error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
//   183 |     unique_ptr<int> p2(p1);
//     |                          ^
// In file included from /usr/include/c++/11/memory:76,
//                from /mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch12/chapter12.cpp:3:
// /usr/include/c++/11/bits/unique_ptr.h:468:7: note: declared here
// 468 |       unique_ptr(const unique_ptr&) = delete;
    unique_ptr<int> p3;
    // p3 = p1;
//     error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>& std::unique_ptr<_Tp, _Dp>::operator=(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
//   185 |     p3 = p1;
//     |          ^~
// In file included from /usr/include/c++/11/memory:76,
//                from /mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch12/chapter12.cpp:3:
// /usr/include/c++/11/bits/unique_ptr.h:469:19: note: declared here
// 469 |       unique_ptr& operator=(const unique_ptr&) = delete;
//     |                   ^~~~~~~~
    cout << *p1 << endl;
}

void q_12_17() {
    int ix = 1024, *pi = &ix, *pi2 = new int(2048);
    typedef unique_ptr<int> IntP;
    // IntP p0(ix);  // illegal, 需要将其绑定到一个new 返回的指针上。
    // IntP p1(pi);  // illegal, 需要将其绑定到一个new 返回的指针上。
    IntP p2(pi2);  // legal, 但pi2就会是dangling pointer，需要delete
    p2 = nullptr;
    // IntP p3(&ix);  // 不合适 p3销毁时， ix也会被释放
    IntP p4(new int(2048));  // legal
    // Don’t use get() to initialize or reset another smart pointer.
    // IntP p5(p2.get());  // p5 和 p2 指向同一个对象，当 p5 和 p2 被销毁时，会使得同一个指针被释放两次
}


int main(int argc, char *argv[]) {
    q_12_17();
    q_12_16();
    test_return_unique_ptr();
    test_unique_ptr();
    test_mix();
    // q_12_6();
    q_12_1();
    test_smart_ptr();
    return 0;
}
