#include <algorithm>
#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <list>
#include <numeric>
#include <bitset>

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

int main(int argv, char** argc) {
    q_17_11();
    q_17_10();
    test_bitset_operation();
    // q_17_4();
    test_tuple();
    return 0;
}