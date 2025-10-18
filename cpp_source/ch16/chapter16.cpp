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
#include "Vec.h"

using std::cout;
using std::cin;
using std::endl;


// Templates are the foundation for generic programming in C++

//Function Templates
template <typename T>  // 早期标准中使用 class关键字声明模板参数
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

    Blob<char> c_a = {'a' , 'b', 'c'}; // BlobPtr<char> and operator==<char> are friends
    Blob<char> c_b = {'b', 'c'};
    cout << std::boolalpha << (c_a == c_b) << endl;
    Blob<int> i_a; // BlobPtr<int> and operator==<int> are friends
}

// 将自己的类型参数成为友元
// Foo 是Bar<Foo>的友元， int 是Bar<int> 的 友元
template <typename Type>
class Bar {
    friend Type;
};

// Template Type Aliases
template <typename T> using twin = std::pair<T, T>;
template <typename T> using partNo = std::pair<T, unsigned>;

void test_template_type_aliases() {
    typedef Blob<std::string> StrBlob;
    using IntBlob = Blob<int>;
    StrBlob b = {"a", "b", "foo", "bar"};
    IntBlob ia{1, 2, 3, 4};
    twin<StrBlob> twin_str;
    twin_str.first = {"a", "b"};
    twin_str.second = {"foo", "bar"};
    partNo<std::string> pno;
}

// static members of class template
template <typename T>
class Foo {
public:
    static std::size_t count() {return ctr;}
private:
    static std::size_t ctr;
};

template <typename T>
size_t Foo<T>::ctr = 110;

void test_static_member() {
    Foo<int> fi, fi2;
    auto ct = Foo<int>::count();
    ct = fi.count();
    cout << "ctr: " << ct << endl;
    // ct = Foo::count();  // Use of class template requires template argument list
}

void q_16_9() {
    //What is a function template? What is a class template?
    /*
     * 一个函数模版就是一个公式，可用来生成针对特定类型的函数版本。
     * 类模版是用来生成类的蓝图的，与函数模版的不同之处是，编译器不能为类模版推断模版参数类型。
     * 如果我们已经多次看到，为了使用类模版，我们必须在模版名后的尖括号中提供额外信息。
     */
}

void q_16_10() {
    // What happens when a class template is instantiated?
    // 一个类模版的每个实例都形成一个独立的类。
}

// 16_11

template <typename elemType> class ListItem;
template <typename elemType>
class List {
public:
    List<elemType>();
    List<elemType>(const List<elemType> &);
    List<elemType>& operator=(const List<elemType> &);
    ~List();
    void insert(ListItem<elemType> *ptr, elemType value); // Use of class template requires template argument list
private:
    ListItem<elemType> *front, *end;  // Use of class template requires template argument list
};

void q_16_13() {
    // Explain which kind of friendship you chose for the equality and relational operators for BlobPtr.
    // one-on-one 一对一友好关系

}


// q_16_14, 16_15  nontype parameters
template<unsigned H, unsigned W>
class Screen {
public:
    using pos = std::string::size_type;
    Screen() = default;
    Screen(char c) :contents(H * W, c) {}
    char get() const {return contents[cursor];}
    Screen &move(pos c, pos r);
    friend std::ostream &operator<<(std::ostream &os, Screen &c) {

        for (unsigned i = 0; i < c.height; ++i) {
            os<< c.contents.substr(i * W, W) << endl;
        }
        return os;
    }

    friend std::istream & operator>>(std::istream &is, Screen &c) {
        char a;
        is >> a;
        c.contents = std::string(H * W, a);
        return is;
    }
private:
    pos cursor = 0;
    pos height = H, width = W;
    std::string contents;
};

template<unsigned H, unsigned W>
Screen<H, W> &Screen<H, W>::move(pos c, pos r) {
    cursor = r * width + c;
    return *this;
}

void q_16_14_15() {
    Screen<4, 8> screen('0');
    cout << screen;
    cin >> screen;
    cout << screen;
}

void q_16_16() {
    Vec<std::string> svec({"a", "b"});
    svec.push_back("c");
    cout << *svec.begin() << endl;
    cout << svec << endl;

}

// Template Parameters
typedef double A;
template <typename A, typename B>
void f(A a, B b) {
    A tmp = a;
    // parameter name cannot be reused
    // double B;  // Local variable double B redeclares type template parameter typename B from an outer scope

}

// Using Class Members That Are Types
// 显式 声明 name 是 type
template <typename T>
typename T::value_type top(const T &c) {
    if (!c.empty()) {
        return c.back();
    } else {
        return typename T::value_type();
    }
}

// default template arguments
template <typename T, typename F = std::less<T>>
int compare_1(const T &v1, const T &v2, F f = F()) {
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}

void test_default_template_arguments() {
    int v1 = 2, v2 = 3;
    cout << compare_1(v1, v2) << endl;
    auto f = [](double a, double b) {
        if (a < b) return -1;
        if (b < a) return 1;
        return 0;
    };
    cout << compare_1(12.5, 3.2, f) << endl;
}

// Template Default Arguments and Class Templates
template <typename T = int>
class Numbers {
public:
    Numbers(T v = 0) : val(v) {}
private:
    T val;
};

void test_number() {
    Numbers<long double> lots_of_precision;
    Numbers<> average_precision;  // 空的<> 使用默认type  int
}

void q_16_17() {
    // What, if any, are the differences between a type parameter that is declared as a typename and one that is
    // declared as a class? When must typename be used?
    // 没有什么不同。当我们希望通知编译器一个名字表示类型时，必须使用关键字 typename，而不能使用 class。
}


template <typename T, typename U, typename V> void f1(T, U, V);
template <typename T> T f2(int &t);
template <typename T> T foo(T, unsigned int*);
template <typename T> T f4(T, T);

typedef char Ctype;  // Ctype 被隐藏
template <typename Ctype> Ctype f5(Ctype a);
void q_16_18() {
    /*
     * Explain each of the following function template declarations and identify whether any are illegal.
     * Correct each error that you find.
     */

    /*
    *
    (a) template <typename T, U, typename V> void f1(T, U, V);
    (b) template <typename T> T f2(int &T);
    (c) inline template <typename T> T foo(T, unsigned int*);
    (d) template <typename T> f4(T, T);
    (e) typedef char Ctype;
    template <typename Ctype> Ctype f5(Ctype a);

     */
}

template <typename T>
void func(const T &t) {
    for (typename T::size_type i = 0; i < t.size(); ++i) {
        cout << t[i] << " ";
    }
    cout << endl;
}

template <typename T>
void func2(const T &t) {
    for (auto it = t.begin(); it != t.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void q_16_19_20() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    func(v);
    func2(v);
}


// member template
class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr) : os(s) {}
    template <typename T>
    void operator()(T *p){
        os << "deleting unique_ptr " << std::endl;
        delete p;
    }
private:
    std::ostream &os;
};

void test_debug_delete() {
    double *p = new double;
    DebugDelete d;
    d(p);

    int *ip = new int;
    DebugDelete()(ip);

    std::unique_ptr<int, DebugDelete> up(new int(32), DebugDelete());
    std::unique_ptr<std::string, DebugDelete> up_str(new std::string("aaa"), DebugDelete());
    cout << *up << endl;
    cout << *up_str<< endl;
}

// member templates of class templates
void test_Member_Templates_of_Class_Templates() {
    std::vector<std::string> v1{"a", "b", "c"};
    Blob<std::string> b1(v1.begin(), v1.end());
    b1.push_back("d");
    cout << b1.size() << endl;
}

int main(int argc, char **argv) {
    test_Member_Templates_of_Class_Templates();
    test_debug_delete();
    q_16_19_20();
    test_default_template_arguments();
    f<int, int>(2, 3);
    // q_16_16();
    // q_16_14_15();
    std::vector<std::vector<int>> ans;
    ans.push_back({1});
    test_static_member();
    test_template_type_aliases();
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
