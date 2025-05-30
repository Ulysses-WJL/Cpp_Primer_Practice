#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <numeric>
#include <iterator>
#include <functional>

#include "../ch08/Sales_Data.h"
#include "../ch01/Sales_item.h"

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
using std::partition;
using std::stable_partition;
using std::find_if;
using std::for_each;
using std::stable_sort;
using std::transform;
using std::count_if;
using std::bind;  // functional
using namespace std::placeholders;  // 使用占位符
using std::inserter;
using std::back_inserter;
using std::front_inserter;



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
    int a2[sizeof(a1) / sizeof(*a1)];
    // int a2[(a1)];
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
    // vec还是空的,使用push_back插入数值
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

template <typename Sequence>
auto println(Sequence const &seq) -> std::ostream& {
    for (auto const &item: seq) {
        cout << item  << " ";
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

bool is_shorter(const string &s1, const string &s2) {
    return s1.size() < s2.size();
}

void test_sort_with_predicate() {
    vector<string> svec{"the", "quick", "red", "fox", "jumps", "over", "a", "lazy", "dog"};
    sort(svec.begin(), svec.end());
    // sort(svec.begin(), svec.end(), is_shorter);
    println(svec);
    // equal的元素间顺序与原始的保持一致
    stable_sort(svec.begin(), svec.end(), is_shorter);
    println(svec);
}

bool is_shorter_sales_data(const Sales_Data &s1, const Sales_Data &s2) {
    return s1.isbn() < s2.isbn();
}

void q_10_12() {
    vector<Sales_Data> svec;
    svec.emplace_back("aaa", 123, 2.5);
    svec.emplace_back("ddd", 10, 2.0);
    svec.emplace_back("ccc", 24, 5.5);
    sort(svec.begin(), svec.end(), is_shorter_sales_data);
    for (auto &item: svec) {
        print(cout, item) << "\n";
    }
}

bool is_more_than_five(const string &str) {
    return str.size() >= 5;
}

void q_10_13_partition() {
    vector<string> svec{"abc", "def", "hello", "partition", "hi"};
    auto last = partition(svec.begin(), svec.end(), is_more_than_five);
    // svec.erase(last, svec.end());
    // println(svec);
    for (auto it=svec.begin(); it != last; ++it) {
        cout << *it << " ";
    }
    cout << "\n";
}

void q_10_14_test_lambda() {
    // capture list 使用local statics 和函数外部生命
    // [capture list](parameter list) -> return type { function body }
    auto f = [] (const int a, const int b) {return a + b;};
    cout << f(3, 4) << endl;
}

void elim_dups(vector<string> &words) {
    sort(words.begin(), words.end());
    auto last_unique = unique(words.begin(), words.end());
    words.erase(last_unique, words.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz) {
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

void q_10_15() {
    int sz = 100;
    auto f = [sz](const int a){return a + sz;};
    cout << f(23) << endl;
}


void q_10_17() {
    vector<Sales_Data> svec;
    svec.emplace_back("aaa");
    svec.emplace_back("ddd");
    svec.emplace_back("ccc");
    svec.emplace_back("abc");
    svec.emplace_back("cae");
    sort(svec.begin(), svec.end(),
        [](const Sales_Data &item1, const Sales_Data &item2){return item1.isbn() < item2.isbn();});
    for_each(svec.begin(), svec.end(), [](const Sales_Data &item){print(cout, item) << " ";});
    cout << endl;
}

void q_10_18(vector<string> &words, vector<string>::size_type sz) {
    elim_dups(words);
    auto pivot = partition(words.begin(), words.end(), [sz](const string &a){return a.size() >= sz;});
    // print
    for_each(words.begin(), pivot, [](const string &s){cout << s << " ";});
    cout << endl;
}

void q_10_19(vector<string> &words, vector<string>::size_type sz) {
    elim_dups(words);
    auto pivot = stable_partition(words.begin(), words.end(), [sz](const string &a){return a.size() >= sz;});
    // print
    for_each(words.begin(), pivot, [](const string &s){cout << s << " ";});
    cout << endl;
}

void test_lambda_capture() {
    size_t v1 = 42;
    auto f = [v1](){return v1;};  // 定义时就copy了 v1
    auto f2 = [&v1] {return v1;};  // 引用
    v1 = 0;
    cout << f() << endl;  // 42
    cout << f2() << endl;  // 0
}

void test_mix_captures(vector<string> &words, vector<string>::size_type sz, std::ostream &os=cout, char c=' ') {
    elim_dups(words);
    auto pivot = stable_partition(words.begin(), words.end(), [sz](const string &a){return a.size() >= sz;});
    // print
    // 隐式捕获在前，显式在后；混合时 比需一者为值捕获， 另一种引用捕获
    for_each(words.begin(), pivot, [&, c](const string &s){os << s << c;});
    cout << endl;
    for_each(words.begin(), pivot, [=, &os](const string &s){os << s << c;});
}

void test_multable_lambda() {
    size_t v1 = 0;
    auto f = [v1](){return v1;};  // 定义时就copy了 v1
    // auto f2 = [v1]() mutable  {return ++v1;};  // 可以改变v1, 参数列表不能省略
    auto f2 = [v1]() mutable   {return ++v1;};  // 引用nonconst variable  可以改变v1
    v1 = 100;
    cout << f() << endl;  // 0
    cout << f2() << endl;  // 1
}

void test_multable_lambda_2() {
    size_t v1 = 0;
    auto f = [v1](){return v1;};  // 定义时就copy了 v1
    // auto f2 = [v1]() mutable  {return ++v1;};  // 可以改变v1, 参数列表不能省略
    auto f2 = [&v1]()  {return ++v1;};  // 引用nonconst variable  可以改变v1
    v1 = 100;
    cout << f() << endl;  // 0
    cout << f2() << endl;  // 101
}

void test_lambda_return_type() {
    vector<int> ivec{-1, 2, -3, 133, -2442};
    // transform(ivec.begin(), ivec.end(), ivec.begin(),
    //     [](int i){return i < 0 ? -i:i;});
    // tailing return type
    transform(ivec.begin(), ivec.end(), ivec.begin(),
        [](int i) -> int {if (i < 0) return -i; else return i;});
    println(ivec);
}

void q_10_20_count_if(vector<string> &svec, vector<string>::size_type sz) {
    auto i = count_if(svec.begin(), svec.end(),
        [sz](const string &s){return s.size() >= sz;});
    cout << i  << endl;
}

void q_10_21() {
    int local_int = 10;
    // 非0 local_int递减，!() 返回false
    auto f = [&local_int]() -> bool { return (local_int == 0 ? true: !(local_int--));};
    while (!f()) cout << local_int <<endl;
}

bool check_size(const string &s, string::size_type sz) {
    return s.size() == sz;
}

std::ostream &printc(std::ostream &os, const string &s, char c) {
    return os << s << c;
}

void test_bind() {
    // 类似 partial， _1 占位符表示check_size的第一个参数
    auto check6 = bind(check_size, _1, 6);
    string s = "hello!";
    cout << std::boolalpha << check6(s) << endl;

    vector<string> svec{"a", "aaa", "cd", "1134", ""};
    // 最长到最短
    sort(svec.begin(), svec.end(), bind(is_shorter, _2, _1));
    // sort(svec.begin(), svec.end(),
    //     [](const string &str1, const string &str2){return str1.size() > str2.size();});
    // println(svec);

    // 在bind 中使用引用
    for_each(svec.begin(), svec.end(),
        bind(printc, ref(cout), _1, ';')
    );
}

bool is_le(const string &str, string::size_type sz) {
    return str.size() <= sz;
}

void q_10_22() {
    vector<string> svec{"the", "quick", "red", "fox", "jumps",
        "over", "the", "slow", "red", "turtle", "fox", "interesting", "international"};
    string::size_type sz = 6;
    auto cnt = count_if(svec.begin(), svec.end(), bind(is_le, _1, sz));
    cout << cnt << endl;
}

auto checksize(const string &str, size_t sz) -> bool {
    return str.size() < sz;
}

void q_10_24() {
    // 给定一个string，使用 bind 和 check_size 在一个 int 的vector 中查找第一个大于string长度的值。
    vector<int> ivec{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    string str("123234");
    auto result = find_if(
        ivec.begin(), ivec.end(), bind(check_size, str, _1));
    if (result != ivec.end())
        cout << *result << endl;
    else
        cout << "not found" << endl;
}

auto check_size_2(const string &str, size_t sz) {
    return str.size() >= sz;
}

void q_10_25(vector<string> words, size_t sz) {
    elim_dups(words);
    // 按 长度排序
    auto pviot = stable_partition(
        words.begin(), words.end(), bind(check_size_2, _1, sz));
    // print
    for_each(words.begin(), pviot, [](const string &s){cout << s << " ";});
    cout << endl;
}


void test_inserter() {
    vector<int> ivec{1, 2, 3, 4, 5};
    vector<int> dest;
    list<int> dest_front;
    // inserter 任意位置插入

    copy(ivec.begin(), ivec.end(), inserter(dest, dest.begin()));
    // 等价于
    // auto it = dest.begin();
    // for (auto &item: ivec) {
    //     it = dest.insert(it, item);
    //     ++it;
    // }
    println(dest);
    // 使用push_front 在开头插入， 5 4 3 2 1
    copy(ivec.begin(), ivec.end(), front_inserter(dest_front));
    println(dest_front);
}

void q_10_27_unique_copy() {
    vector<string> svec{"test", "how", "test", "how", "low"};
    list<string> unique_lst;
    sort(svec.begin(), svec.end());
    // 移除相邻重复项, 先排序
    std::unique_copy(svec.begin(), svec.end(), back_inserter(unique_lst));
    println(unique_lst);
}

void q_10_28() {
    vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> vec, vec1, vec2;
    list<int> lst3;
    // 1->9
    // copy(ivec.begin(), ivec.end(), vec.begin());
    // println(vec);
    // vec没有预先分配空间 直接复制到vec程序可能会崩溃或产生其他未定义行为
    copy(ivec.begin(), ivec.end(), inserter(vec1, vec1.begin()));
    println(vec1);
    // 1 -> 9
    copy(ivec.begin(), ivec.end(), back_inserter(vec2));
    println(vec2);
    // 9 -> 1
    copy(ivec.begin(), ivec.end(), front_inserter(lst3));
    println(lst3);
}

void test_istream_iterators() {
    //Lazy Evaluation, 使用到迭代器时 才会读
    // std::istream_iterator<int> int_it(cin);  // read ints from cin
    // std::istream_iterator<int> int_eof;  // empty istream_iterator 代表eof
    // vector<int> ivec;
    // while (int_it != int_eof)
    //     ivec.push_back(*int_it++);
    std::istream_iterator<int> int_it(cin), int_eof;
    // vector<int> ivec(int_it, int_eof);
    // println(ivec);
    cout << accumulate(int_it, int_eof, 0) << endl;
}

void test_ostream_iterators() {
    vector<int> ivec{1, 2, 3, 4};
    // 往cout写入 int型数据，followed by 空格
    std::ostream_iterator<int> out_iter(cout, " ");
    // for (auto e: ivec)
    //     *out_iter++ = e;
    copy(ivec.begin(), ivec.end(), out_iter);
    cout << endl;
}

void q_10_29() {
    std::ifstream in(R"(D:\cpp_primer\ch10\words)");
    std::istream_iterator<string> it(in), eof;
    vector<string> svec(it, eof);
    println(svec);
}

void q_10_30() {
    std::istream_iterator<int> iter_int(cin), eof;
    vector<int> ivec(iter_int, eof);
    sort(ivec.begin(), ivec.end());
    std::ostream_iterator<int> out(cout, " ");
    copy(ivec.begin(), ivec.end(), out);
    cout << endl;
}

void q_10_31() {
    std::istream_iterator<int> iter_int(cin), eof;
    vector<int> ivec(iter_int, eof);
    sort(ivec.begin(), ivec.end());
    std::ostream_iterator<int> out(cout, " ");
    unique_copy(ivec.begin(), ivec.end(), out);
    cout << endl;
}

void q_10_32() {
    std::ifstream in(R"(D:\cpp_primer\ch10\item)");
    std::istream_iterator<Sales_item> in_inter(in), in_eof;
    vector<Sales_item> vec(in_inter, in_eof);
    cout << "origin data: \n";
    for_each(vec.begin(), vec.end(), [](const Sales_item &item){cout << item << endl;});
    sort(vec.begin(),vec.end(), [](const Sales_item &a, const Sales_item &b){return a.isbn() < b.isbn();});
    cout << "result: \n";
    for (auto beg = vec.begin(), end = beg; beg != vec.end(); beg = end) {
        // 找到isbn相同的一块
        // Find the first element in a sequence for which a predicate is true. 前面为false 后面为True
        end = find_if(beg, vec.end(),
            [beg](const Sales_item &item){return beg->isbn() != item.isbn();});  // 前面为相同，后面不同
        // 累加相同的，创建一个空的Sales_item
        cout << accumulate(beg, end, Sales_item(beg->isbn())) << endl;
        // beg更新成当前end
    }
}

int q_10_33(const string &in_file, const string &even_file, const string &odd_file) {
    std::ifstream in(in_file);
    std::ofstream ofs_even(even_file), ofs_odd(odd_file);

    std::istream_iterator<int> in_iter(in), eof;
    std::ostream_iterator<int> out_even(ofs_even, "\n"), out_odd(ofs_odd, " ");
    // *out_iter++ = e;
    for_each(in_iter, eof,
        [&out_even, &out_odd](const int i){*(i & 0x01? out_odd: out_even)++ = i;}
        );
    return 0;
}

void test_reverse_iterators() {
    // reverse iterators 需要支持--操作
    vector<int> vec{0 ,1, 2, 4, 6, 5, 7, 9, 8, 3};
    for (auto r_iter=vec.rbegin(); r_iter != vec.rend(); ++r_iter)
        cout << *r_iter << " ";
    cout << endl;
    // sort(vec.begin(), vec.end());

    sort(vec.rbegin(), vec.rend());  // 反序排序
    println(vec);
    std::reverse(vec.begin(), vec.end());
    cout << "reverse 反转" << endl;
    println(vec);

    string line = "FIRST,MIDDLE,LAST";
    auto first_comma = find(line.cbegin(), line.cend(), ',');
    cout << string(line.cbegin(), first_comma) << endl;  // FIRST
    auto last_comma = find(line.crbegin(), line.crend(), ',');
    cout << string(line.crbegin(), last_comma) << endl;   // 反向 TSAL
    cout << string(last_comma.base(), line.cend()) << endl;  // LAST
}

void q_10_35() {
    vector<int> ivec{1, 2, 3, 4, 5 ,6};
    // 迭代器反序， 普通
    for (auto it = std::prev(ivec.cend()); ; --it) {
        cout << *it << ' ';
        if (it == ivec.cbegin()) break;
    }
    cout << endl;
}

void q_10_36() {
    // find last 0
    list<int> lst{1, 2, 0, 4, 0, 111, 0, 355};
    auto last_zero = find(lst.crbegin(), lst.crend(), 0);
    if (last_zero != lst.crend())
        cout << std::distance(last_zero, lst.crend()) << endl;
}

void q_10_37() {
    vector<int> ivec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    list<int> lst(ivec.crbegin()+3, ivec.crend() - 2);

    list<int> l;
    copy(ivec.crbegin() + 3, ivec.crbegin() + 8, back_inserter(l));
    println(lst);
}

void q_10_38() {
    // 输入迭代器 : ==,!=,++,*,->
    // 输出迭代器 : ++,*
    // 前向迭代器 : ==,!=,++,*,->
    // 双向迭代器 : ==,!=,++,--,*,->
    // 随机访问迭代器 : ==,!=,<,<=,>,>=,++,--,+,+=,-,-=,*,->,iter[n]==*(iter+n)
}

void q_10_42_elim_dups(list<string> &words) {
    words.sort();
    words.unique();
    println(words);
}


int main(int *argc, char **argv) {
    list<string> lst{"the", "quick", "red", "fox", "jumps",
        "over", "the", "slow", "red", "turtle", "fox", "interesting", "international"};
    q_10_42_elim_dups(lst);
    q_10_37();
    q_10_36();
    q_10_35();
    test_reverse_iterators();
    // q_10_33(R"(D:\cpp_primer\ch10\int)", R"(D:\cpp_primer\ch10\even)", R"(D:\cpp_primer\ch10\odd)");
    q_10_32();
    q_10_29();
    test_ostream_iterators();
    // test_istream_iterators();
    q_10_28();
    q_10_27_unique_copy();
    test_inserter();
    vector<string> svec{"the", "quick", "red", "fox", "jumps",
        "over", "the", "slow", "red", "turtle", "fox", "interesting", "international"};
    q_10_25(svec, 5);
    q_10_24();
    q_10_22();
    test_bind();
    q_10_21();

    q_10_20_count_if(svec, 6);
    test_lambda_return_type();
    test_multable_lambda();
    test_multable_lambda_2();
    test_lambda_capture();
    q_10_17();
    q_10_15();
    q_10_14_test_lambda();
    q_10_19(svec, 4);
    q_10_18(svec, 4);
    biggies(svec, 5);
    q_10_13_partition();
    q_10_12();
    test_sort_with_predicate();
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
