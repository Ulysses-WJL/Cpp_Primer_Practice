#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <vector>
#include "Sales_item.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::vector;
using std::begin;
using std::end;

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
void q_1_20() {
    for (Sales_item item; std::cin >> item; std::cout << item << std::endl);
}

int e_1_5_2() {
    Sales_item item1, item2;
    std::cin >> item1 >> item2;
    // first check that item1 and item2 represent the same book
    if (item1.isbn() == item2.isbn()) {
        std::cout << item1 + item2 << std::endl;
        return 0; // indicate success
    } else {
        std::cerr << "Data must refer to same ISBN"
                  << std::endl;
        return -1; // indicate failure
    }
}

int q_1_23() {
    Sales_item total;
    if (std::cin >> total) {
        Sales_item item;
        while (std::cin >> item) {
            if (total.isbn() == item.isbn()) {
                total += item;
            } else {
                std::cout << total << std::endl;
                total = item;
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cerr << "No data ?" << std::endl;
        return -1;
    }
    return 0;
}

void test_convert() {
    unsigned u = 10, u2 = 42;
    std::cout << u2 - u << std::endl;
    std::cout << u - u2 << std::endl;
    int i = 10, i2 = 42;
    std::cout << i2 - i << std::endl;
    std::cout << i - i2 << std::endl;
    std::cout << i - u << std::endl;
    std::cout << u - i << std::endl;
}

void q_2_5() {
    double x = 10e-2, y = 1e-2;
    std::cout << "value : " << x << ", " << y << std::endl;
}

void q_2_8() {
    std::cout << 2 << "\r\n\tM" << std::endl;
}

void test_list_initialization() {
    int units_sold = 0;
    int units_sold_1 = {0};  // 构造初始化
    int units_sold_2{0};  // 列表初始化 防止窄化转换
    int units_sold_3(0);  // 括号初始化
    long double ld = 3.1415926536;
//    int a{ld}, b = {ld};  // error
    int c(ld), d = ld;  // OK, Narrowing conversion
}


int reused = 42;
void test_nested_scopes() {
    int unique = 0; // unique has block scope
// output #1: uses global reused; prints 42 0
    std::cout << reused << " " << unique << std::endl;
    int reused = 0; // new, local object named reused hides global reused
// output #2: uses local reused; prints 0 0
    std::cout << reused << " " << unique << std::endl;
// output #3: explicitly requests the global reused; prints 42 0
// ::scope operator，全局变量没有名称
    std::cout << ::reused << " " << unique << std::endl;
}


void tes_reference() {
    //引用不是对象 A reference defines an alternative name for an object
    // a reference must be initialized
    // 不能绑定到 literal
    int i, &ri = i;  // 类型需要一致,
    i = 5;
    ri = 10;
    std::cout << i << " " << ri << std::endl;
}

void test_pointers() {
    // A pointer holds the address of another object.
    int ival = 42;
    int *p = &ival;  // address-of operator: & 取地址 操作
    std::cout << *p << std::endl;  // * yields the object to which p points;
    *p = 0;  // * dereference operator  去引用 操作
    std::cout << *p << " " << ival << std::endl;
}

void test_null_pointers() {
    int *p1 = nullptr;  // c++ 11 表示空指针  更安全, 可以转为任意其他指针类型
    int *p2 = 0;
    int *p3 = NULL;

}

void test_void_pointer() {
    double obj = 3.14, *pd = &obj;
    void *pv = &obj;
    pv = pd;

}

void  q_2_18() {
    int num = 24, count = 0, *pi = &num;
    pi = &count;
    *pi = 1;
    std::cout << "count : " << count << std::endl;
}

void pointer_to_pointer() {
    int ival = 1024;
    int *pi = &ival;
    int **ppi = &pi;
    std::cout << "The value of ival\n"
         << "direct value: " << ival << "\n"
         << "indirect value: " << *pi << "\n"
         << "doubly indirect value: " << **ppi
         << std::endl;
}

void reference_to_pointer() {
    int i = 42;
    int *p;
    int *&r = p;  // read the definition right to left.

    r = &i;  // p = &i
    *r = 0;  // i = 0
}

void test_const() {
    // const 类型必须初始化
//    const int ci = 1024;
//    const int &r1 = ci;
//    r1 = 42;  // error: r1 is a reference to const
//    int &r2 = ci;  // error: nonconst reference to a const object

//  普通引用不能绑定到临时对象。只有const引用可以这样做，因为它们可以延长临时对象的生命周期。
    int i = 1024;
    int &r = i;
    const int &r1 = i; // we can bind a const int& to a plain int object
    const int &r2 = 42; // ok: r2 is a reference to const
    const int &r3 = r1 * 2; // ok: r3 is a reference to const
//    int &r4 = r * 2; // error: r4 is a plain, nonconst reference  r * 2的结果是一个临时对象

// 无法通过r1修改i，但能直接修改i
    i = 512;
    std::cout << "i: " << i << " r1: " << r1 << std::endl;

    const double pi = 3.14;
//    double *ptr = &pi;  // error: ptr is a plain pointer
    const double *cptr = &pi;  // cptr point to a double that is const
//    *cptr = 3.1415;  // error: cannot assign to *cptr

    double dval = 4.0;
    cptr = &dval;  // cptr 指向另一个double变量
//    *cptr = 5.0
    dval = 5.0;
    std::cout << "dval: " << dval << " *cptr: " << *cptr << std::endl;
//    const pointer
    int errNumb = 0;
    int *const curErr = &errNumb;  // curErr will always point to errNumb
    const double *const pip = &pi;  // pip is a const pointer to a const object
    std::cout << "pi: " << pi << " *pip: " << *pip << std::endl;

    // change errNumb by curErr
    *curErr = 1;
    cout << "errNumb: " << errNumb << endl;
}

void q_2_28() {
//    int i, *const cp;       // 不合法, const 指针必须初始化
//    int *p1, *const p2;     // 不合法, const 指针必须初始化
//    const int ic, &r = ic;  // 不合法, const int 必须初始化
//    const int *const p3;    // 不合法, const 指针必须初始化
    const int *p;           // 合法. 一个指针，指向 const int
}

void q_2_27() {
//    int i2 = 1;
//    int i = -1, &r = 0;         // 不合法, r 必须引用一个对象
//    int *const p2 = &i2;        // 合法，常量指针
//    const int i = -1, &r = 0;   // 合法
//    const int *const p3 = &i2;  // 合法
//    const int *p1 = &i2;        // 合法
//    const int &const r2;        // 不合法, r2 是引用, 引用自带顶层 const, 第二个const写法多余但合法, 但引用需要初始化.
//    const int i2 = i, &r = i;   // 合法
}

void test_top_level_const() {
//    Top-Level Const用于声明常量变量，确保其值在初始化后不可更改。 pointer itself is a const.
//    Low-Level Const用于修饰指针或引用所指向的对象，确保这些对象的值不可被修改，
//    但指针或引用本身可以重新指向其他对象。 a pointer can point to a const object,
    int i = 0;
    int *const p1 = &i; // we can’t change the value of p1; const is top-level
    const int ci = 42; // we cannot change ci; const is top-level
    const int *p2 = &ci; // we can change p2; const is low-level
    const int *const p3 = p2; // right-most const is top-level, left-most is not
    const int &r = ci; // const in reference types is always low-level

    // When we copy an object, top-level consts are ignored, low-level const 必须相同
    i = ci; // ok: copying the value of ci; top-level const in ci is ignored
    p2 = p3; // ok: pointed-to type matches; top-level const in p3 is ignored

//    int *p = p3; // error: p3 has a low-level const but p doesn’t
    p2 = p3; // ok: p2 has the same low-level const qualification as p3
    p2 = &i; // ok: we can convert int* to const int*
//    int &r = ci; // error: can’t bind an ordinary int& to a const int object
    const int &r2 = i; // ok: can bind const int& to plain int
}

void q_2_31() {
    const int i = 1024;
    const int v2 = 0; int v1 = v2;
    int *p1 = &v1, &r1 = v1;
    const int *p2 = &v2, *const p3 = &i, &r2 = v2;
    // v2 top-level, p2 low-level, p3 both, r2 low-level
    r1 = v2; // 合法, 顶层const在拷贝时不受影响
//    p1 = p2; // 不合法, p2 是底层const，如果要拷贝必须要求 p1 也是底层const
    p2 = p1; // 合法, int* 可以转换成const int*
//    p1 = p3; // 不合法, p3 是一个底层const，p1 不是
    p2 = p3; // 合法, p2 和 p3 都是底层const，拷贝时忽略掉顶层const
}

int get_size() {
    return 1024;
}

constexpr int size() {
    return 1024;
}

void test_constexpr() {
    // constant expression: 在 compile 时就确定了 cannot change
    const int max_files = 20; // max_files is a constant expression
    const int limit = max_files + 1; // limit is a constant expression
    int staff_size = 27; // staff_size is not a constant expression
    const int sz = get_size(); // sz is not a constant expression

    // 在编译阶段完成更多的计算和验证，减少运行时的开销，提升程序的整体效率
    constexpr int mf = 20; // 20 is a constant expression
    constexpr int limit_1 = mf + 1; // mf + 1 is a constant expression
    constexpr int sz_1 = size(); // ok only if size is a constexpr function

    const int *p = nullptr;  // p is a pointer to a const int
    constexpr int *q = nullptr;  // q is a const pointer to int
    int null = 0, *p1 = &null;
}

constexpr int *np = nullptr; // np is a constant pointer to int that is null
int j = 0;
constexpr int i = 42; // type of i is const int
// i and j must be defined outside any function
constexpr const int *p = &i; // p is a constant pointer to the const int i
constexpr int *p1 = &j; // p1 is a constant pointer to the int j


void test_type_alias() {
    //traditionally
    typedef double wages;
    typedef wages base, *p; // base is a synonym for double, p for double*
    // C++11 new standard
    using SI = Sales_item;
    wages hourly, weekly;
    SI item;

    using FuncPtr = void (*)(int);  // 指向函数的指针

    typedef char *pstring;  // pstring: char*

    // const 修饰的是 pstring（即 char*），因此 cstr 是一个 指向 char 的常量指针
    const pstring cstr = 0;  // cstr is a constant pointer to char :  const (char *) cstr = 0;

    // ps 是一个 指向 const char* 的指针。0
    const pstring *ps;   // ps is a pointer to a constant pointer to char

//    const char *cstr = 0;  // wrong interpretation of const pstring cstr
}

void test_auto() {
    // auto： compiler 推断类型，必须初始化
    int val1 = 0, val2 = 2;
    auto item = val1 + val2;
    auto i = 0, *p = &i;
//    auto sz = 0, pi = 3.14;  // error: inconsistent types for sz and pi
// const, and auto ：auto会忽略top-level const(声明常量变量), low-level const 保留 （修饰指针， 引用）
    int &r = i;
    auto a = r;  // a: int
    const int ci = i, &cr = ci;

    auto b = ci; // b is an int (top-level const in ci is dropped)
    auto c = cr; // c is an int (cr is an alias for ci whose const is top-level)
    auto d = &i; // d is an int* (& of an int object is int*)
    auto e = &ci; // e is const int* (& of a const object is low-level const)

    const auto f = ci;  // 显示声明 top-level

    auto &g = ci; // g is a const int& that is bound to ci
//    auto &h = 42; // error: we can’t bind a plain reference to a literal
    const auto &j = 42; // ok: we can bind a const reference to a literal

    auto k = ci, &l = i; // k is int; l is int&
    auto &m = ci, *p2 = &ci; // m is a const int&; p is a pointer to const int
//    auto &n = i, *p2 = &ci;  //  error: type deduced fromi is int; type deduced from &ci is const int
}

void q_2_35() {
    const int i = 42;
    auto j = i;
    const auto &k = i;
    auto *p = &i;
    const auto j2 =i, &k2 = i;
}

void test_decltype() {
    const int ci = 0, &cj = ci;
    decltype(ci) x = 0;
    // 包括其顶层 const 和引用特性
    decltype(cj) y = x;
//    decltype(cj) z;  // error: z is a reference and must be initialized
    int i = 42, *p = &i, &r = i;
    decltype(r + 0) b;
//    decltype(*p) c;  // error: c is int& and must be initialized
    // 处理左值和右值的类型差异
    int z = 0;
    decltype(z) a = z;  //  int（z 是左值，但 decltype 不保留左值特性）
    decltype((z)) aa = z;  // int&（表达式 (z) 是左值，所以推导为引用类型）
    decltype(5) c = 5;    // c 的类型是 int（5 是右值，不带引用）

    /*
     *  lvalue vs rvalue
        变量、引用、指针、成员变量：通常是左值。
        字面量、临时对象、表达式结果：通常是右值。
        函数返回临时对象：返回的是右值（除非返回左值引用）。
    */

}

void q_2_36() {
    int a = 3, b = 4;
    decltype(a) c = a;  // c是int 值为4
    decltype((b)) d = a;  // d int& 对a 的引用
    ++c;
    ++d;
    cout << "a: " << a << " b : " << c << " d : "  << d << endl;
}

void test_struct() {
    struct Sales_data {
        std::string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
    };
    Sales_data data1;
    double price = 0.0;
    cin >> data1.bookNo >> data1.units_sold >> price;
    data1.revenue = price * data1.units_sold;
    cout << "revenue : " << data1.revenue << endl;
}

void test_string() {
    string s1;
    string s2 = s1;
    string s3 = "hello";
    string s4(10, 'c');
    string s5 = "hi";  // copy initialization
    string s6("hello"); // direct initialization
    string s7 = string(10, 'a');  //  copy initialization
    cout << "s4: " << s4 << " s6: " << s6 << endl;
    cout << s7.size() << endl;
    cout << s2.empty() << endl;
    cout << s4 + s7 << endl;

//    string line;
//    while (getline(cin, line)) {
//        if (!line.empty()) {
//            cout << line << endl;
//        } else {
//            break;
//        }
//    }
//    auto len = line.size();

    string str = "Hello";
    string phrase = "Hello World";
    string slang = "Hiya";
    cout << (slang > phrase) << endl;

    string a = "hello";
    string b = "world";
    string c = a + b;
    string d = a + ", " + b + "\n";
    // + 左右 至少要有一个string类型 ，string literal 是const char[N]
//    string e = "hello" + ", " + c;  // error: can’t add string literals
}

void test_string_op() {
    string str("some string !!!");
    decltype(str.size()) punc_cnt = 0;
    for (auto c: str) {
        cout << c << endl;
        if (ispunct(c)) {
            ++punc_cnt;
        }
    }
    for (auto &c : str) {
        if (islower(c))
            c = toupper(c);  // c is a reference, so the assignment changes the char in s
    }
    string s2("abc efg");
    if (!s2.empty())
        s2[0] = toupper(s2[0]);
    cout << punc_cnt
         << " punctuation characters in " << str << endl;
    cout << s2 << endl;
    for (decltype(s2.size()) index = 0; index != s2.size() && !isspace(s2[index]); ++index)
        s2[index] = toupper(s2[index]);
    cout << s2 << endl;
}

void test_vector() {
    vector<int> ivec(10, -1);
    vector<int> ivec2(ivec);
    vector<int> ivec3 = ivec;
    vector<string> svec(10, "Hi!");
    vector<string> s1{"a", "b", "chat"};  // list initialization

    vector<int> ivec_0(10); // ten elements, each initialized to 0
    vector<string> svec_0(10); // ten elements, each an empty string

    // {} list initialize； 括号size (10, 1) 10个1  compiler先看是否为list initialize
    vector<int> v1(10); // v1 has ten elements with value 0
    vector<int> v2{10}; // v2 has one element with value 10
    vector<int> v3(10, 1); // v3 has ten elements with value 1
    vector<int> v4{10, 1}; // v4 has two elements with values 10 and 1

    for (int i = 0; i != 100; ++i) {
        ivec.push_back(i);
    }
    cout << "size if ivec: " <<  ivec.size() << endl;
}

void test_q_3_14() {
    vector<int> ivec;
    int tmp = 0;
    while (cin >> tmp) {
        ivec.push_back(tmp);
    }
    cout << ivec.size() << endl;
}

void q_3_17() {
    vector<string> svec;
    string s;
    while (cin >> s) {
        svec.push_back(s);
    }
    for (auto &str: svec) {
        for (auto &c : str) {
            c = toupper(c);
        }
        cout << str << endl;
    }
}

void q_3_20() {
    vector<int> ivec;
    int i;
    while (cin >> i)
    {
        ivec.push_back(i);
    }

    for (int i = 0; i < ivec.size() - 1; ++i)
    {
        cout << ivec[i] + ivec[i + 1] << endl;
    }

    //---------------------------------
    cout << "---------------------------------" << endl;
    int start = 0, end = ivec.size() - 1;
    while (start < end) {
        cout << ivec[start] + ivec[end] << endl;
        ++start;
        ++end;
    }
}

void test_iterator() {
    string str = "abc def";
    for (auto it = str.begin(); it != str.end() && !isspace(*it); ++it) {
        *it = toupper(*it);
    }
    cout << str << endl;
    for (auto cit : str) {
        cout << cit << endl;
    }
    vector<string> svec{"abc", "gogo", "", "test"};
    for (auto it = svec.cbegin(); it != svec.cend() && !it->empty(); ++it) {
        // it->empty() (*it).empty()  dereference and member access
        cout << *it << endl;
    }
}

// auto binary_search(int sought, vector<int>& vec) {
//     auto beg = vec.begin(), end = vec.end();
//     auto mid = beg + (end - beg) / 2;
//     while (mid != end && *mid != sought) {
//         if (sought < *mid)
//             end = mid;
//         else
//             beg = mid + 1;
//         mid = beg + (end - beg) / 2;
//     }
//     return mid - beg;
// }

void q_3_24() {
    vector<int> ivec;
    int i;
    while (cin >> i)
    {
        ivec.push_back(i);
    }

    for (auto it = ivec.begin(); it != ivec.end() - 1; ++it)
    {
        cout << *it + *(it + 1) << endl;
    }

    //---------------------------------
    cout << "---------------------------------" << endl;

    auto it1 = ivec.begin();
    auto it2 = ivec.end() - 1;
    while (it1 < it2)
    {
        cout << *it1 + *it2 << endl;
        ++it1;
        --it2;
    }
}

void test_array () {
    // 固定大小， 编译阶段确定大小
    unsigned cnt = 42;
    constexpr unsigned sz = 42;
    // 全局或静态数组在定义时如果没有显式初始化，会被默认初始化
    // 局部数组 栈上分配，如果没有初始化的话，
    // 默认类型里面的值是未初始化的，也就是垃圾值； 类类型，被默认构造
    int arr[10]; // array of ten ints
    int *parr[sz]; // array of 42 pointers to int
    // 编译器的VLA扩展 支持可变长度数组
    //  g++ -std=c++11 -pedantic -Werror your_code.cpp -o
    string bad[cnt]; // error: cnt is not a constant expression
    string strs[get_size()]; // ok if get_size is constexpr, error otherwise
    bad[0] = "test";
    cout << bad[0] << endl;
    int a1[] = {1, 2, 3};  // 长度默认3
    int a2[5] = {0, 1, 2}; // {0, 1, 2, 0, 0}
    string a3[3] = {"hi", "hello"};
    for (int i = 0; i != a3->size(); ++i) {
        // a[i] = *(a+i) = *(i+a) = i[a]
        cout << a3[i] << "  " << *(a3 + i) << endl;
    }
    for (auto &s: a3) {
        cout << s << endl;
    }

    // character arrays 结尾默认加 null结尾
    char c1[] = {'c', '+', '+'}; // list initialization, no null
    char c2[] = {'c', '+', '+', '\0'}; // list initialization, explicit null
    char c3[] = "C++"; // null terminator added automatically
    // const char c4[6] = "Daniel"; // error: no space for the null!
    // char c4[] = c1;  // error: cannot initialize one array with another
    // c2 = c1;  // array 无法赋值

    // Complicated Array Declarations: right-to-left , inside out
    int *ptrs[10];  // ptrs: 10个指针的array， 指针指向int类型
    int (*Parray)[10] = &arr;  // Parray是一个指针， 指向一个包含10个int的array：，右边要取对应arr地址
    int (&arrRef)[10] = arr;   // arrRef是一个引用，是一个包含10个int的array的引用
    int *(&arry)[10] = ptrs; // arry is a reference to an array of ten pointers
}

void q_3_31() {
    constexpr size_t size = 10;
    int arr[size];
    for (int i = 0; i != size; ++i) {
        arr[i] = i;
    }

    vector<int> vec(10);
    for (int i = 0; i != size; ++i) {
        vec[i] = arr[i];
    }

}

void test_pointers_arrays () {
    // 对数组的操作实质是对指针的操作
    string nums[] = {"one", "two", "three"};
    string *p = &nums[0];
    string *p2 = nums;
    cout << "p: " << *p << " p2: " << *p2 << endl;

    int ia[] = {0, 1, 2, 3, 4, 5, -1, 0, -2};
    auto ia2(ia);  // ia2 is an int* that points to the first element in ia
    auto ia3(&ia[0]);
    cout << "ia2: " << *ia2 << " ia3: " << *ia3  << endl;

    int arr[] = {0,1,2,3,4,5,6,7,8,9};
    int *p3 = arr; // p points to the first element in arr
    ++p3; // p points to arr[1]
    cout << "value of *p: " << *p3 << endl;

    int *e = &arr[10];  // nonexistent   off-the-end pointer
    for (int *b = arr; b != e; ++b)
        cout << *b << endl;

    // begin 和 end 获取 array的起始位置和结束位置
    int *first = begin(ia);
    int *last = end(ia);
    while (first != last && *first >= 0)
        ++first;
    if (first != last)
        cout << *first << endl;
    auto n = last - first;

    int i = ia[2];
    int *p4 = ia;
    i = *(p4 + 2);

    int *p5 = &ia[2];
    int j = p5[1];  // *(p5+1) ia[3]
    int k = p5[-2];  // ia[0]  下标可以为负数

    cout << "j: " << j << " k: " << k << endl;

    // 使用array 初始化vector
    int int_arr[] = {0, 1, 2, 3, 4, 5, 6};
    vector<int> ivec(begin(int_arr), end(int_arr));
    for (auto val: ivec) {
        cout << val << " ";
    }
    cout << endl;

    vector<int> subVec(int_arr + 1, int_arr + 4);
    for (auto val: subVec) {
        cout << val << " ";
    }
    cout << endl;

}

bool compare(int *pb, int *pe, int *qb, int *qe) {
    if ((pe - pb)  != (qe - qb)) {
        return false;
    } else {
        for (;pb != pe && qb != qe; ++qb, ++pb)
            if (*pb != *qb) return false;
    }

    return true;
}

void q_3_36() {
    int arr1[3] = {1, 2, 3};
    int arr2[3] = {1, 2, 4};

    vector<int> ivec1(10, 1);
    vector<int> ivec2(8, 2);

    if (ivec1 == ivec2)
        cout << "vector 相同" << endl;
    else
        cout << "vector 不同" <<endl;

    bool res = compare(begin(arr1), end(arr1), begin(arr2), end(arr2));
    if (res)
        cout << "相同" << endl;
    else
        cout << "不同" << endl;

}

void q_3_39() {
    string s1("Mooophy"), s2("Pezy");
    if (s1 == s2)
        cout << "same string." << endl;
    else if (s1 > s2)
        cout << "Mooophy > Pezy" << endl;
    else
        cout << "Mooophy < Pezy" << endl;

    cout << "=========" << endl;

    // use C-Style character strings.
    const char* cs1 = "Wangyue";
    const char* cs2 = "Pezy";
    auto result = strcmp(cs1, cs2);
    if (result == 0)
        cout << "same string." << endl;
    else if (result < 0)
        cout << "Wangyue < Pezy" << endl;
    else
        cout << "Wangyue > Pezy" << endl;
}

void q_3_40() {
    const char s1[] = "hello";
    const char s2[] = "world!";

    constexpr size_t new_size = strlen(s1) + strlen(" ") + strlen(s2) + 1;
    char s3[new_size];
    strcpy(s3, s1);
    strcat(s3, " ");
    strcat(s3, s2);
    cout << "result: " << s3 <<endl;
}

void test_multi_dimension_array() {
    int ia[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11}
    };
    // 等价于
    int ia1[3][4] = {0,1,2,3,4,5,6,7,8,9,10,11};
    int ia2[3][4] = {
        {0},
        {4},
        {8}
    };  // 只初始化 每个row的第0个
    int (&row)[4] = ia[1]; // row是引用， 对长度为4的array, 数据类型为int 的引用

    constexpr size_t row_size = 3, col_size = 4;
    int multi_arr[row_size][col_size];
    for (size_t i=0; i != row_size; ++i) {
        for (size_t j=0; j != col_size; ++j) {
            multi_arr[i][j] = i * row_size + j;
        }
    }

    size_t cnt = 0;
    int new_arr[row_size][col_size];
    for (auto &row: new_arr) {
        for (auto &col: row) {
            col = cnt;
            ++cnt;
        }
    }

    // for (auto row: new_arr) {  // row 被转为 int* 无法直接遍历
    //     for (auto col: row) {
    //         cout << col << " ";
    //     }
    //     cout << endl;
    // }
    for (auto &row: new_arr) {  // 使用引用保持 row 的数组类型
        for (auto col: row) {
            cout << col << " ";
        }
        cout << endl;
    }

}


int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    // >>和<<都是 left-hand operand， 返回的是输入留和输出流本身
    auto lang = "C++";
    int _;
    std::cout << "Hello and welcome to " << lang << "!\n";
    int num = 10;
    vector<int> vec{1, 2, 3, 10, 11, 22, 34};
    // auto index = binary_search(num, vec);
    // cout << "index of 10 : " << index << endl;
    test_multi_dimension_array();
    q_3_40();
    q_3_39();
    q_3_36();
    test_pointers_arrays();
    test_array();
    test_iterator();
    // q_3_24();
//    q_3_20();
//    q_3_17();
//    test_q_3_14();
    test_vector();
    test_string_op();
    test_string();
//    test_struct();
    q_2_36();
    test_const();
    pointer_to_pointer();
    q_2_18();
    test_pointers();
    tes_reference();
    test_nested_scopes();
    test_convert();
    q_2_5();
    q_2_8();
//    q_1_20();
//    e_1_5_2();
//    q_1_23();
//    std::cout << "Enter two numbers: " << std::endl; // std::endl 会flushing the buffer
//    int start = 0, end = 0;
//    std::cin >> start >> end;
//    std::cout << "The product of " << start  << " and " << end
//              << " is " << start * end << std::endl;
//    if (start < end) {
//        for (int i = start; i <= end; i++) {
//            std::cout << i << std::endl;
//        }
//    }
//    int sum = 0, val = 0;
//    std::cout << "input the num" << std::endl;
//    while (std::cin >> val) {
//        sum += val;
//    }
//    std::cout << "sum is : " << sum << std::endl;


    std::cout << "/*";
    std::cout << "*/";
    std::cout << /* "*/" */";
    std::cout << /* "*/" /* "/*" */;
    std::cout << "\n";
//    int sum = 0, val = 50;
//    while (val <= 100) {
//        sum += val;
//        val += 1;
//    }
//    std::cout << "sum of 50~100 is " << sum << std::endl;

    for (int i = 1; i <= 5; ++i) {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code.
        // We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
        // breakpoint for you, but you can always add more by pressing
        // <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return -1;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.
