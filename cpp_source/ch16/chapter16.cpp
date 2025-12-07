//
// Created by w30065676 on 2025/9/29.
//
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <memory>
#include <type_traits>
#include <utility>
#include <cstdint>
#include "../ch08/Sales_Data.h"
#include "Blob.h"
#include "Vec.h"
#include "MyVector.h"
#include "shared_pointer.hpp"
#include "unique_pointer.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;


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
        os << "deleting ptr " << std::endl;
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

void test_explict_instantiation() {
    MyVector<int> vec(10);
    int result = add(110, 231);
}


void q_16_25() {
    /*
     * Explain the meaning of these declarations:
     * extern template class vector<string>;  // 显式实例化声明 （告诉编译器这些实例会在别处定义）
     * template class vector<Sales_data>;  // 实例化定义 （在这里实际生成代码）
     */
}

class NoDefalt {
public:
    NoDefalt(int x): value(x) {}
    int get() const { return value; }
private:
    int value;
};

void q_16_26() {
    /*
     * Assuming NoDefault is a class that does not have a default constructor,
     * can we explicitly instantiate vector<NoDefault>? If not, why not?
     * No, An instantiation definition for a class template instantiates all the members of that template
     * including inline member functions.
     * 显式实例化会尝试编译 std::vector 的所有成员函数，包括那些要求元素类型具有默认构造函数的函数。
     * 由于 NoDefault 没有默认构造函数，这些函数的实例化会失败，导致整个显式实例化失败。
     * 在隐式实例化中，编译器只生成实际被使用的成员函数
     */
    std::vector<NoDefalt> v;
    // std::vector<NoDefalt> v1(10); // 需要默认构造函数，NoDefalt中没有， 会失败
    std::vector<NoDefalt> v2{12, 14};
    cout << "v2: " << v2[0].get() << endl;
    v.reserve(10);

    v.emplace_back(42);
}

void q_16_27() {
    /*
    *隐式实例化：只有当模板类的完整定义（complete type） 被需要时，编译器才会实例化它。
    不完整类型：声明指针、引用、函数参数时，通常不需要完整类型。
    需要完整类型：定义对象、访问成员、sizeof、new 等操作需要完整类型。
     *
    *template <typename T> class Stack {	};
    void f1(Stack<char>); 		//(a)  不会导致模板实例化  声明函数，没有使用该类型的完整定义，
    class Exercise {
        Stack<double> &rds;		//(b)  不会， 引用声明不需要知道所引用类型的完整定义，
        Stack<int> si;			//(c)  会， 对象定义 编译器必须知道Stack<int>的完整定义
    };
    int main() {
        Stack<char> *sc;		//(d) 不会， 指针声明
        f1(*sc);				//(e) 会， 解引用，和值传递
        int iObj = sizeof(Stack<string>);	//(f) 会，sizeof 需要完整类型来计算大小
    }
     *
     */
}

void q_16_28() {
    // 运行时绑定Deleter
    auto foo = wjl::SharedPointer<int> {new int(42), DebugDelete()};
    auto bar{foo};
    std::cout << *foo << std::endl;
    std::cout << foo.use_count() << std::endl;

    auto string_ptr = wjl::SharedPointer<std::string>{ new std::string{ "Test" } };
    std::cout << *string_ptr << std::endl;
    std::cout << string_ptr->size() << std::endl;

    // 编译时绑定deleter
    unique_pointer<std::string> ps1(new std::string{ "Test" });
    unique_pointer<std::string> ps2(ps1.release());
    unique_pointer<std::string> ps3(new std::string{ "GoGoGo" });
    ps2.reset(ps3.release());
    auto ptr = ps2.get();
    cout << "ps2 value: " << *ptr << endl;
    ps2 = nullptr;
    unique_pointer<std::string> ps4(new std::string{ "Foo" });
    auto ptr2 = ps4.release();
    cout << "ps3 value: " << *ptr2 << endl;
    delete ptr2;
}

// template argument deduced

// 不能直接将数组传递给期望引用的函数
template <size_t N>
void func(const int (&arr)[N]) {
    for (size_t i = 0; i < N; ++i) {
        cout << arr[i] << endl;
    }
}

void process_array() {
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9};  // a 的类型是 int[10]
    func(a);
}


// argument types can differ but must be compatible
template <typename A, typename B>
int flexibleCompare(const A& v1, const B& v2)
{
    if (v1 < v2) return -1;
    if (v2 < v1) return 1;
    return 0;
}

void same_template_parameter_type() {
    long lng = 123456789;
    // compare(lng, 124); // No viable function Argument types: long, int.
    flexibleCompare(lng, 1234);
}

// （普通）非模板参数的转换，应用常规的类型转换规则
// 模板参数 要严格类型匹配
template<typename T>
bool is_greater_than(const T& value, int threshold) {
    return value > threshold;
}

void test_normal_conversion() {
    double price = 14.5;
    float templature = 21.4f;
    long bignum = 1001L;
    cout << std::boolalpha;
    cout << is_greater_than(bignum, 15.5f) << std::endl;  // float -> int
    cout << is_greater_than(templature, 25L) << std::endl;  // long -> int
    cout << is_greater_than(price, 999.1) << std::endl;  // double -> int
}

void q_16_32() {
    // What happens during template argument deduction?
    //  the compiler uses the arguments in a call to determine
    //  the template parameters for a function template.
    // 在模版实参推断过程中，编译器使用函数调用中的实参类型来寻找模版实参
}

void q_16_33() {
    // Name two type conversions allowed on function arguments involved in template argument deduction.
    // 1. const 转换，可以将一个非 `const` 对象的引用（或指针）传递给一个 `const` 的引用（或指针）形参。
    // 2. 数组或函数指针转换：如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换。
    // 一个数组实参可以转换为一个指向其首元素的指针。类似的，一个函数实参可以转换为一个该函数类型的指针。
}

template <typename T>
int compare_34(const T& v1, const T& v2) {
    return 0;
}

void q_16_34() {
    // c++ 数组类型包含大小信息
    // 字符串字面量的类型 const char[3] const char[6]
    // Inferred conflicting substitutions for template parameter T: char[3], char[6]
    // compare_34("hi", "world");
    compare_34("bye", "dad");  // T 类型是 char[4], 两个参数类型相同;
}

template <typename T>
T calc(T a, int b) {
    return a;
};
template <typename T> T fcn(T a, T b) {
    return a;
};

void q_16_35() {
    double d = 2.5;
    float f = 2.5;
    char c = 'c';

    calc(c, 'c');  // T为char，第二个参数常规转换 char -> int
    calc(d, f);  // T为double，第二个参数常规转换 float -> int
    fcn(c, 'c');  // T为char
    // fcn(d, f);   // illegal 模板参数严格转换，无法确认是double or float
}

template <typename T>
void f1(T, T) {};
template <typename T1, typename T2>
void f2(T1, T2) {};

void q_16_36() {
    int i = 0, j = 42, *p1 = &i, *p2 = &j;
    const int *cp1 = &i, *cp2 = &j;
    f1(p1, p2); // int *, int *
    f2(p1, p2);  // int *, int *
    f1(cp1, cp2);  // const int *, const int *
    f2(cp1, cp2);  // const int *, const int *
    // f1(p1, cp1);  // 不合法 int* 和 const int*
    f2(p1, cp1); // const int *, const int *
}

// Function-Template Explicit Arguments
template <typename T1, typename T2, typename T3>
T1 sum(T2 lhs, T3 rhs) {
    return lhs + rhs;
}

void test_explict_template_argument() {
    // 在函数名后<>内指定类型,  顺序要和模板参数列表的相同
    int i = 12334;
    long l = 22433134;
    auto val3 = sum<long long>(i, l);
    auto val4 = sum<long, int, long>(i, l);
    cout << val3 << endl;
    cout << val4 << endl;
}

void q_16_37() {
    // cout << std::max(12, 12.5);
    cout << std::max<double>(12, 12.5);  // 显式给出模板实参
}

void q_16_38() {
    // When we call make_shared (§ 12.1.1, p. 451), we have to provide an explicit template argument.
    // Explain why that argument is needed and how it is used.
    // make_shared<int>(42);
    // 如果不显示提供模版实参，那么 `make_shared` 无法推断要分配多大内存空间。
}

void q_16_39() {
    // compare_34("hi", "hello");
    compare_34<std::string>("hi", "hello");
}


// Trailing Return Types
template <typename It>
auto foo1(It beg, It end) -> decltype(*beg) {  // reference to element
    return *beg;
}

void test_trailing_return_types_template() {
    int a = 100;
    int *p = &a;
    int &ref = a;
    std::vector<int> vi = {1,  2, 3, 4};
    std::vector<std::string> svec = {"a", "fire", "go"};
    auto &i = foo1(vi.begin(), vi.end());
    auto &s  = foo1(svec.begin(), svec.end());
}

// type transformation
template <typename It>
auto foo2(It beg, It end) ->  // element by value
    std::remove_reference_t<decltype(*beg)> {  // typename remove_reference<decltype(*beg)>::type
    return *beg;
}

void test_type_transformation() {
    std::vector<int> vi = {1,  2, 3, 4};
    auto i = foo2(vi.begin(), vi.end());
    cout << i << endl;
}


// 16.40
template <typename It>
auto fcn3(It beg, It end) ->
    decltype(*beg + 0)  // string + 0 ill-formed, 需要支持+操作; 变成rvalue of ...
{
    // process the range
    return *beg; // return a copy of an element from the range
}

void q_16_40() {
    std::vector<int> vi = {1,  2, 3, 4};
    std::vector<std::string> svec = {"a", "fire", "go"};
    std::vector<float> fi = {1.1, 2.2, 3.3, 4.4};
    // auto &i = fcn3(vi.begin(), vi.end());  Non-const lvalue reference 'i' to type int cannot bind to rvalue of type int
    // auto &s  = fcn3(svec.begin(), svec.end());

    auto i = fcn3(vi.begin(), vi.end());
    auto f = fcn3(fi.begin(), fi.end());
    cout << i << " " << f << endl;
}

template <typename T1, typename T2>
auto sum(T1 lhs, T2 rhs) -> decltype(lhs + rhs) {
    using ResultType = std::common_type_t<T1, T2>;
    return static_cast<ResultType>(lhs) + static_cast<ResultType>(rhs);
}

void q_16_41() {
    int lhs = 0x1fffffff;
    int rhs = 0x7fffffff;
    cout << sum(lhs, rhs) << endl;
}

// Function Pointers and Argument Deduction
template <typename T>
int compare_2_4(const T& lhs, const T& rhs) {
    return lhs - rhs;
}

void func(int(*)(const std::string&, const std::string&)) {};
void func(int(*)(const int&, const int&)) {};

void test_function_pointer() {
    // pf1 points to the instantiation int compare(const int&, const int&)
    int (*pf1)(const int&, const int&) = compare_2_4;
    func(pf1);
    // func(compare);  // Ambiguous function call
    func(compare_2_4<int>);  // explicitly specify which version of compare to instantiate
}

// Template Argument Deduction and References

template <typename T>
void fff(T &t) {};

template <typename T>
void fff2(const T &t) {};

template <typename T>
void fff3(T &&t) {};

void template_argument_deduction() {
    int i = 1;
    const int ci = 1;
    fff(i);  // i is an int; template parameter T is int
    fff(ci);  // ci is a const int; template parameter T is const int
    // fff(5);  // Non-const lvalue reference to type int cannot bind to rvalue of type int

    fff2(i);  // i is an int; template parameter T is int
    fff2(ci);  // ci is a const int, but template parameter T is int
    fff2(5); // a const & parameter can be bound to an rvalue; T is int

    fff3(42);  // argument is an rvalue of type int; template parameter T is int

    // Reference Collapsing
    // 引用折叠仅在间接创建对引用的引用时适用，例如在类型别名或模板参数中。
    // X& &, X& &&,and X&& & all collapse to type X&
    // The type X&& && collapses to X&&

    // lvalue (e.g., i) to a function parameter that is an rvalue reference to a template type parameter
    fff3(i); // argument is an lvalue; template parameter T is int&
    fff3(ci); // argument is an lvalue; template parameter T is const int&

}


template <typename T>
void g(T &&val) {cout << val;}

void q_16_42_43() {
    int i = 0;
    const int ci = i;
    g(i);  // since i is lvalue, T is deduced as int&, val is int& && collapsing to int&
    g(ci);  //since ci is lvaue, T is deduced as const int&, val is const int& && collapsing to const int&
    g(i * ci);  // since i * ci is rvalue, T is deduced as int, val is int&& && colapsing to int&&
    g(i = ci);  // (i = ci) 返回的是lvalue , Hence T is deduced as int& val is int& && collapsing to int&.
}
template <typename T>
void g1(T val) {cout << val;}
void q_16_44_1() {
    int i = 0;
    const int ci = i;
    g1(i);  // T is deduced as int
    g1(ci);  // T is deduced as int, top-level consts in either the parameter or the argument are ignored
    g1(i * ci);  // T is deduced as int, (i * ci) returns rvalue which is copied to T
}

template <typename T>
void g2(const T& val) {cout << val;}
void q_16_44_2() {
    int i = 0;
    const int ci = i;
    g1(i);  // T is deduced as int , val : const int&
    g1(ci);  //  T is deduced as int  , val : const int&
    g1(i * ci);  //  T is deduced as int  , val : const int& ;  a const & parameter can be bound to an rvalue
}

template <typename T> void g3(T&& val) { std::vector<T> v; }

void q_16_45() {
    g3(42);  // argument is an rvalue of type int; template parameter T is int
    int i = 42;
    // g3(i);  // T 是 Int &;  std::vector<int &> illegal
}

void q_16_46() {
    // for (size_t i = 0; i != size(); ++i)
    //     alloc.construct(dest++, std::move(*elem++));
    // 在每个循环中，对 `elem` 的解引用操作 `*` 当中，会返回一个左值，`std::move` 函数将该左值转换为右值，提供给 `construct` 函数。
}

// forward
template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2)
{
    f(t2, t1);
}

void f(int v1, int& v2) {
    cout << v1 << " " << ++v2 << endl;
}

// reference collapsing
// A function parameter that is an rvalue reference to a template type parameter (i.e., T&&)
// preserves the constness and lvalue/rvalue property of its corresponding argument.
template <typename F, typename T1, typename T2>
void flip2(F f, T1&& t1, T2&& t2)
{
    f(t2, t1);
}

void g(int &&i, int& j)
{
    cout << i << " " << ++j << endl;
}

template <typename F, typename T1, typename T2>
void flip3(F f, T1&& t1, T2&& t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
    //保持值类别 , 完美转发
}

void test_flip() {
    int i = 0;
    f(42,i);
    cout << "f changes its argument i : " << i << endl;
    int j = 0;
    // 按值传递导致引用丢失：f 的第二个参数是 int&，但在 flip1 中 t1 是按值传递的 T1 类型
    flip1<void(int, int&)>(f, j, 0);  // 显式指定模板参数
    cout << " f called through flip1 leaves j unchanged : "  << j << endl;
    flip2<void(int, int&)>(f, j, 0);
    cout << " reference collapsing : "  << j << endl;
    // error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
    /*
    * t2 在函数内部是左值
    42 作为右值传递给 flip2
    t2 的类型推导为 int&&（万能引用）
    但是，在 flip2 函数体内，t2 是一个有名字的变量，所以它是左值
    不能将左值 t2 传递给 g 的右值引用参数 i

    t1 也有类似问题
    i 作为左值传递给 flip2
    t1 的类型推导为 int&（万能引用）
    在函数体内 t1 是左值，可以传递给 g 的左值引用参数 j
     */
    // flip2<void(int &&, int&)>(g, i, 42);
    int k = 0;
    flip3<void(int &&, int&)>(g, k, 42);
    cout << " 完美转发: "  << k << endl;
}

// 模板函数和 重载

template <typename T>
string debug_rep(const T &t) {
    cout << "first" << endl;
    std::ostringstream ret;
    ret << t;
    return ret.str();  // return a copy of the string to which ret is bound
}

template <typename T>
string debug_rep(T *p) {
    cout << "second" << endl;
    std::ostringstream ret;
    ret << "pointer: " << p;
    // print the pointer’s own value
    if (p)
        ret << " " << debug_rep(*p); // print the value to which p points
    else
        ret << " null pointer"; // or indicate that the p is null
    return ret.str(); // return a copy of the string to which ret is bound
}

string debug_rep(const string &s) {
    cout << "nontemplate" << endl;
    return '"' + s + '"';
}

void test_rep() {
    string s("hello world");
    cout << debug_rep(s) << endl;  // 调用第一个
    // 第一个： debug_rep(const string*&),  T 是string*
    // 第二个： debug_rep(string *), T 是 string
    cout << debug_rep(&s) << endl;

//   debug_rep(const string*&), the instantiation of the first version of the template with T bound to const string*
//   debug_rep(const string*), the instantiation of the second version of the template with T bound to const string
    // resolves to debug_rep(T*)
    const string *sp = &s;
    cout << debug_rep(sp) << endl;
}

void test_nontemplate_and_template_overloads() {
    string s("hi");
    // a nontemplate function is preferred over equally good match(es) to a function template.
    cout << debug_rep(s) << endl;
}

void test_c_style_strings() {
    /*
    * debug_rep(const T&),with T bound to char[10]
    • debug_rep(T*),with T bound to const char (more specialized)
    • debug_rep(const string&), which requires a conversion from const char* to string
     */
    cout << debug_rep("hello world") << endl;
}

// q_16-49
template <typename T> void f1649(T t) {cout << "f1 " << t << endl; };
template <typename T> void f1649(const T* t) { cout << "f2 " <<  *t << endl; };
template <typename T> void g1649(T t) {cout << "g1 " << t << endl; };
template <typename T> void g1649(T*t) {cout << "g2 " << *t << endl; };

void q_16_49() {
    int i = 42, *p = &i;
    const int ci = 0, *p2 = &ci;
    g1649(42);  // g(T)
    g1649(p);  // g(T*)
    g1649(ci);  // g(T)
    g1649(p2);  // g(T * )
    f1649(42); // f(T)
    f1649(p);  // f(T)  T is bound to int*
    f1649(ci);  // f(T)
    f1649(p2);  // f(const T*)
}

// variadic template 可变参数模板， 接收可变数目的参数
template<typename T, typename... Args>
void foo1651(const T &t, const Args & ... rest) {
    cout << "=================" << endl;
    cout << sizeof...(rest) << endl;  // number of function parameters
    cout << sizeof...(Args) << endl;  // number of type parameters
    cout << "=================" << endl;
}

void q_16_51_52() {
    int i = 0;
    double d = 3.14;
    string s = "how now brown cow";
    foo1651(i, s, 42, d); // three parameters in the pack
    foo1651(s, 42, "hi"); // two parameters in the pack
    foo1651(d, s); // one parameter in the pack
    foo1651("hi"); // empty pack
}


// 非可变参数版本的  需要先定义，否则  no matching function for call
template<typename T>
std::ostream &print_1653(std::ostream &os, const T &t) {
    return os << t;
}

template <typename T, typename... Args>
std::ostream &print_1653(std::ostream &os, const T &t, const Args &... rest) {
    // os << t << ", ";
    return print_1653(os << t << ", ",  rest...);
}

void q_16_53() {
    int i = 42;
    double d = 3.14;
    string s = "go go go";
    const int ci = 0, *p = &i;
    print_1653(cout, i, d, s, ci, *p);
    cout << endl;
    print_1653(cout, i, d, s);
    cout << endl;
    print_1653(cout, i);
    cout << endl;
}

// Pack Expansions
template <typename ...Args>
std::ostream &errorMsg(std::ostream &os, const Args ... args) {
    return print_1653(cout, debug_rep(args)...);
}

void q_16_56() {
    cout << "===========16 56============" << endl;
    int i = 42;
    double d = 3.14;
    string s = "go go go";
    errorMsg(cout, i, d, s) << endl;
    cout << "===========16 56============" << endl;
}

int main(int argc, char **argv) {
    q_16_56();
    q_16_53();
    q_16_51_52();
    q_16_49();
    test_c_style_strings();
    test_nontemplate_and_template_overloads();
    test_rep();
    test_flip();
    q_16_45();
    q_16_44_2();
    q_16_44_1();
    q_16_42_43();
    q_16_41();
    q_16_40();
    test_type_transformation();
    test_trailing_return_types_template();
    q_16_39();
    q_16_37();
    test_explict_template_argument();
    q_16_35();
    q_16_34();
    test_normal_conversion();
    same_template_parameter_type();
    q_16_28();
    q_16_26();
    test_explict_instantiation();
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
    cout << compare_1(0.6, 0.5) << endl;
    cout << compare(10, 41) << endl;
    cout << compare(0, 0) << endl;
    int x = 124;
    int *p = &x;
    cout << foo(p) << endl;
    return 0;
}
