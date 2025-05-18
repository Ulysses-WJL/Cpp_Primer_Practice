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
    c.emplace_back();  // 使用默认的构造函数

    for (auto &item : c) {
        print(cout, item) << "\n";
    }
}

void q_9_18() {
    string temp;
    deque<string> dq;
    while (cin >> temp) {
        dq.push_front(temp);
    }
    for (auto &item : dq) {
        cout << item << " ";
    }
    cout << "\n";
}

void q_9_20() {
    list<int> ilst{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    deque<int> dq_even, dq_odd;
    // for (auto &item : ilst) {
    //     if (item % 2 == 0) {
    //         dq_even.push_back(item);
    //     } else {
    //         dq_odd.push_back(item);
    //     }
    // }
    for (auto &item : ilst) {
        ((item & 0x01) ? dq_odd : dq_even).push_back(item);
    }
    cout << "=============even===========\n";
    for (auto &item : dq_even) {
        cout << item << " ";
    }
    cout << "\n";
    cout << "=============odd===========\n";
    for (auto &item : dq_odd) {
        cout << item << " ";
    }
    cout << "\n";
}

void q_9_21() {
    int i;
    vector<int> ivec1;
    auto iter = ivec1.begin();
    while (cin >> i)
        // 使用返回的迭代器 进行插入   == push_front
        // 将一个新元素插入到 iter 之前，并将 iter 改变为新加入元素的位置
        iter = ivec1.insert(iter, i);
}

void q_9_22() {
    vector <int> iv{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int some_value = 2;
    vector<int>::iterator iter = iv.begin(), mid = iv.begin() + iv.size()/2;
    while (iter != mid) {
        if (*iter == some_value)
            iv.insert(iter, 2 * some_value);
        ++iter;
    }
    for (auto &item : iv) {
        cout << item << " ";
    }
    cout << "\n";
}

void test_access() {
    vector<int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (!ivec.empty()) {  // 总是先check 是否为空
        // 起始
        auto val = *ivec.begin(), val2 = ivec.front();
        // 结束
        auto last = ivec.end();  // 结尾的后一个 nonexistent
        auto val3 = *(--last);
        auto &val4 = ivec.back();  // 使用reference change value
        val4 = 1024;
        auto val5 = ivec.at(ivec.size() - 1);
        // auto val6 = ivec.at(10);  // at 越界会报 'std::out_of_range'
        cout << val << " " << val2 << " " << ivec[0] << "\n";
        cout << val3 << " " << val5 << " " <<  ivec[9] << "\n";
    }
}

void test_erase() {
    vector <int> ivec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    while (!ivec.empty()) {
        ivec.pop_back();
    }
    cout << ivec.size() << "\n";

    list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto it = lst.begin();
    while (it != lst.end()) {
        if (*it & 0x01) {
            it = lst.erase(it);  // 清除it 并返回下一个
        } else {
            ++it;
        }
    }

    vector<string> svec = {"a", "b", "c", "d", "e", "f"} ;
    auto it1 = svec.begin();
    // one past the last element we want to remove
    auto it2 = svec.begin() + 3;
    svec.erase(it1, it2);
    for (auto &item : svec) {
        cout << item << " ";
    }
    cout << "\n";

    svec.clear();
    // svec.erase(svec.begin(), svec.end());
}

void q_9_26() {
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    vector<int> ivec(std::begin(ia), std::end(ia));
    list<int> ilst(std::begin(ia), std::end(ia));
    auto it = ivec.begin();
    while (it != ivec.end()) {
        if (*it & 0x01) {
            it = ivec.erase(it);
        } else {
            ++it;
        }

    }

    for (auto item : ivec) {
        cout << item << " ";
    }
    cout << "\n";

    auto it1 = ilst.begin();
    while (it1 != ilst.end()) {
        if (*it1 & 0x01) {
            it1 = ilst.erase(it1);
        } else {
            ++it1;
        }
    }

    for (auto item : ilst) {
        cout << item << " ";
    }
    cout << "\n";
}

void test_forward_list_erase() {
    forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    auto prev = flst.before_begin();
    auto curr = flst.begin();
    while (curr != flst.end()) {
        if (*curr & 0x01) {
            // 删去prev的下一个（curr）, 返回 curr的下一个元素
            curr = flst.erase_after(prev);
        } else {
            prev = curr;
            ++curr;
        }
    }

    for (auto &item : flst) {
        cout << item << " ";
    }
    cout << endl;
}

void q_9_27(forward_list<string> &fst, const string &str, const string &str2) {
    auto prev = fst.before_begin();
    auto curr = fst.begin();
    while (curr != fst.end()) {
        if (*curr == str) {
            // 返回iterator to the last inserted element
            fst.insert_after(curr, str2);
            return;
        }
        prev = curr;
        ++curr;
    }
    // prev 是最后一个元素
    fst.insert_after(prev, str2);
}

int main(int argc, char **argv) {
    forward_list<string> fst = {"a", "b", "c", "d", "e", "f"};
    q_9_27(fst, "c", "find");
    for (auto &item : fst) {
        cout << item << " ";
    }
    cout << "\n";
    test_forward_list_erase();
    q_9_26();
    test_erase();
    test_access();
    q_9_22();
    q_9_20();
    // q_9_18();
    test_emplace();
    // test_return_from_insert();
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
