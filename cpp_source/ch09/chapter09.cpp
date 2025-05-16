#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <vector>
#include "../ch08/Sales_Data.h"

using std::vector;
using std::array;
using std::list;
using std::deque;
using std::string;
using std::forward_list;
using std::array;
using std::endl; using std::cout; using std::cin;


void q_9_2() {
    list<deque<int>> l;
}

bool q_9_3(vector<int>::const_iterator beg, vector<int>::const_iterator end, const int val) {
    while (beg != end) {
        if (*beg++ == val) {
            return true;
        }
    }
    return false;
}

vector<int>::const_iterator q_9_4(vector<int>::const_iterator beg, vector<int>::const_iterator end, const int val) {
    while (beg != end) {
        if (*beg == val) {
            break;
        }
        ++beg;
    }
    return beg;
}

void test_copy_container(){
    list<string> authors = {"Tom", "Jackey", "Bill"};
    vector<const char*> articles = {"a", "the", "an"};

    // container element type 要一致
    list<string> list2(authors);

    // 传入iterators， element type 可以convert 就可以
    forward_list<string> words(articles.begin(), articles.end());

    vector<int> ivec(10, -1);
    deque<string> svec(10);

    // array不能使用 (n, val)的方式
    array<int, 10> iarr = {0, 1, 2, 3, 4};
    for (auto &item : iarr) {
        cout << item << " ";
    }
    cout << endl;

    int digs[10] = {0,1,2,3,4,5,6,7,8,9};
    // int cpy[10] = digs; // error: no copy or assignment for built-in arrays
    array<int, 10> digits = {0,1,2,3,4,5,6,7,8,9};
    array<int, 10> copy(digits); // ok: so long as array types match
    copy = {1, 2, 3};
}

void q_9_11() {
    vector<int> vec;
    vector<int> vec2 = {1, 2, 3};
    vector<int> vec3{1, 2, 3};
    vector<int> vec4(vec2);
    vector<int> vec5 = vec2;
    vector<int> vec6(vec2.begin(), vec2.end());
    vector<int> vec7(7);
    vector<int> vec8(7, 2);
}

void q_9_13() {
    vector<int> ivec = {1, 2, 3};
    list<int> ilst = {1, 2, 3};
    vector<double> dvec(ivec.begin(), ivec.end());
    vector<double> dvec2(ilst.begin(), ilst.end());
    for (auto &item: dvec) {
        cout << item << " ";
    }
    cout << "\n";
}

void test_assignment() {
    array<int, 10> a1 = {0,1,2,3,4,5,6,7,8,9};
    array<int, 10> a2 = {0}; // elements all have value 0
    a1 = a2; // replaces elements in a1
    a2 = {1, 2, 3}; // error: cannot assign to an array from a braced list
    for (auto &item: a2) {
        cout << item << " ";
    }
    cout << "\n";

    list<string> names;
    vector<const char*> oldstyle = {"aaa", "bbb", "ccc", "ddd"};
    names.assign(oldstyle.cbegin(), oldstyle.cend());

    list<string> slist1(1); // one element, which is the empty string
    slist1.assign(10, "Hiya!"); // ten elements; each one is Hiya!
}

void test_swap() {
    vector<string> svec1(4, "a");
    vector<string> svec2(6, "b");
    // 交换容器内部的值，容器本身没有交换
    swap(svec1, svec2);
    for (auto &s : svec1) {
        cout << s << " ";
    }
    cout << "\n";

    for (auto &s : svec2) {
        cout << s << " ";
    }
    cout << "\n";
}

bool is_vector_int_equal(const vector<int> &a, const vector<int> &b) {
    if (a.size() == b.size()) {
        for (decltype(a.size()) i = 0; i != a.size(); ++i) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void q_9_15() {
    vector<int> ivec1{1, 2, 3};
    vector<int> ivec2{1, 2, 4};
    vector<int> ivec3{1, 2, 3};
    cout << is_vector_int_equal(ivec1, ivec2) << "\n";
    cout << (ivec1 == ivec3 ? "true" : "false") << "\n";
}

void q_9_16() {
    vector<int> ivec1{1, 2, 3};
    list<int> ilst1{1, 2, 4};
    list<int> ilst2{1, 2, 3};
    // 使用临时对象，右值
    cout << (vector<int>(ilst1.begin(), ilst1.end()) == ivec1 ? "true" : "false") << "\n";
    cout << (vector<int>(ilst2.begin(), ilst2.end()) == ivec1 ? "true" : "false") << "\n";
}

void test_push_char() {
    string word = "123";
    word.push_back('a');
    word.append("cde");
    cout << word << endl;
}

void test_push() {
    list<int> ilist;
    for (size_t ix = 0; ix != 4; ++ix) {
        ilist.push_front(ix);
    }
    ilist.insert(ilist.begin(), {11, 21, 31});
}

void test_insert() {
    vector<string> svec;
    list<string> slist;
    // equivalent to calling slist.push_front("Hello!");
    slist.insert(slist.begin(), "Hello!");
    // no push_front on vector but we can insert before begin()
    // warning: inserting anywhere but at the end of a vector might be slow
    svec.insert(svec.begin(), "Hello!");
    svec.insert(svec.end(), 10, "Tom");

    vector<string> v = {"quasi", "simba", "frollo", "scar"};
    // 添加 v的最后2个到slist, 不能使用slist
    slist.insert(slist.begin(), v.end() - 2, v.end());
    slist.insert(slist.end(), {"first", "second"});
}

void test_return_from_insert() {
    string word = "123";
    list<string> lst;
    auto iter = lst.begin();
    while (cin >> word)
        iter = lst.insert(iter, word); // same as calling push_front
    for (auto &item : lst)
        cout << item << " ";
    cout << "\n";
}

void test_emplace() {
    vector<Sales_Data> c;
    c.emplace_back("aaa", 14, 0.5);

    // 创建了临时对象
    c.push_back(Sales_Data("aaa", 10, 1.5));

    for (auto &item : c) {
        print(cout, item) << "\n";

    }
}

int main(int argc, char **argv) {
    test_emplace();
    test_return_from_insert();
    test_push_char();
    q_9_16();
    q_9_15();
    test_swap();
    test_assignment();
    q_9_13();
    test_copy_container();
    vector<int> vec{1, 2, 3, 4, 5};
    auto flag = q_9_3(vec.begin(), vec.end(), 1);
    std::cout << flag << std::endl;
    return 0;
}
