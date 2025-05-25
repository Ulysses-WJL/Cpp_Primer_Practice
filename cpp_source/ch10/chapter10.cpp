#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <numeric>
#include <iterator>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::find;
using std::count;
using std::string;
using std::list;
using std::accumulate;
using std::equal;
using std::fill;
using std::fill_n;
using std::back_inserter;
using std::copy;
using std::replace;
using std::replace_copy;
using std::sort;
using std::unique;


void test_find() {
    int val = 34;
    vector<int> ivec{12, 23, 344, 343, 23, 1};
    auto result = find(ivec.cbegin(), ivec.cend(), val);
    cout << "Find val: " << (result == ivec.cend() ? "not exist" : "exist")  << endl;

    int ia[] = {23, 231, 44, 4, 23, 55, 344, 243, 5455};
    int ival = 44;
    // auto i_result = find(std::begin(ia), std::end(ia), ival);
    // [2, 7) 范围
    int *i_result = find(ia+2, ia+7, ival);
    cout << "Find val: " << (i_result == ia+7 ? "not exist" : "exist")  << endl;
}

void q_10_1(const vector<int> &ivec, int val) {
    auto num = count(ivec.cbegin(), ivec.cend(),  val);
    cout << "count: " << num << endl;
}

void q_10_1(const list<string> &slist, string val) {
    auto num = count(slist.cbegin(), slist.cend(),  val);
    cout << "count: " << num << endl;
}

void test_accumulate() {
    vector<int> ivec{1, 2, 3, 4, 4, 24, 54, 4};
    int sum = accumulate(ivec.cbegin(), ivec.cend(), 0);
    cout << "the sum : " << sum << endl;

    vector<string> svec{"hello ", "world ", "have ", "fun"};
    // const char* 无法使用+ 显式声明为string
    string res = accumulate(svec.cbegin(), svec.cend(), string{""});
    cout << "the sum : " << res << endl;
}

void q_10_5() {
    // vector<string> roster1{"a", "c", "d"}, roster2{"pre", "a", "c", "d"};
    // c-style strings cannot be compared using == and < and >, 'casue these relational operators compare addresses in
    // pointers rather than strings represented by char pointers.

    // true
    vector<const char*> roster1{"a", "c", "d"}, roster2{"pre", "a", "c", "d"};
    cout << std::boolalpha << equal(roster1.cbegin(), roster1.cend(), roster2.cbegin() + 1) << endl;

    // false
    // For such case, std::equal is going to compare the address value rather than the string value.
    const char a[3][2] = {"A", "B", "C"}; // {'A' , '\0'},
    const char b[3][2] = {"A", "B", "C"};
    std::vector<const char*> v1(std::begin(a), std::end(a));
    std::list<const char*> v2(std::begin(b), std::end(b));
    std::cout << std::boolalpha
        << std::equal(v1.cbegin(), v1.cend(), v2.cbegin()) << std::endl;

    // true
    //  literals of same contents pointed to by pointers share the same memories, but literals in arrays are stored individually.
    const char *c[3] = {"A", "B", "C"};
    const char *d[3] = {"A", "B", "C"};
    std::vector<const char*> v3(std::begin(c), std::end(c));
    std::list<const char*> v4(std::begin(d), std::end(d));
    std::cout << std::boolalpha
        << std::equal(v3.cbegin(), v3.cend(), v4.cbegin()) << std::endl;
}


void test_fill() {
    vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    fill(ivec.begin() + 1, ivec.end() - 1, 0);
    for (auto &item: ivec) {
        cout << item << " ";
    }
    cout << endl;
    fill_n(ivec.begin() + 1, 4, 100.0);
    for (auto &item: ivec) {
        cout << item << " ";
    }
    cout << endl;
}

void test_back_inserter() {
    vector<int> ivec;
    auto it = back_inserter(ivec);
    *it = 110; // calls push_back to add an element to ivec
    fill_n(back_inserter(ivec), 11, 1);
    for (auto &item: ivec) {
        cout << item << " ";
    }
    cout << endl;
}

void test_copy_replace() {
    int a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int a2[] = a1; // 无法这样初始化
    // int a2[sizeof(a1) / sizeof(*a1)];
    int a2[std::size(a1)];
    auto ret = copy(std::begin(a1), std::end(a1), a2);
    // ret will point just past the last element copied into a2.
    cout << "ret pos: " << ret << endl;
    cout << "pos a1: " << a1 << " pos a2: " << a2 << endl;

    list<int> ilst{1, 2 , 3, 2, 4, 5};
    replace(ilst.begin(), ilst.end(), 2, 11);
    for (auto &item: ilst) {
        cout << item << " ";
    }
    cout << endl;

    vector<int> ivec;
    // 通过replace_copy给 ivec赋值
    // back_inserter 是iterator包
    replace_copy(ilst.cbegin(), ilst.cend(), back_inserter(ivec), 11, 42);
    for (auto &item: ivec) {
        cout << item << " ";
    }
    cout << endl;
}

void q_10_7() {
    vector<int> vec; list<int> lst; int i;
    while (cin >> i) {
        lst.push_back(i);
    }
    copy(lst.cbegin(), lst.cend(), back_inserter(vec));
    for (auto &item : vec) {
        cout << item << " ";
    }
    cout << endl;

    vector<int> vec2;
    // vec2.reserve(10); // vec2.size() 还是0
    // 1
    // vec2.resize(10);
    // fill_n(vec2.begin(), 10, 0);
    // 2
    fill_n(back_inserter(vec2), 10, 2);
    for (auto &item : vec2) {
        cout << item << " ";
    }
    cout << endl;
}

template<typename Sequence>
auto println(Sequence const &seq) -> std::ostream& {
    for (auto const &item: seq) {
        cout << item + "_" << "\n";
    }
    return cout << endl;
}

void test_sort_unique() {
    vector<string> svec{"the", "quick", "red", "fox", "jumps",
        "over", "the", "slow", "red", "turtle", "fox"};
    sort(svec.begin(), svec.end());
    println(svec);
    // 重复的部分排在最尾部
    // The elements beyond that point still exist, but we don’t know what values they have.
    auto end_unique = unique(svec.begin(), svec.end());
    // end_unique后的值未定义
    println(svec);
    // 删去重复的部分
    svec.erase(end_unique, svec.end());
    println(svec);
}

int main(int *argc, char **argv) {
    test_sort_unique();
    // q_10_7();
    test_copy_replace();
    test_back_inserter();
    test_fill();
    q_10_5();
    test_accumulate();

    vector<int> ivec{1, 2, 3, 4, 4, 24, 54, 4};
    list<string> slist{"hello", "world", "hello", "world", "hello", "world"};
    slist.emplace_back("hello");
    q_10_1(slist, "hello");
    q_10_1(ivec, 433);
    test_find();
    return 0;
}