#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <new>
#include <fstream>
#include <sstream>

#include "StrBlob.h"
#include "TextQuery.h"

using std::cout; using std::endl; using std::cin;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
using std::make_shared;
using std::vector;
using std::allocator;

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
    cout << "j的值 undefine ： " << j << endl;
}

void test_shared_ptr_operations() {
    shared_ptr<int> p(new int(23));
    // p = new int(1024); // error: cannot assign a pointer to a shared_ptr
    p.reset(new int(1024)); // p points to a new object
    cout << "value of p: " << *p << endl;
    if (!p.unique())
        // 有其他共享资源的指针， 重置p，不影响其他指针
        p.reset(new int(*p));
    *p += 23;
    cout << "new value of p: " << *p << endl;
}

void q_12_10() {
    // 正确
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p));  // 创建一个临时的智能指针, 引用同一个对象 reference count +1
    cout << "end, P: " << *p << endl;
    // 结束后释放
}

void q_12_11() {
    // 正确
    shared_ptr<int> p(new int(42));
    process(shared_ptr<int>(p.get()));  // 创建新智能指针，count 为1, 这里结束后 临时智能指针会被销毁
    // p 所指的内存空间也被释放 ，p dangling pointer
    // Process finished with exit code -1073740940 (0xC0000374)
    cout << "end, P: " << *p << endl;
}

void q_12_12() {
    auto p = new int();
    auto sp = make_shared<int>();

    process(sp);  // legal，结束后引用计数 重新变为1
    // process(new int()); // illegal, 不能从内置指针隐式转换为智能指针。
    // process(p);  //  illegal, 不能从内置指针隐式转换为智能指针。
    // process(shared_ptr<int>(p));  // legal , 但结束后p指向的对象会被释放, 后续继续使用会出错
}

void q_12_13() {
    auto sp = make_shared<int>();
    auto p = sp.get();
    delete p;  // sp 指向的内存空间也被释放，继续使用sp会报错
}

struct connection {
    string ip;
    int port;
    connection(string s, int p): ip(s), port(p) {};
};

struct destination {
    string ip;
    int port;
    destination(string s, int p): ip(s), port(p) {};
};

connection connect(destination *p_dest) {
    // 创建一个到dest的 connection
    shared_ptr<connection> p_conn(new connection(p_dest->ip, p_dest->port));  // p_conn_out销毁时，p_conn指向的连接也被释放
    cout << "creating connection to " << p_dest->ip << ":" << p_dest->port  << "; use_count: " << p_conn.use_count() << endl;
    return *p_conn;  // 返回连接的对象
}
void disconnect(connection conn) {
    // 关闭连接，...
    std::cout << "connection close(" << conn.ip << ":" << conn.port << ")" << std::endl;
}

void end_connection(connection *p_conn) {
    disconnect(*p_conn);
}

void q_12_14(destination &d /* other parameters */)
{
    // 创建连接
    connection conn = connect(&d);
    // 使用智能指针管理conn，p_conn_out指向conn，当reference count 为0时，销毁指针，
    // 释放conn 调用end_connection
    // shared_ptr<connection> p_conn_out(&conn, end_connection);  // deleter function
    shared_ptr<connection> p_conn_out(&conn, [](connection *p){disconnect(*p);});  // 使用lambda函数
    // auto p_conn_out = make_shared<connection>(conn);
    cout << "connecting now(" << p_conn_out.use_count() << ")" << std::endl;
    // 使用 ...
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

void test_weak_ptr() {
    auto p = make_shared<int>(42);
    // weak_ptr需要指向被shared_ptr管理的对象
    weak_ptr<int> wp(p);
    // 不会增加引用计数，即使有弱指针指向该对象，该对象也会被删除
    cout << "use count : " << p.use_count() << endl;
    // lock 检测weak_ptr 指向的对象是否存在
    if (shared_ptr<int> np = wp.lock()) {  // true if np is not null
        cout << "inside use count : " << p.use_count() << endl;
        cout << *np << endl;
    }
    cout << "use count : " << p.use_count() << endl;
}

void q_12_19() {
    std::ifstream f("/mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch12/storyDataFile.txt");
    StrBlob sb;
    for (string s; std::getline(f, s);) {
        sb.push_back(s);
    }
    // 使用 StrBlobPtr 进行输出sb的内容, 需重要定义 !=
    for (StrBlobPtr sbp = sb.begin(); sbp != sb.end(); sbp.incr()) {
        cout << sbp.deref() << endl;
    }
}

void q_12_21() {
    // 为了能让 StrBlobPtr 使用 const StrBlob，你觉得应该如何修改？
    // 定义一个名为ConstStrBlobPtr 的类，使其能够指向 const StrBlob。
    const StrBlob csb = {"str 1", "hello world","what doesn't kill you", "makes you stronger!"};
    // 使用 StrBlobPtr 进行输出sb的内容, 需重要定义 !=
    for (ConstStrBlobPtr csbp = csb.cbegin(); csbp != csb.cend(); csbp.incr()) {
        cout << csbp.deref() << endl;
    }
}

size_t get_size() {
    return 4;  // 可以创建大小为0的dynamic array
}

void test_dynamic_arrays() {
    // 更推荐使用library containers
    // pia points to the first of these ints, 而不是指向array的指针，也不能使用begin end， range-for
    size_t n = get_size();
    int *pia = new int[n];
    int *p1 = new int[42];  // uninitialized ints
    using arrT = int [42];
    int *p2 = new arrT();  // initialized to 0
    string *psa = new string[10];  // 10 empty string
    string *psa1 = new string[10]();  // 10 empty string
    // 不能在括号里面进行element initializer，
    // 不能像`auto p3 = new auto("string");` 使用auto分配dynamic array

    // braced list initializer
    int *pia2 = new int[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    string *psa2 = new string[10]{"a", "an", "the", string(4, 'x')};
    for (int *q = pia; q != pia + n; ++q) {
        *q = 12;
    }
    if (n > 0)
        cout << "pia: " << *pia << endl;
    else
        cout << "cannot dereference pia" << endl;

    // brackets are necessary because we allocated an array
    delete [] pia;
    delete [] p1;
    delete [] p2;
    delete [] psa;
    delete [] psa1;
    delete [] pia2;
    delete [] psa2;
}

void test_smart_pointer_dynamic_arrays() {
    // 使用unique_ptr 管理 dynamic arrays
    unique_ptr<int []> up(new int[10]);
    for (size_t i = 0; i != 10; ++i) {
        // unqiue_ptr points to an array, 使用subscript操作
        up[i] = i;
    }
    up.release();  // automatically uses delete[] to destroy its pointer

    // shared_ptrs provide no direct support for managing a dynamic array. 需
    // 要自定义 deleter
    shared_ptr<int> sp(new int[10], [](int *p){delete [] p;});
    for (size_t i = 0; i != 10; ++i) {
        // 使用get获取built-in pointer(int *p), + i移动到指定位置, dereference 到对应对象
        *(sp.get() + i) = i;
    }
    sp.reset();  // uses the lambda we supplied that uses delete[] to free the array
}

void q_12_23() {
    string s1("hello"), s2(" world");
    const char *c1 = "hello";
    const char *c2 = " world";
    unsigned len = strlen(c1) + strlen(c2) + 1;
    // unique_ptr<char []> uq(new char[len]);
    char *r = new char[len]();
    strcat(r, c1);
    strcat(r, c2);
    cout << r << endl;

    strcpy(r, (s1+s2).c_str());
    cout << r << endl;

    delete [] r;
}

void q_12_24() {
    //从标准输入读取一个字符串，存入一个动态分配的字符数组中
    cout << "输入长度";
    int size(0);
    cin >> size;
    char *buffer = new char[size + 1]();
    cin.ignore(); // 1. **清除输入缓冲区中的多余字**, 2 清除cin的换行符
    cout << "input the string: ";
    cin.getline(buffer, size + 1);
    cout << "input: " << buffer << endl;
    delete [] buffer;
}

void test_coupling_allocation_construction() {
    size_t n = 3;
    string *const p = new string[n];
    string *q = p;
    for (string s; cin >> s && q != p+n; q++) {
        *q = s;
    }
    const size_t size = q - p;
    delete [] p;
}

void test_allocator() {
    // separate allocation from construction
    size_t n = get_size();
    allocator<string> alloc;
    auto const p = alloc.allocate(n);  // allocate n unconstructed strings
    auto q = p;
    // 超出n，会报 sysmalloc 错误
    alloc.construct(q++, string(5, 'x'));  // 构造 指针指向区域的对象
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++);
    cout << *p << endl;
    cout << *q << endl;  // disaster: q points to unconstructed memory!

    // destroy， 只能释放已constructed的元素
    while (q != p) {
        alloc.destroy(--q);
    }
    // reuse the memory
    alloc.deallocate(p, n);
}

void test_allocator_algorithms() {
    // 在未初始化的内存中构造数据
    allocator<int> ialloc;
    vector<int> ivec{1, 2, 3, 4};
    auto p = ialloc.allocate(ivec.size() * 2);
    // 前半部分 copy自ivec , q：one past the last constructed element
    auto q = std::uninitialized_copy(ivec.begin(), ivec.end(), p);
    // 后半部分 fill 100
    std::uninitialized_fill_n(q, ivec.size(), 100);
}

void q_12_26() {
    size_t n = 3;
    allocator<string> salloc;
    auto const p = salloc.allocate(n);
    auto q = p;
    for (string s; cin >> s && q != p + n; q++) {
        salloc.construct(q, s);
    }
    while (q != p) {
        cout << "val: " << *--q << endl;
        salloc.destroy(q);
    }
    salloc.deallocate(p, n);
}

void run_querires(std::ifstream &ifs) {
    TextQuery tq(ifs);
    while (true) {
        cout << "enter word to look for , or q to quit: \n";
        string s;
        if (!(cin >> s) || (s == "q")) break;

        print(cout, tq.query(toLowerCase(s))) << endl;
    }
}

void q_12_27() {
    std::ifstream file("/mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch12/storyDataFile.txt");
    run_querires(file);
}

void q_12_28() {
    using lineno = vector<string>::size_type;
    std::map<const string, std::set<lineno>> word_map;
    std::set<lineno> line_nos;
    vector<string> file_text;
    std::ifstream file("/mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch12/storyDataFile.txt");
    for (string line; std::getline(file, line);) {
        file_text.push_back(line);
        lineno n = file_text.size() - 1;
        std::istringstream words(line);
        for (string word, clean_word, lower_word; words >> word; clean_word.clear()) {
            lower_word = toLowerCase(word);
            std::remove_copy_if(lower_word.begin(), lower_word.end(), std::back_inserter(clean_word), ispunct);
            word_map[clean_word].insert(n);
        }
    }
    while (true) {
        cout << "enter word to look for , or q to quit: \n";
        string s;
        if (!(cin >> s) || (s == "q")) break;

        if (auto res = word_map.find(toLowerCase(s)); res != word_map.end()) {
            std::cout << s << " occurs " << res->second.size() << (res->second.size() > 1 ? " times" : " time") << std::endl;
            for (auto no: res->second) {
                cout << "\t(line " << no + 1 << ") " << file_text[no] << endl;
            }
        } else {
            cout << s << " occurs 0 time." << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    q_12_28();
    // q_12_27();
    // q_12_26();
    test_allocator();
    // q_12_24();
    q_12_23();
    test_dynamic_arrays();
    q_12_21();
    q_12_19();
    test_weak_ptr();
    q_12_17();
    q_12_16();
    test_return_unique_ptr();
    test_unique_ptr();
    // q_12_11();
    destination dest("192.168.0.1", 88);
    q_12_14(dest);
    q_12_10();
    test_mix();
    // q_12_6();
    q_12_1();
    test_smart_ptr();
    return 0;
}
