#include <algorithm>
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <list>
#include <numeric>
#include <bitset>
#include <iomanip>
#include <format>
// #include <print>
#include <regex>
#include <random>
#include "../ch08/Sales_Data.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::tuple;
using std::vector;
using std::list;
using std::get;
using std::bitset;

void test_tuple() {
    tuple<size_t, size_t, size_t> threeD;
    tuple<string, vector<string>, int , list<int>> someVal("hello", {"1", "2"}, 23, {1, 2, 3});
    tuple<size_t, size_t, size_t> threeD2 = {1,2,3};
    cout << std::get<0>(threeD2) << endl;

    auto item = std::make_tuple("2", 4, 5.1);  // 类似make_pair
    auto item2  = tuple{1, "2", 3.1};
    auto item3  = std::make_tuple();
    get<2>(item2) *= 2.5;
    auto [a, b, c] = item2;  // 解包
    using trans = decltype(item2);

    // tuple 的成员数量
    // size_t sz = std::tuple_size<trans>::value;
    size_t sz = std::tuple_size_v<trans>;
    cout << sz << endl;

    // tuple member 类型
    // cnt类型是 item2 第二个元素的类型 string
    // std::tuple_element<1, trans>::type cnt = std::get<1>(item2);
    std::tuple_element_t<1, trans> cnt = std::get<1>(item2);

    tuple<int, double> t1{1, 2.1};
    tuple<int, double> t2{2, 3.1};
    bool res = (t1 < t2);
    cout << std::boolalpha << res << endl;
}

void q_17_1_2() {
    tuple<int, int, int> t1{10, 20, 30};
    tuple<string, vector<string>, std::pair<string, int>> t2;
}

// 使用tuple 返回多个结果

using matches = tuple<
    vector<Sales_Data>::size_type,
    vector<Sales_Data>::const_iterator,
    vector<Sales_Data>::const_iterator>;

bool compareIsbn(const Sales_Data &lhs, const Sales_Data &rhs) {
    return lhs.isbn() < rhs.isbn();
}

vector<matches> findBook(const vector<vector<Sales_Data>> &files, const string &book) {
    vector<matches> ret;
    for (auto it = files.begin(); it != files.end(); ++it) {
        // find the range of Sales_data that have the same ISBN  二分查找插入的位置
        auto found = std::equal_range(it->begin(), it->end(), book, compareIsbn);
        if (found.first != found.second) {  // 有相同isbn的存在
            // ret.push_back(std::make_tuple(it-files.cbegin(), found.first, found.second));
            ret.emplace_back(it-files.cbegin(), found.first, found.second);
        }
    }
    return ret;
}

void reportResults(std::istream &in, std::ostream &os,
                   const vector<vector<Sales_Data>> &files){
    string s;
    while (in >> s) {
        auto trans = findBook(files, s);
        if (trans.empty()) {
            cout << s << " not found in any stores" << endl;
            continue; // get the next book to look for
        }
        for (const auto &store: trans) {
            // get<n> returns the specified member from the tuple in store
            os << "store " << get<0>(store) << " sales: "
                << std::accumulate(get<1>(store), get<2>(store), Sales_Data(s))
                << endl;
        }
    }

}

void q_17_4() {
    vector<Sales_Data> file, file2;
    file.emplace_back("book1", 25, 0.5);
    file.emplace_back("book2", 25, 0.5);
    file.emplace_back("book3", 25, 0.5);
    file.emplace_back("book4", 25, 0.5);

    file2.emplace_back("book1", 25, 0.5);
    file2.emplace_back("book2", 25, 0.5);
    file2.emplace_back("book5", 25, 0.5);
    const vector<vector<Sales_Data>> files{file, file2};
    reportResults(cin, cout, files);
}

void test_bitset() {
    std::bitset<32> bitvec(1U << 3);  //  0b1000 unsigned long long

    // bitvec1 is smaller than the initializer; high-order bits from the initializer are discarded
    bitset<13> bitvec1(0xbeef); // bits are 1111011101111
    // bitvec2 is larger than the initializer; high-order bits in bitvec2 are set to zero
    bitset<20> bitvec2(0xbeef); // bits are 00001011111011101111
    // on machines with 64-bit long long 0ULL is 64 bits of 0, so ~0ULL is 64 ones
    bitset<128> bitvec3(~0ULL); // bits 0...63 are one;63...127 are zero

    // 使用string 初始化
    bitset<32> bitvec4("1100");  // bit2, bit3 为1， 其余0

    string str("1111111000000011001101");
    bitset<32> bitvec5(str, 5, 4); // four bits starting at str[5], 1100
    bitset<32> bitvec6(str, str.size()-4); // use the last four characters
}

void q_17_9() {
    bitset<32> bitvec(32);  // 32 -> 0x20 -> 0b0010 0000 , bit5 为1， 其余0
    bitset<32> bv(1010101);  // 1010101 -> 0xf69b5 -> 0b11110110100110110101

    // 根据输入的string 转 bitset
    string bstr;
    cin >> bstr;
    bitset<8> bv2(bstr);
}

void test_bitset_operation() {
    bitset<32> bitvec(1U); // 32 bits; low-order bit is 1, remaining bits are 0
    bool is_set = bitvec.any(); // true, one bit is set
    bool is_not_set = bitvec.none(); // false, one bit is set
    bool all_set = bitvec.all(); // false, only one bit is set
    size_t onBits = bitvec.count(); // returns 1
    size_t sz = bitvec.size(); // returns 32
    bitvec.flip(); // reverses the value of all the bits in bitvec
    bitvec.reset(); // sets all the bits to 0
    bitvec.set(); // sets all the bits to 1
    bitvec.flip(0);  // 翻转first bit
    bitvec.set(bitvec.size() - 1);  // last bit 设置 1 true
    bitvec.set(0, false);  // first bit 设置 0 false
    bitvec.reset(5);  // 第5 设置false
    bitvec.test(0);  // first bit 是否为true
    unsigned long ulong = bitvec.to_ulong();
    cout << "ulong: " << ulong << endl;

    bool status;
    // version using bitwise operators
    unsigned long quizA = 0; // this value is used as a collection of bits
    quizA |= 1UL << 27;
    // indicate student number 27 passed
    status = quizA & (1UL << 27); // check how student number 27 did
    quizA &= ~(1UL << 27); // student number 27 failed
    // equivalent actions using the bitset library
    bitset<30> quizB; // allocate one bit per student; all bits initialized to 0
    quizB.set(27);// indicate student number 27 passed
    status = quizB[27]; // check how student number 27 did
    quizB.reset(27); // student number 27 failed
}

void q_17_10() {
    vector<int> ivec = {1, 2, 3, 5, 8, 13, 21};
    bitset<32> bitvec1;
    for (auto const &i : ivec) {
        bitvec1.set(i);
    }
    bitset<32> bitvec2;
    for (unsigned int i = 0; i < 32; ++i) {
        bitvec2[i] = bitvec1.test(i);
    }
    cout << bitvec1 << endl;
    cout << bitvec2 << endl;
}

template <size_t N>
class Quiz {
public:
    Quiz() = default;
    Quiz(string &s): bitquiz(s) {};
    ~Quiz() = default;
    //generate grade
    template<std::size_t M>
    friend std::size_t grade(Quiz<M> const &stu, Quiz<M> const &ans);

    //print
    template<std::size_t M>
    friend std::ostream &operator<<(std::ostream &os, Quiz<M> const &q);

    //update bitset
    void update(std::pair<std::size_t, bool> p) {
        bitquiz[p.first] = p.second;
    }

private:
    bitset<N> bitquiz;
};

template<std::size_t M>
std::ostream& operator<<(std::ostream& os, Quiz<M> const& quiz)
{
    os << quiz.bitquiz;
    return os;
}

template<std::size_t M>
std::size_t grade(Quiz<M> const& corAns, Quiz<M> const& stuAns)
{
    auto result = stuAns.bitquiz ^ corAns.bitquiz;
    result.flip();
    return result.count();
}

void q_17_11() {
    //Ex17_11
    std::string s = "1010101";
    Quiz<10> quiz(s);
    std::cout << quiz << std::endl;

    //EX17_12
    quiz.update(std::make_pair(1, true));
    std::cout << quiz << std::endl;

    //Ex17_13
    std::string answer = "10011";
    std::string stu_answer = "11001";
    Quiz<5> ans(answer), stu_ans(stu_answer);
    std::cout << grade(ans, stu_ans) << std::endl;
}

// 正则表达式
void test_regex() {
    // 完全匹配
    string str = "Hello123";
    std::regex pattern1(R"([A-Za-z]+\d{3}$)");
    if (std::regex_match(str, pattern1)) {
        cout << "完全匹配" << endl;
    }
    // 捕获分组
    std::regex pattern2(R"((\w+)\s+(\d+))");
    string str2 = "hello  1234";
    std::smatch results; // 匹配的结果 string
    if (std::regex_match(str2, results, pattern2)) {
        cout << "完全匹配: " << results[0] << endl;
        cout << "第一组: " << results[1] << endl;    // "abc"
        cout << "第二组: " << results[2] << endl;    // "123"
    }
    // 搜索匹配, 找 第一个匹配到的
    std::regex phone_pat(R"((\d{3})-(\d{4})-(\d{4}))");
    string str3 = "我的电话是 138-1234-5678，另一个是 139-8765-4321";
    if (std::regex_search(str3, results, phone_pat)) {
        cout << "找到电话: " << results[0] << endl;      // 138-1234-5678
        cout << "区号: " << results[1] << endl;          // 138
    }

    // 迭代器 所有匹配到的
    auto words_begin = std::sregex_iterator(str3.begin(), str3.end(), phone_pat);
    auto words_end = std::sregex_iterator();
    for (auto it = words_begin; it != words_end; ++it) {
        // std::smatch match = *it;
        // cout << "号码: " << match.str() << endl;
        cout << "号码: " << it->str()
            << "位置: " << it->position()
            << "长度: " << it->length() << endl;
    }

    try {
        // error: missing close bracket after alnum; the constructor will throw
        std::regex r("[[:alnum:]+\\.(cpp|cxx|cc)$", std::regex::icase);
    } catch (std::regex_error &e) {
        cout << e.what() << "\ncode: " << e.code() << endl;
    }

    std::regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);  // c++字符串中使用 双转义符
    // must match the type of the input sequence
    std::cmatch c_results;
    if (std::regex_search("main.cpp", c_results, r)) {  // smatch需要 string 的输入而不是 char*
        cout << results.str() << endl;
    }

    // string filename;
    // while (cin >> filename)
    //     if (regex_search(filename, results, r))
    //         cout << results.str() << endl; // print the current match

    // 替换 regex_replace
    // 简单替换
    string text = "C++ is cool, C++ is powerful";
    std::regex r1(R"(C\+\+)");
    string result = std::regex_replace(text, r1, "Python");
    cout << result << endl;

    // 使用捕获组 替换
    std::string date = "2024-01-15";
    std::regex date_pattern(R"((\d{4})-(\d{2})-(\d{2}))");
    std::string new_date = std::regex_replace(
        date, date_pattern, "$2/$3/$1");
    cout << new_date << endl;

    string fmt = "年: $1, 月: $2 日: $3";
    string formatted = std::regex_replace(date, date_pattern, fmt);
    cout << formatted << endl;
}

// 随机数
// 常用引擎：
// std::default_random_engine      // 默认引擎（实现依赖）
// std::mt19937                    // 32位梅森旋转算法（最常用）
// std::mt19937_64                 // 64位梅森旋转算法
// std::ranlux48                   // 高质量随机数，速度较慢
// std::minstd_rand                // 线性同余生成器

// 均匀分布
// std::uniform_int_distribution<int>      // 整数均匀分布
// std::uniform_real_distribution<double>  // 浮点数均匀分布
//
// // 其他常见分布
// std::normal_distribution<double>        // 正态分布
// std::bernoulli_distribution            // 伯努利分布（true/false）
// std::binomial_distribution<int>        // 二项分布
// std::poisson_distribution<int>         // 泊松分布
// std::exponential_distribution<double>  // 指数分布

// 创建可复用的随机函数
class RandomGenerator {
private:
    std::mt19937 gen;
    std::uniform_int_distribution<int> distrib;

public:
    RandomGenerator(int min, int max)
        : gen(std::random_device{}()), distrib(min, max) {}

    int operator()() {
        return distrib(gen);
    }
};

void test_random() {
    std::default_random_engine e;  // 随机数引擎 generates random unsigned integers
    for (size_t i = 0; i != 10; ++i) {
        cout << e() << " ";
    }
    cout << endl;

    // 1. 创建随机设备 （seed）
    std::random_device rd;
    // 2. 随机数引擎
    std::mt19937 gen(rd());  // 梅森旋转
    // 3. 分布 范围
    std::uniform_int_distribution<int> distrib(0, 99);
    std::normal_distribution<double> distrib_d(0.0, 1.0);  // mean 0，std: 1
    // 4. 生成随机数
    for (int i = 0; i != 10; ++i) {
        std::cout << distrib(gen) << " ";
        std::cout << distrib_d(gen)

        << " ";
    }
    std::cout << endl;

    RandomGenerator dice(1, 6);
    int roll = dice();  // 掷骰子
}

unsigned random_gen() {
    // 引擎对象应该重用，而不是每次需要随机数时都新建
    static std::default_random_engine e;
    static std::uniform_int_distribution<unsigned> ud;
    return ud(e);
}

unsigned random_gen(int seed) {
    static std::default_random_engine e(seed);
    static std::uniform_int_distribution<unsigned> ud;
    return ud(e);
}

unsigned random_gen(int seed, int min_val, int max_val) {
    static std::default_random_engine e(seed);
    static std::uniform_int_distribution<unsigned> ud(min_val, max_val);
    return ud(e);
}

void q_17_28_29_30() {
    std::string temp;
    while(std::cin >> temp)
        std::cout << std::hex << random_gen(19, 1, 10) << std::endl;
}

// 格式化输入 输出
void test_io_format() {
    // boolalpha noboolalpha
    cout << "default bool values: " << true << " " << false
    << "\nalpha bool values: " << std::boolalpha
    << true << " " << false << endl;
    // 修改整数 输出进制
    cout << std::showbase; // show the base when printing integral values  noshowbase
    cout << "default: " << 20 << " " << 1024 << endl;
    cout << "octal: " << std::oct << 20 << " " << 1024 << endl;
    cout << "hex: " << std::hex << 20 << " " << 1024 << endl;
    cout << "decimal: " << std::dec << 20 << " " << 1024 << endl;

    // 浮点数的 小数位
    // cout.precision reports the current precision value
    cout << "Precision: " << cout.precision()
    << ", Value: " << sqrt(2.0) << endl;
    // cout.precision(12) asks that 12 digits of precision be printed
    cout.precision(12);
    cout << "Precision: " << cout.precision()
    << ", Value: " << sqrt(2.0) << endl;
    // alternative way to set precision using the setprecision manipulator
    cout << std::setprecision(3);
    cout << "Precision: " << cout.precision()
    << ", Value: " << sqrt(2.0) << endl;
}

void test_format() {
    // c++ 20 std::format
    int apples = 5;
    double price = 3.14;
    string fruit  = "apples";
    cout << std::format("I have {} {}. \n", apples, fruit);
    cout << std::format("Price {0:.2f}, Count: {1:04d} \n", price, apples);
    // 3. 直接返回字符串，方便组合
    std::string msg = std::format("Total: ${:.2f}", apples * price);
    std::cout << msg << std::endl; // Total: $15.70
 }

int main(int argv, char** argc) {
    test_format();
    test_io_format();
    // q_17_28_29_30();
    test_random();
    test_regex();
    q_17_11();
    q_17_10();
    test_bitset_operation();
    // q_17_4();
    test_tuple();
    return 0;
}