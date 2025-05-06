//
//
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <vector>
#include <cstdio>
#include "Chapter6.h"

#include <algorithm>


using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::runtime_error;
using std::begin;
using std::end;

void q_6_4() {
    const string prompt = "输入数字: \n";
    int num = 0;
    while (cout << prompt, cin >> num) {
        cout << "结果是：" << fact(num) << endl;
    }
}

int abs(int i) {
    return i > 0 ? i : -i;
}

int count_num(int n) {
    static int ctr = 0;  // 静态变量  跨调用保留
    int temp = n * 2;    //  局部变量：temp（每次调用重新初始化）
    ++ctr;
    printf("Call #%d: value = %d, temp = %d\n", ctr, n, temp);
    return n;
}

void q_6_6() {
    for (size_t i = 0; i != 10; ++i) {
        cout << count_num(i) << endl;
    }
}

int generate() {
    static int call_cnt = 0;
    return call_cnt++;
}

void q_6_7() {
    for (size_t i = 0; i != 10; ++i) {
        cout << i << ": " << generate() << endl;
    }
}

void reset(int *p) {
    *p = 0;
    p = 0;
}

void q_6_10(int *p, int *q) {
    int tmp;
    tmp = *p;
    *p = *q;
    *q = tmp;
}

bool is_shorter(const string &str1, const string &str2) {
    return str1.size() < str2.size();
}

string::size_type find_char(const string &str, char c, string::size_type &occurs) {
    auto ret = str.size();
    occurs = 0;
    for (decltype(ret) i = 0; i != str.size(); ++i) {
        if (str[i] == c) {
            if (ret == str.size()) {
                ret = i;  // 第一次出现位置
            }
            ++occurs;
        }
    }
    return ret;
}

void q_6_12(int &a, int &b) {
    int tmp;
    tmp = a;
    a = b;
    b =  tmp;
}

int q_6_14(int a, int b) {
    return a + b;
}

void print(const int *array) {
    cout << *array << endl;
}

void print_array(const int *beg, const int *end) {
    while (beg != end) {
        cout << *beg++ << " ";
    }
    cout << endl;
}
// void print(const int[]); // shows the intent that the function takes an array
// void print(const int[10]);

void test_array_parameter() {
    int i = 0, j[] = {100, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "==============array_parameter================\n";
    print(&i);
    print_array(begin(j), end(j));
}

bool q_6_17_capital(const string &s) {
    for (auto &ch: s) {
        if (isupper(ch)) return true;
    }
    return false;
}

void q_6_17_lowercase(string &s) {
    for (auto &ch: s) {
        if (isupper(ch))
            ch = tolower(ch);
    }
}


void q_6_18() {
    // bool compare(matrix &m1, matrix &m2);
    vector<int>::iterator change_val(int i, vector<int>::iterator);
}

void test_array_reference_parameter(int (&arr)[10]) {  // 指定array 大小
    for (auto i: arr) {
        cout << i << " ";
    }
    cout << endl;
}

// matrix points to the first element in an array whose elements are arrays of ten ints
// void print_multi_array(int (*matrix)[10], int row_size) {
void print_multi_array(int matrix[][10], int row_size) {
    for (int i = 0; i != row_size; ++i) {
        for (int j = 0; j != 10; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

}

int q_6_21(const int i, const int *const j) {
    return i > *j ? i : *j;
}

void q_6_22(int *&left, int *&right) {  // 修改指针的值，需要引用传递
    auto tmp = right;
    right = left;
    left = tmp;
}

int q_6_27(std::initializer_list<int> lst) {
    int ret = 0;
    for (const auto &item: lst) {
        ret += item;
    }
    return ret;
}

const std::string& manip() {
    static std::string ret; // 静态变量，生命周期为程序运行期间
    // transform ret in some way
    if (!ret.empty()) {
        return ret; // 返回静态变量的引用，安全
    } else {
        static const std::string empty_str = "Empty"; // 同样使用静态变量
        return empty_str;
    }
}

// 返回类型为引用的，是lvalue
char &get_val(string &str, string::size_type ix)
{
    return str[ix]; // get_val assumes the given index is valid
}

void test_reference_return_lvalue() {
    string s("a value");
    cout << s << endl;
    get_val(s, 0) = 'A';  // 像其它lvalue一样使用
    cout << s << endl;
}

vector<string> test_list_initializing_return(const string &str) {
    if (str.empty()) {
        return {};
    } else if (str == "actual") {
        return {"func", "abcv"};
    } else {
        return {"A", "BC"};
    }

}

bool str_subrange(const string &str1, const string &str2)
{
    // same sizes: return normal equality test
    if (str1.size() == str2.size())
        return str1 == str2; // ok: == returns bool
    // find the size of the smaller string; conditional operator, see § 4.7 (p. 151)
    auto size = (str1.size() < str2.size()) ? str1.size() : str2.size();
    // look at each element up to the size of the smaller string
    for (decltype(size) i = 0; i != size; ++i) {
        if (str1[i] != str2[i])
            return false; // error #1: no return value; compiler should detect this error
    }
    // error #2: control might flow off the end of the function without a return
    // the compiler might not detect this error
    //没有返回时 g++  warning: control reaches end of non-void function [-Wreturn-type]
    return true;
}

void test_return_pointer_to_array() {
    // 使用type alias
    using arrT = int[10];  // typedef int arrT[10];
    arrT* func1(int i);  // 返回一个 指向含有10个int的array 的指针

    // 不使用type alias
    int arr[10];
    int *p1[10];  // p1 含有10个指针的array
    int (*p2)[10] = &arr;  // p2 指针， 指向含有10个int的array

    // Type (*function(parameter_list))[dimension]
    int (*func2(int i))[10];

    // 使用 trailing return
    auto func3(int i) -> int(*)[10];
}

// 使用 decltype
int odd[] = {1, 3, 5, 7, 9};
int even[] = {2, 4, 6, 8, 10};
// decltype 推断指向的对象和odd相同， 手动添加* 表示返回的是一个指针
decltype(odd) *arrPtr(int i) {
    return (i % 2) ? &odd : &even;
}

void q_6_37() {
    // unction that returns a reference to an array
    // of ten strings
    string s[10];
    string (&func_1_1(int i))[10];


    using arrS = string[10];

    arrS& func_2_1(int i);

    auto func_2_2(int i) -> string(&)[10];

    decltype(s) &func_2_3(int i);
}

decltype(odd) &q_6_38(int i) {
    return (i % 2) ? odd : even;
}

typedef string::size_type sz;
string screen(sz ht = 24, sz wid = 80, char backgrnd = ' ') {
    string res = "";
    res += ht;
    res += " ";
    res += wid;
    res += " ";
    res += backgrnd;
    res += "\n";
    return res;
}

void test_default_arguments() {
    // 一旦某个形参被赋予了默认值，那么它之后的形参都必须要有默认值。

    ;
    string window;
    // 默认参数用于调用的尾部（最右侧）参数。
    window = screen('?');  // calls screen('?',80, '')
    cout << window << endl;
}

// 编译器会直接将函数的代码插入到调用处，而不是通过常规的函数调用指令（如call或ret）。这样可以避免函数调用的开销
// 仅对小函数使用：函数体应简单（如几行代码），避免循环或复杂逻辑。
// 高频调用优先：对循环内或关键路径上的函数内联效果更明显。
// 依赖编译器优化：现代编译器可能自动内联未标记的函数，可先测试性能再决定是否显式标记。
// 头文件放置：内联函数定义应放在头文件中，确保所有调用点可见。
inline const string &test_inline_shorter(const string &s1, const string &s2) {
    return (s1.size() < s2.size()) ? s1 : s2;
}


constexpr int new_size(){return 42;}

void test_constexpr_func() {
    // implicitly inline. 返回值和参数 都要是 literal type
    // replace a call to a constexpr function with its resulting value
    constexpr int func_size = new_size();
}

constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

constexpr int fib(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 1; i < n; ++i) {
        int next = a + b;
        a = b;
        b = next;
    }
    return b;
}

void print(){
#ifndef NDEBUG  // 非调试状态  g++ -D NDEBUG
    cerr << __func__ << "..." << endl;
#endif
}

void f()
{
    cout << "f()" << endl;
}

void f(int)
{
    cout << "f(int)" << endl;
}

void f(int, int)
{
    cout << "f(int, int)" << endl;
}

void f(double, double)
{
    cout << "f(double, double)" << endl;
}

void q_6_51() {
    // f(2.56, 42); // error: 'f' is ambiguous.
    f(42);
    f(42, 0);
    f(2.56, 3.14);

}

void test_pointer_to_function() {
    bool (*pf)(const string &, const string &);
    pf = is_shorter;  // 使用函数名时， 转为指针
    // pf = &is_shorter;
    bool b1 = pf("aaa", "cc");
    bool b2 = (*pf)("zzz", "sdc");
    bool b3 = is_shorter("hello", "hi");
}

// Func and Func2 have function type
typedef bool Func(const string&, const string&);
typedef decltype(is_shorter) Func2; // equivalent type
// FuncP and FuncP2 have pointer to function type
typedef bool(*FuncP)(const string&, const string&);
typedef decltype(is_shorter) *FuncP2; // equivalent type
using FuncP3 = decltype(&is_shorter);

void useBigger(const string &s1, const string &s2,
            // bool pf(const string &, const string &)
            // bool (*pf)(const string &, const string &)
            FuncP3 pf
) {
    bool b1 = pf(s1, s2);
    cout << "result :" << b1 << endl;
}

void test_func_pointer_parameters() {
    useBigger("hello", "world", is_shorter);
}


void test_return_pointer_to_func() {
    using F = int(int *, int);  // F is a function type,
    using PF = int (*) (int *, int);  // pointer type
    // 返回值不会自动转为指针，需要显式声明
    PF f1(int);
    F *f2(int);
    // 返回的函数的返回值类型 (*函数名(函数参数)) (返回的函数的参数类型)
    int (*f3(int)) (int *, int);
    auto f4(int) -> int (*)(int *, int);  // trailing return

    // 使用decltype
    string::size_type sumLength(const string&, const string&);
    string::size_type largerLength(const string&, const string&);
    // depending on the value of its string parameter,
    // getFcn returns a pointer to sumLength or to largerLength
    decltype(sumLength) *getFcn(const string &); // * 不能遗漏
}

int add(int a, int b) {return a + b;}
int subtract(int a, int b) {return a - b;}
int multiply(int a, int b) {return a * b;}
int divide(int a, int b) {return b == 0 ? 0 : a / b;}
void q_6_54() {
    int func(int, int);
    vector<decltype(func) *>vc;

    vc.push_back(add);
    vc.push_back(subtract);
    vc.push_back(multiply);
    vc.push_back(divide);
    for (auto f: vc) {
        cout << f(4, 2) << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    q_6_54();
    q_6_51();
    print();
    test_default_arguments();
    static_assert(factorial(5) == 120);  // 编译期计算
    static_assert(fib(10) == 55);  // 编译期计算
    for (const auto &s: test_list_initializing_return("actual") )
        cout << s << endl;
    test_reference_return_lvalue();
    int arg1 = 5;
    cout << "res: " << q_6_27({1, 2, 3, 4, arg1}) << endl;
    string input_str = "参数： ";
    for (int i = 1; i != argc; ++i) {
        input_str += string(argv[i]) + " ";
    }
    cout << input_str << endl;
    int a = 42, b = 21;
    cout << q_6_21(a, &b) << endl;
    auto left = &a;
    auto right = &b;
    q_6_22(left, right);
    cout << "left: " << *left << " right: " << *right << endl;


    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    test_array_reference_parameter(arr);
    int multi_arr[2][10] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15, 16, 17, 18, 19, 110}
    };
    print_multi_array(multi_arr, 2);
    string s = "AbcDefg";
    // q_6_17_lowercase(s);
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    cout << s << endl;
    cout << "含有大写字符？ " << std::boolalpha << q_6_17_capital("abcDef") << endl;
    test_array_parameter();
    cout << std::boolalpha << (120 == fact(5)) << endl;
    cout << abs(-12) << endl;
    int i = 42;
    reset(&i);
    cout << "i = " << i <<endl;
    int num_a = 100, num_b = 1;
    q_6_12(num_a, num_b);
    cout << "a: "<< num_a << " b: " << num_b << endl;
    q_6_7();

    string str1 = "c++ /mnt/d/Project/C_plus_plus_primer/ch06/chapt6.cpp -o chapt6";
    string str2 = "/usr/bin/ld: /tmp/cchCpC03.o: in function `q_6_4()':";
    cout << is_shorter(str1, str2) << endl;
    string::size_type occurs = 0;
    auto first_index = find_char(str1, 'o', occurs);
    cout << "第一次出现位置: " << first_index << " 出现次数： " << occurs << endl;

    int res = q_6_14(1, 2); // 非 const 的左值引用（T&）不能绑定到右值（临时对象）。
    // q_6_6();
    // q_6_4();

    // return -1;
    return EXIT_SUCCESS;
    // return EXIT_FAILURE;
}
