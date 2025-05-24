#include <algorithm>
#include <array>
#include <deque>
#include <filesystem>
#include <forward_list>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <stack>
#include <queue>

#include "../ch08/Sales_Data.h"

using std::stack;
using std::queue;
using std::priority_queue;
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

void test_resize() {
    list<int> ilist(10, 42);
    ilist.resize(15);  // 元素要有默认构造函数
    ilist.resize(25, -1);
    ilist.resize(5);
}

void test_loop_change_container() {
    vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
    auto iter = vi.begin(); // call begin, not cbegin because we’re changing vi
    while (iter != vi.end()) {
        if (*iter % 2) {
            // 1前面插入一个1，iter位置是前一个1
            iter = vi.insert(iter, *iter); // duplicate the current element
            //  +2 指向原来的1的后一个（2）
            iter += 2; // advance past this element and the one inserted before it
        } else
            // 删除2， iter指向下一个元素(3)
            iter = vi.erase(iter); // remove even elements
        // don’t advance the iterator; iter denotes the element after the one we erased
    }
    for (auto &item : vi) {
        cout << item << " ";
    }
    cout << "\n";
}


void test_avoid_store_end() {
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto begin = v.begin();
    while (begin != v.end()) {  // 每次重新计算end
        ++begin;  // 0 -> 1, 1 -> 2
        begin = v.insert(begin, 42);  // 在1前面(0后面)插入
        ++begin;  // 42 -> 1, 42 -> 2
    }
    for (auto &item : v) {
        cout << item << " ";
    }
    cout << "\n";
}

void q_9_31() {
    // silly loop to remove even-valued elements and insert a duplicate of odd-valued elements
    list<int> l = {0,1,2,3,4,5,6,7,8,9};
    auto iter = l.begin(); // call begin, not cbegin because we’re changing vi
    while (iter != l.end()) {
        if (*iter % 2) {
            iter = l.insert(iter, *iter); // duplicate the current element
            // 复合赋值语句只能用于string、vector、deque、array
            // iter += 2; // advance past this element and the one inserted before it
            ++iter;
            ++iter;
        } else
            iter = l.erase(iter); // remove even elements
        // don’t advance the iterator; iter denotes the element after the one we erased
    }
    for (auto &item : l) {
        cout << item << " ";
    }
    cout << endl;
}

void q_9_31_forward_list() {
    // silly loop to remove even-valued elements and insert a duplicate of odd-valued elements
    forward_list<int> l = {0,1,2,3,4,5,6,7,8,9};
    // auto prev = l.before_begin();
    // auto curr = l.begin();
    // while (curr != l.end()) {
    //     if (*curr & 0x01) {
    //         // 0 后面插入1， curr指向插入的1
    //         curr = l.insert_after(prev, *curr);
    //         // curr 指向 2
    //         ++curr;
    //         ++curr;
    //         // prev 指向第二个1
    //         ++prev;
    //         ++prev;
    //     } else {
    //         curr = l.erase_after(prev);
    //     }
    //
    // }
    for (auto curr = l.begin(), prev = l.before_begin(); curr != l.end(); ) {
        if (*curr & 0x01) {
            curr = l.insert_after(prev, *curr);

            std::advance(curr, 2);
            std::advance(prev, 2);
        } else {
            curr = l.erase_after(prev);
        }
    }
    for (auto &item : l) {
        cout << item << " ";
    }
    cout << endl;
}

void q_9_33() {
    vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto begin = v.begin();
    while (begin != v.end()) {
        ++begin;
        //v.insert(begin, 42); // begin 会失效  the iterator is invalid after inserting.
        begin = v.insert(begin, 42);
        ++begin;
    }

    for (auto i : v)
        cout << i << " ";
}

void q_9_34() {
    vector<int> vi{0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    for (auto iter = vi.begin(); iter != vi.end(); ++iter) {
        if (*iter & 0x01) {
            iter = vi.insert(iter, *iter), ++iter;
        }
    }
}

void test_capacity_size() {
    vector<int> ivec;
    // size should be zero; capacity is implementation defined
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
    // give ivec 24 elements
    for (vector<int>::size_type ix = 0; ix != 24; ++ix)
        ivec.push_back(ix);
    // size should be 24; capacity will be >= 24 and is implementation defined
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;

    ivec.reserve(50); // sets capacity to at least 50; might be more
    // size should be 24; capacity will be >= 50 and is implementation defined
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;

    // add elements to use up the excess capacity
    while (ivec.size() != ivec.capacity())
        ivec.push_back(0);
    // capacity should be unchanged and size and capacity are now equal
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;

    ivec.push_back(42); // add one more element
    // size should be 51; capacity will be >= 51 and is implementation defined
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;

    ivec.shrink_to_fit(); // ask for the memory to be returned
    // size should be unchanged; capacity is implementation defined
    cout << "ivec: size: " << ivec.size()
         << " capacity: " << ivec.capacity() << endl;
}


void q_9_38() {
    vector<int> ivec;
    for (auto i = 0; i != 100; ++i) {
        ivec.push_back(i);
        cout << "ivec: size: " << ivec.size() << " capacity: " << ivec.capacity() << endl;
    }
}

void test_string_constructor() {
    const char *cp = "hello world !!!";  // null-terminated array
    char noNUll [] = {'H', 'i'};  // not null terminated
    string s1(cp);
    string s2(noNUll, 2);
    string s3(noNUll);   //
    string s4(cp + 6, 5);
    string s5(s1, 6, 5);
    string s6(s1, 6);
    string s7(s1, 6, 20);

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;  // Hie
    cout << s4 << endl;
    cout << s5 << endl;
    cout << s6 << endl;
    cout << s7 << endl;
    // string s8(s1, 16);  // std::out_of_range
    // cout << s8 << endl;

}

void test_string_substr() {
    string s1 = "hello world";
    string s2 = s1.substr(0, 5);  // [0, 5)
    cout << s2 << endl;
    string s3 = s1.substr(6);  // [6, n)
    cout << s3 << endl;
    string s4 = s1.substr(6, 11);
    cout << s4 << endl;
}

void q_9_41() {
    vector<char> vc = {'a', 'b', 'c', 'd'};
    string s(vc.cbegin(), vc.cend());
    cout << s << endl;
    int i = 44-27 + 91-76 + 19-2+57-42+20-5+58-43+29-14+68-51+35-20+70-55+42-25+77-62+29-9+82-65+10-0+639-630;
    cout << i << endl;
}

void q_9_42 () {
    string s1;
    s1.reserve(100);   // 读至少100个字符
    char c;
    while (cin >> c) {
        s1.push_back(c);
    }
    cout << s1 << endl;
}

void test_string_insert_erase_assign() {
    // 除了 iterator 还可接收position参数
    string s = "hello";
    s.insert(s.size(), 5, '!');   // 末尾插入5个！
    s.erase(s.size() - 5, 5);   // 删除结尾5个

    const char *cp = "let's go!";
    size_t length = std::strlen(cp);

    cout << length << endl;
    size_t n = 5;
    if (n <= length) {
        s.assign(cp, n);
    } else {
        std::cout << "Error: n is greater than the length of the string." << std::endl;
    }
    // s.assign(cp, 5);   // s = cp 前5个  n超出cp长度会引发undefined
    cout << s << endl;

    s.insert(s.size(), cp + 5);
    cout << s << endl;

    string s1 = "some string", s2 = "some other string";
    s1.insert(0, s2); // insert a copy of s2 before position 0 in s
    cout << s1 << endl;
    // insert s2.size() characters from s2 starting at s2[0] before s[0]
    s1.insert(0, s2, 0, s2.size());
    cout << s1 << endl;
}

void test_string_append_replace() {
    string s("C++ Primer"), s2 = s; // initialize s and s2 to "C++ Primer"
    s.insert(s.size(), " 4th Ed.");
    s2.append(" 4th Ed.");

    s.erase(11, 3);
    s.insert(11, "5th");
    cout << s << endl;

    s2.replace(11, 3, "5th");
    cout << s2 << endl;

    // s.replace(11, 3, "Fifth"); // 删除3个，插入5个
}

void replace_iterator(string &s, const string &old_val, const string &new_val) {
    for (auto iter = s.begin(); iter != s.end() - old_val.size(); ) {
        if (old_val == string{iter, iter + old_val.size()}) {
            iter = s.erase(iter, iter + old_val.size());
            iter = s.insert(iter, new_val.begin(), new_val.end());
            iter += new_val.size();
        } else {
            ++iter;
        }
    }
}


void replace_index(string &s, const string &old_val, const string &new_val) {
    for (decltype(s.size()) i = 0; i < s.size() - old_val.size(); ) {
        if (s[i] == old_val[0] && old_val == s.substr(i, old_val.size())) {
            s.replace(i, old_val.size(), new_val);
            i += new_val.size();
        } else {
            ++i;
        }
    }
}

void q_9_45(string &name , const string &pre, const string &suf) {
    name.insert(name.begin(), pre.cbegin(), pre.cend());
    name.append(suf);
}

void q_9_46(string &name , const string &pre, const string &suf) {
    name.insert(0, pre);
    name.insert(name.size(), suf);
}

void test_find() {
    string name("Ulysses");
    auto pos1 = name.find("ss");
    auto pos2 = name.find('a');  // npos -1 18446744073709551615
    cout << pos1 << " " << pos2 << endl;

    string numbers("0123456789"), name2("r2d2");
    auto pos3 = name2.find_first_of(numbers); // 找到第一个在numbers中的 字符的位置
    cout << pos3 << '\n';
    string dept("234dp1");
    cout << dept.find_first_not_of(numbers) << '\n';  // 第一个不是的 位置
    string str = "a quick brown fox jumps over the lazy dog";

    string::size_type pos = 0;
    string str3 = "dfdf1d=23cxcd3-454csas5";
    while ( (pos = str3.find_first_of(numbers, pos)) != string::npos) {
        cout << "find number at : " << pos << " element is " << str3[pos] << "\n";
        ++pos;
    }

    string river("Mississippi");
    auto first_pos = river.find("is"); // returns 1
    auto last_pos = river.rfind("is"); // returns 4
    cout << first_pos << " " << last_pos << '\n';
}


void q_9_47() {
    string name("ab2c3d7R4E6"), numbers("0123456789");

    cout << "num pos: " << '\n';
    for (int i = 0; (i = name.find_first_of(numbers, i)) != string::npos; ++i) {
        cout << "find num at : " << i << " element is : " << name[i] << endl;
    }

    cout << "alphabetic pos: " << '\n';
    for (int i = 0; (i = name.find_first_not_of(numbers, i)) != string::npos; ++i) {
        cout << "find alphabet at : " << i << " element is : " << name[i] << endl;
    }

}

void q_9_49(string filename) {
    std::ifstream ifs(filename);
    if (! ifs) {
        cout << "file not exist!!!" << endl;
        return ;
    }
    string longest;
    auto get_longest = [&longest](const string &str) -> void {
        if (string::npos == str.find_first_not_of("aceimnorsuvwxz")) {  // 只含这几个字符
            longest = str.size() > longest.size() ? str : longest ;
        }
    };

    for (string word; ifs >> word;get_longest(word));
    cout << longest << "\n";
}

int q_9_50(const vector<string> &sv) {
    int sum = 0;
    for (auto &str : sv) {
        sum += std::stoi(str);
    }
    return sum;
}

float q_9_50_2(const vector<string> &sv) {
    float sum = 0;
    for (auto &str : sv) {
        sum += std::stof(str);
    }
    return sum;
}


void test_numeric_conversion() {
    int i = 42;
    string s = std::to_string(i);
    double d = std::stod(s);
    string s2 = "pi = 3.1415";
    d = std::stod(s2.substr(s2.find_first_of("+-0123456789.")));
    cout << d << endl;
}

class Date {
private:
    unsigned year;
    unsigned month;
    unsigned day;
public:
    Date() : year(2025), month(5), day(25) {};
    explicit Date(const string &date) {
        // January 1, 1900, 1/1/1900, Jan 1, 1900
        // 1/1/1900
        unsigned format = 0, tag = 0;
        if (date.find('/') != string::npos) {
            format = 0x01;
        }
        if ((date.find_first_of(",") >= 4) && (date.find_first_of(",") != string::npos)) {
            // January 1, 1900   Jan 1, 1900
            format = 0x10;
        } else if (date.find_first_of(' ') >= 3 && date.find_first_of(' ') != string::npos) {
            //  Jan 1 1900
            format = 0x10;
            tag = 1;
        }

        switch (format) {
            case 0x01: {
                auto first_slash = date.find_first_of('/');
                auto last_slash = date.find_last_of('/');
                day = std::stoi(date.substr(0, first_slash));
                month = std::stoi(date.substr(first_slash+1, last_slash - first_slash));
                year = std::stoi(date.substr(last_slash+1, 4));
                break;
            }
            case 0x10: {
                if( date.find("Jan") < date.size() )  month = 1;
                if( date.find("Feb") < date.size() )  month = 2;
                if( date.find("Mar") < date.size() )  month = 3;
                if( date.find("Apr") < date.size() )  month = 4;
                if( date.find("May") < date.size() )  month = 5;
                if( date.find("Jun") < date.size() )  month = 6;
                if( date.find("Jul") < date.size() )  month = 7;
                if( date.find("Aug") < date.size() )  month = 8;
                if( date.find("Sep") < date.size() )  month = 9;
                if( date.find("Oct") < date.size() )  month =10;
                if( date.find("Nov") < date.size() )  month =11;
                if( date.find("Dec") < date.size() )  month =12;
                char split_chr = ',';
                if (tag == 1) {
                    split_chr = ' ';
                }
                auto first_num = date.find_first_of("123456789");
                // 第一个数字 和 split
                day = std::stoi(date.substr(first_num, date.find_first_of(split_chr) - first_num));
                year = std::stoi(date.substr(date.find_last_of(' ') + 1, 4));
                break;
            }

        }


    };
    void print() {
        cout << "day:" << day << " " << "month: " << month << " " << "year: " << year << '\n';
    }
};

void test_adaptor() {
    // stack , queue 根据deque实现
    // priority_queue 根据vector实现
    deque<int> deq{1, 2, 3};
    std::stack<int> stk(deq);
    // override the default container type by naming a sequential container as a second type argument :
    // 这个stack底层使用vector实现
    stack<string, vector<string>> str_stack;
    vector<string> svec{"abc", "deff"};
    stack<string, vector<string>> str_stack2(svec);
}

void test_stack_adaptor() {
    stack<int> intStack;
    for (size_t ix = 0; ix != 10; ++ix)
        intStack.push(ix);
    while (!intStack.empty()) {
        int val = intStack.top();
        cout << val << ' ';
        intStack.pop();
    }
    cout << endl;
}

void q_9_52(const string &s) {
    // string s = "hello, (come and have fun (go) !!)!";
    stack<char> stk;
    string temp = "";
    for (const auto &c : s) {
        if (c == ')') {
            // 出栈
            while (!stk.empty() && stk.top() != '(') {
                temp += stk.top();
                stk.pop();
            }
            stk.pop(); // pop (

            for (auto rit = temp.rbegin(); rit != temp.rend(); ++rit) {
                stk.push(*rit);
            }
            temp = "";

        } else {
            stk.push(c);
        }
    }
    string res = "";
    while (! stk.empty()) {
        res += stk.top();
        stk.pop();
    }
    std::reverse(res.begin(), res.end());


    cout << res << endl;
}


int main(int argc, char **argv) {
    string s1 = "(he)l(lo), (come (and) have fun (go) !!)!";
    q_9_52(s1);
    test_stack_adaptor();
    Date date1("1/1/2025");
    date1.print();
    Date date2("Jan 1 2024");
    date2.print();
    Date date3("January 1, 2023");
    date3.print();

    vector<string> sv{"123", "-23", "0"};
    vector<string> fv{"123.1", "-12.4"};
    cout << q_9_50_2(fv) << endl;
    cout << q_9_50(sv) << endl;
    test_numeric_conversion();
    string file_name = "/mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch09/data";
    q_9_49(file_name);
    q_9_47();
    test_find();
    string name = "Ulysses";
    // q_9_45(name, "Mr. ",  " Jr.");
    q_9_46(name, "Mr. ",  " Jr.");
    cout << name << endl;

    string s{ "To drive straight thru is a foolish, tho courageous act." };
    // replace_iterator(s, "tho", "though");
    // replace_iterator(s, "thru", "through");
    // cout << s << endl;
    replace_index(s, "tho", "though");
    replace_index(s, "thru", "through");
    cout << s << endl;
    test_string_append_replace();
    test_string_insert_erase_assign();
    // q_9_42();
    q_9_41();
    test_string_substr();
    test_string_constructor();
    // q_9_38();
    test_capacity_size();
    q_9_33();
    q_9_31_forward_list();
    q_9_31();
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
