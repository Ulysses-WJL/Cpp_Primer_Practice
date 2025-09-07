#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "../ch08/Sales_Data.h"
#include "../ch13/String.h"
#include "Book.h"
#include "../ch12/StrBlob.h"
#include "../ch13/StrVec.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::string;
using std::map;
using std::sort;
using namespace std::placeholders;
using std::stable_sort;
using std::size_t;


void q_14_1() {
    /*
    * In what ways does an overloaded operator differ from a built-in operator?
In what ways are overloaded operators the same as the built-in operators?
不同：
1，可以直接调用重载运算符函数  operator+()
2. 重载运算符的要么是class的member，要么至少一个参数是对应类类型
3. 一些操作符保证操作数的求值顺序。这些操作符的重载版本不保留求值顺序和/或短路求值（short-circuit）  logical and/or: &&, ||
相同：
    重载的运算符和built-in的运算符右相同的优先级和结合性
     */
}

void q_14_2() {
    Sales_Data data1, data2;
    cin >> data1 >> data2;
    data1 += data2;
    cout << data1 << endl;
    Sales_Data data3 = data1 + data2;
    cout << data3 << endl;
}

void q_14_3() {
    /*
    * (a) "cobble" == "stone"    const char * 的 ==
    * (b) svec1[0] == svec2[0]   string的  ==
    * (c) svec1 == svec2   vector 的 ==
    * (d) svec1[0] == "stone"  string 的 ==
     */
}

void q_14_4() {
    /*
    * Explain how to decide whether the following should be class members:
    (a) %  Symmetric operators: non-member function
    (b) %=  修改了对象本身（that change the state of their object ） member function
    (c) ++  修改了对象本身 member function
    (d) ->  = [] () ->   must be defined as members
    (e) <<  Symmetric operators:  non-member
    (f) &&  Symmetric operators: non-member function
    (g) ==  Symmetric operators: non-member function
    (h) ()  = [] () ->   must be defined as members
     */
}

void q_14_7() {
    String s{"abcdef"};
    // cin >> s >> endl;
    cout << s << endl;
}

void q_14_15() {
    Book b1(0, "Book1", "Alice", "2024", 15);
    Book b2(0, "Book1", "Alice", "2024", 24);
    Book b3(1, "Book2", "Alice", "2024", 50);
    std::cout << std::boolalpha;
    cout << (b1 > b3) << endl;
    cout << (b1 == b2) << endl;
    cout << (b1 != b3) << endl;
    cout << (b1 + b2) << endl;
    Book b4(cin);
    std::cout << b4 << endl;

}

void q_14_23() {
    StrVec v;
    v = {"1", "2", "3"};
    cout << v;
}

void q_14_22() {
    Sales_Data s1("aa", 1, 2.5);
    s1 = "bbbb";
    cout << s1 << endl;
}

void q_14_26() {
    StrVec svec{"a", "b", "c"};
    const StrVec csvec = svec;
    svec[1] = 'a';
    cout << "svec: " << svec << endl;
    cout << "csvec: " <<  csvec << endl;
}

void q_14_27_28() {
    StrBlob sb1{"a", "b", "c"};
    StrBlob sb2 = sb1;
    sb2[1] = "z";
    if (sb2 > sb1) {
        for (StrBlobPtr iter = sb2.begin(); iter != sb2.end(); ++iter) {
            // iter.operator++(0); postfix
            // iter.operator++(); prefix
            cout << iter.deref() << " ";
        }
        cout << endl;
    }
    ConstStrBlobPtr iter(sb1);
    cout << "addition: " << (iter + 2).deref() << endl;
}

void q_14_30(){
    StrBlob sb1{"a", "b", "c"};
    StrBlob sb2 = sb1;
    sb2[1] = "z";
    if (sb2 > sb1) {
        for (StrBlobPtr iter = sb2.begin(); iter != sb2.end(); ++iter) {
            // iter.operator++(0); postfix
            // iter.operator++(); prefix
            cout << *iter << " ";
        }
        cout << endl;
    }
    StrBlobPtr p(sb1);
    *p = "good luck";  // sb1 的第一个element 变为
    cout << "0 : " << p->size() << endl;
    cout << "1 : " << (*(p+1)).size() << endl;
    cout << "2 : " << (p+2)->size() << endl;
}

struct absInt {
    int operator() (int val) const {
        return val < 0 ? -val : val;
    }
};

class PrintString {
public:
    PrintString(std::ostream& o = cout, char c = ' ') : os(o), sep(c) {};
    void operator()(const std::string& s) const {os << s << sep; }
    void operator()(const int s) const {os << s << sep; }
private:
    std::ostream &os;
    char sep;
};


void test_function_call() {
    int i = -44;
    absInt abs_func;
    cout << "abs : " << abs_func(i) << endl;

    vector<string> svec{"hello", "world", "come", "and", "have", "fun"};
    PrintString ps(cout, '_');
    ps("good luck");
    cout << endl;
    std::for_each(svec.begin(), svec.end(), ps);
    cout << endl;
    PrintString errors(std::cerr, '\n');
    errors("first");
    errors("second");
    errors("third");
    cout << endl;
}

// q_14_34

class IfThenElse {
public:
    int operator() (bool a, int first, int second) {
        return a ? first : second;
    }
};

void q_14_34(bool arg) {
    IfThenElse if_then_else;
    auto res = if_then_else(arg, 1, 2);
    cout << res << endl;
}

class ReadWrite {
public:
    ReadWrite(std::istream& is = cin): is(is) {}
    string operator()() const {
        string line;
        if (std::getline(is, line))
            return line;
        else
            return {};

    }
private:
    std::istream& is;
};

void q_14_35() {
    ReadWrite rd;
    cout << rd() << endl;
}

void q_14_36() {
    ReadWrite rd1;
    vector<string> svec;
    PrintString ps(cout, '_');
    for (string tmp; !(tmp = rd1()).empty();) svec.push_back(tmp);
    for_each(svec.begin(), svec.end(), ps);
    cout << endl;
}


class IsEqual {
public:
    IsEqual(int val = 0) : val(val) {}
    bool operator() (int a) const {return a == val;}
private:
    int val;
};

void q_14_37() {
    vector<int> ivec{1, 2, 3, 4, 5, 2, 4, 2, 16, 57};
    std::replace_if(ivec.begin(), ivec.end(), IsEqual(2), 222);
    PrintString ps(cout, '_');
    for_each(ivec.begin(), ivec.end(), ps);
    cout << endl;
}

class ShorterString {
public:
    bool operator() (const std::string& s1, const std::string& s2) const {
        return s1.size() < s2.size();
    }
};

class SizeComp {
public:
    SizeComp(size_t n): sz(n) {}
    bool operator()(const std::string& s1) const {return s1.size() >= sz;}  // 第一个大于sz的
private:
    size_t sz;  // captured
};

void test_lambda() {
    vector<string> svec{"hello", "world", "come", "and", "have", "fun"};
    std::stable_sort(svec.begin(), svec.end(), ShorterString());
    auto res = std::find_if(svec.begin(), svec.end(), SizeComp(4));
    std::for_each(res, svec.end(), PrintString(cout, ' '));
    cout << endl;
}

class Range {
public:
    Range(size_t l, size_t u) : upper_limit(u), lower_limit(l) {}
    bool operator() (const string& s) const {return lower_limit <= s.size() && s.size() <= upper_limit;}
    size_t get_upper_limit() const {return upper_limit;}
    size_t get_lower_limit() const {return lower_limit;}
private:
    size_t upper_limit;
    size_t lower_limit;
};

void q_14_38(std::ifstream& ifs) {
    vector<Range> ranges;
    vector<size_t> limits{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::map<size_t, size_t> counter;
    // 10个不同的区间
    for (auto upper: limits) {
        ranges.emplace_back(1, upper);
        counter[upper] = 0;
    }
    std::stringstream ss;
    string line, word;
    while (std::getline(ifs, line)) {
        cout << line << endl;
        ss.clear();
        ss.str(line);
        while (ss >> word) {
            for (auto range : ranges) {
                if (range(word)) {
                    ++counter[range.get_upper_limit()];
                }
            }
        }

    }
    for (auto &p: counter) {
        cout << "Length 1 ~ " << p.first << " , count: " << p.second << endl;
    }
}

void q_14_39(std::ifstream& ifs) {
    Range ranges[] = {{1, 9}, {10, 100}};
    std::map<std::pair<size_t, size_t>, size_t> counter;
    // 10个不同的区间
    std::stringstream ss;
    string line, word;
    while (std::getline(ifs, line)) {
        cout << line << endl;
        ss.clear();
        ss.str(line);
        while (ss >> word) {
            for (auto range : ranges) {
                if (range(word)) {
                    ++counter[std::make_pair(range.get_lower_limit(), range.get_upper_limit())];
                }
            }
        }

    }
    for (auto &p: counter) {
        cout << "Length  " << p.first.first  << " ~ " << p.first.second  <<  " , count: " << p.second << endl;
    }
}



void elim_dups(vector<string> &words) {
    sort(words.begin(), words.end());
    auto last_unique = unique(words.begin(), words.end());
    words.erase(last_unique, words.end());
}

void biggies_ch10(vector<string> &words, vector<string>::size_type sz) {
    elim_dups(words);
    // 按 长度排序
    stable_sort(words.begin(), words.end(),
        [](const string &s1, const string &s2){return s1.size() < s2.size();});
    // 找到第一个 长度大于sz的位置，后面的都大于sz
    // find_if 需要一个unary的 predicate 这里用普通函数需要2个参数完成
    auto wc = find_if(words.begin(), words.end(),
        [sz](const string &a){return a.size() >= sz;});
    // print
    for_each(wc, words.end(), [](const string &s){cout << s << " ";});
    cout << endl;
}

// q_14_40
class Predicate {
public:
    explicit Predicate(const size_t limit) : sz(limit) {}
    bool operator() (const string& s) const {return s.size() >= sz;}
private:
    size_t sz;
};


void biggies(vector<string> &words, vector<string>::size_type sz) {
    elim_dups(words);
    stable_sort(words.begin(), words.end(),ShorterString());
    auto wc = std::find_if(words.begin(), words.end(), Predicate(sz));
    for_each(wc, words.end(), PrintString(cout, ' '));
    cout << endl;
}


/*
*Arithmetic    Relational        Logical
plus<Type>        equal_to<Type>       logical_and<Type>
minus<Type>       not_equal_to<Type>   logical_or<Type>
multiplies<Type>  greater<Type>        logical_not<Type>
divides<Type>     greater_equal<Type>
modulus<Type>     less<Type>
negate<Type>      less_equal<Type>
 *
 */

void q_14_42() {
    vector<int> nums{100, 200, 10000, 2040, 143, 1023, 1034};
    // 类似 partial， _1 占位符表示check_size的第一个参数  变为unary
    auto res = std::count_if(nums.cbegin(), nums.cend(), std::bind(std::greater<int>(), _1, 1024));
    cout << "Greater than 1024: " << res << endl;
    vector<string> words{"pooh", "pooh", "fee", "tee", "pooh"};
    auto s = std::find_if(words.cbegin(), words.cend(), std::bind(std::not_equal_to<string>(), _1, "pooh"));
    std::for_each(s, words.cend(), PrintString(cout, ' '));
    cout << endl;
    std::transform(nums.begin(), nums.end(), nums.begin(), std::bind(std::multiplies<int>(), _1, 2));
    for_each(nums.cbegin(), nums.cend(), PrintString(cout, ' '));
    cout << endl;
}

// ordinary function
int add(int i, int j) { return i + j; }
// lambda, which generates an unnamed function-object class
auto mod = [](int i, int j) { return i % j; };
// function-object class
struct divide {
    int operator()(int denominator, int divisor) {
        return denominator / divisor;
    }
    static int call(int denominator, int divisor) {
        return denominator / divisor;
    }
};
void test_call_signature() {
    // int(int, int)
    std::map<string, int(*)(int, int)> binops;
    binops.insert({"+", add});
    binops.insert({"%", mod});
    // binops.insert({"/", divide()});
    binops.insert({"/", divide::call});  // 使用静态成员函数
    cout << "mod : " << binops["%"](10, 3) << endl;
}

void test_function_type() {
    // std::function<int(int, int)> f1 = add;
    // resolve the ambiguity, 保存函数的指针
    int (*fp)(int, int) = add;
    std::function<int(int, int)> f2 = divide();
    std::function<int(int, int)> f3 = mod;
    std::function<int(int, int)> f4 = [](int i, int j){return i * j;};
    cout << fp(4, 2) << endl;
    cout << f2(4, 2) << endl;
    cout << f3(4, 2) << endl;
    cout << f4(4, 2) << endl;
    std::map<string, std::function<int(int, int)>> binops = {
        {"+", fp},
        {"-", std::minus<int>()},
        {"*", f4},
        {"/", divide()},
        {"%", mod}

    };
    cout << "mod : " << binops["%"](10, 3) << endl;
    cout << "multiply :  " << binops["*"](10, 3) << endl;
    cout << "add : " << binops["+"](10, 3) << endl;
    cout << "divide : " << binops["/"](10, 3) << endl;
    cout << "minus : " << binops["-"](10, 3) << endl;
}


// Conversion Operators
class SmallInt {
public:
    // the compiler won’t automatically apply this conversion
    SmallInt(int i=0): val(i) {
        if (i < 0 || i > 255)
            throw std::out_of_range("Bad SmallInt value");
    }
    // operate type() const;
    explicit operator int() const {return val;}
private:
    size_t val;
};


void test_explicit_conversion() {
    SmallInt si = 3;
    // si + 3;  // error: implicit is conversion required, but operator int is explicit
    static_cast<int>(si) + 3;
}

void q_14_45() {
    Sales_Data s1("book1", 4, 2.5);
    cout << "book no: " << static_cast<string>(s1) << endl;
    cout << "avg price: " << static_cast<double>(s1) << endl;
}

int main(int argc, char *argv[]) {
    int a = 1 + 2;
    q_14_45();
    test_function_type();
    test_call_signature();
    q_14_42();
    vector<string> words{
        "1234","1234","1234","hi~", "alan", "alan", "cp"
    };
    biggies(words, 4);
    std::ifstream ifs("/mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch14/nums.txt");
    q_14_39(ifs);
    test_lambda();
    q_14_37();
    // q_14_36();
    // q_14_35();
    q_14_34(true);
    test_function_call();
    q_14_30();
    q_14_27_28();
    q_14_26();
    q_14_22();
    q_14_23();
    // q_14_15();
    // q_14_2();
    // q_14_7();
}
