#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>
#include <vector>
#include <list>
#include <utility>
#include <fstream>
#include <sstream>
#include <unordered_set>

#include "../ch08/Sales_Data.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::map;
using std::set;
using std::vector;
using std::multimap;
using std::multiset;
using std::pair;

void test_map() {
    map<string, size_t> word_count;
    string word;
    while (cin >> word)
        ++word_count[word];
    for (const auto &item : word_count)
        // item pair
        cout << item.first << " occurs " << item.second << ((item.second > 1) ? " times" : " time") << endl;
}

void test_map_set() {
    map<string, size_t> word_count;
    set<string> exclude = {"The", "But", "And", "Or", "An", "A",
                            "the", "but", "and", "or", "an", "a"};
    string word;
    while (cin >> word)
        if (exclude.find(word) == exclude.end())  // 没有找到需要排除的
            ++word_count[word];
    for (const auto &item : word_count)
        // item pair
            cout << item.first << " occurs " << item.second << ((item.second > 1) ? " times" : " time") << endl;
}

void q_11_4() {
    map<string, int> m;
    string word;
    while (cin >> word) {
        // lowercase
        for (auto &ch: word)
            ch = tolower(ch);
        // remove .
        word.erase(  // erase 删除标点部分
            std::remove_if(word.begin(), word.end(), ispunct),  // 去除punc
            word.end());
        ++m[word];
    }
    for (const auto &e : m)
        cout << e.first << " : " << e.second << "\n";
}

void test_associative_container() {
    map<string, string> authors = {
        {"Joyce", "James"},
        {"Austen", "Jane"},
        {"Dickens", "Charles"}
    };
    for (const auto &item : authors) {
        cout << item.first << " : " << item.second << endl;
    }
    vector<int> ivec;
    for (vector<int>::size_type i = 0; i != 10; ++i) {
        ivec.push_back(i);
        ivec.push_back(i); // duplicate copies of each number
    }
    set<int> iset(ivec.cbegin(), ivec.cend());
    multiset<int> miset(ivec.cbegin(), ivec.cend());

    cout << ivec.size() << endl;
    cout << iset.size() << endl;
    cout << miset.size() << endl;

}

void q_11_7() {
    map<string, vector<string>> families = {
    {"Jones", {"Tom", "Jack"}},
    {"Smith", {"James", "Bill"}},
    };
    families.insert({"Lee", {"Sin"}});
    families["Jones"].push_back("Alice");
    for (const auto &item : families) {
        cout << item.first << ": ";
        for (const auto &child: item.second) {
            cout << child << " ";
        }
        cout << endl;
    }
}

void q_11_8() {
    vector<string> svec = {"a", "b", "c", "d", "e"};
    for (string word; cout << "Enter: \n", cin >> word; ) {
        auto is_exclude = std::binary_search(svec.begin(), svec.end(), word);
        cout << (is_exclude ? "excluded" : "not excluded") << endl;
    }
}

void q_11_9() {
    map<string, std::list<int>> a;
}

void q_11_10() {
    /* vector 支持random access， 支持< 操作
     * list 是 双向迭代器 只有++ --的操作
     */
}

bool compareIsbn(const Sales_Data &lhs, const Sales_Data &rhs) {
    return lhs.isbn() < rhs.isbn();
}

void q_11_11() {
    using funcP = bool (*)(const Sales_Data &, const Sales_Data &);
    multiset<Sales_Data, decltype(compareIsbn)*> bookStore(compareIsbn);
    multiset<Sales_Data, funcP> bookStore2(funcP);
}

void test_pair() {
    // utility 下
    pair<string, int> p1("hi", 1);
    pair<string, string> p2("Tom", "Jin");
    pair<string, vector<int>> p3("1", {1, 2, 3});
    cout << p1.first << " " << p1.second << endl;
    string word{"hello"};
    size_t count = 3;
    auto word_count = std::make_pair(word, count);
}

void q_11_12_13() {
    vector<pair<string, int>> ret;
    string s;
    int i;
    while (cin >> s >> i) {
        // ret.push_back(make_pair(s, i));
        ret.push_back({s, i});
        // ret.push_back(pair(s, i));
    }
    for (auto &item : ret)
        cout << item.first << " : " << item.second << endl;
}

class Families {
public:
    using ChildNameBirth = pair<string, string>;
    using ChildInfo = vector<ChildNameBirth>;
    using Data = map<string, ChildInfo>;
    void add(const string &last_name, const string &first_name, const string &birthday) {
        auto child = std::make_pair(first_name, birthday);
        _data[last_name].push_back(child);
    }
    void print() const {
        for (const auto &item : _data) {
            cout << item.first << ": \n";
            for (const auto &child: item.second) {
                cout << child.first << " : " << child.second << "; ";
            }
            cout << endl;
        }
    }
private:
    Data _data;
};

void q_11_14() {
    Families families;
    string info = "Enter the last name , first name, birthday: \n";
    for (string l, f, b; cout << info, cin >> l >> f >> b; families.add(l, f, b));
    families.print();
}

void test_associative_container_iterators() {
    map<string, int> word_cnt = {{"a", 1}, {"b", 22}};
    auto map_it = word_cnt.begin();
    cout << map_it->first << " " << (*map_it).second << "\n";
    // map_it->first = "new_key";  // key 是 const
    ++map_it->second;
    cout << map_it->first << " " << map_it->second << "\n";

    set<int> iset = {0,1,2,3,4,5,6,7,8,9};
    set<int>::iterator set_it = iset.begin();
    if (set_it != iset.end()) {
        // *set_it = 42; // error: keys in a set are read-only
        cout << *set_it << endl; // ok: can read the key
    }
}

void q_11_16 () {
    map<string, int> word_cnt = {{"a", 1}, {"b", 22}};
    auto map_it = word_cnt.begin();
    map_it->second = 23;
}

template <typename Sequence>
auto println(Sequence const &seq) -> std::ostream& {
    for (auto const &item: seq) {
        cout << item  << " ";
    }
    return cout << endl;
}


void q_11_17() {
    multiset<string> c{"a", "c", "a", "d"};
    vector<string> v{"A", "B", "C"};
    // std::copy(v.begin(), v.end(), std::inserter(c, c.end()));  // legal
    // std::copy(v.begin(), v.end(), std::back_inserter(c));  // multiset 没有push_back
    // std::copy(c.begin(), c.end(), std::inserter(v, v.end()));  // legal
    std::copy(c.begin(), c.end(), std::back_inserter(v));  // legal
    println(v);
}

void q_11_18() {
    map<string, int> word_cnt = {{"a", 1}, {"b", 22}};
    // auto map_it = word_cnt.begin();
    map<string, int>::iterator map_it = word_cnt.begin();
    map_it->second = 23;
}

void q_11_19() {
    using funcP = bool (*)(const Sales_Data &lhs, const Sales_Data &rhs);
    // // multiset<Sales_Data, decltype(compareIsbn)*> bookstore(compareIsbn);
    std::multiset<Sales_Data, funcP> bookStore1(compareIsbn);
    std::multiset<Sales_Data, funcP>::iterator book_it = bookStore1.begin();
}

void test_add_element() {
    map<string, size_t> word_cnt = {{"a", 1}, {"b", 22}};
    string word = "the";
    // 插入位置，是否插入
    auto res = word_cnt.insert({word, 1});  // 最简便的方法
    // word_cnt.insert(std::make_pair(word, 1));
    // word_cnt.insert(pair<string, size_t>(word, 1));
    // word_cnt.insert(map<string, size_t>::value_type(word, 1));
    cout << std::boolalpha << res.second << endl;
}

void test_return_from_insert() {
    map<string, size_t> word_cnt = {{"a", 1}, {"b", 22}};
    string word;
    while (cin >> word) {
        auto ret = word_cnt.insert({word, 1});
        if (!ret.second)
            ++ret.first->second;
    }
    for (auto &item: word_cnt)
        cout << item.first << " : " << item.second << endl;
}

void q_11_22() {
    map<string, vector<int>> cnt;
    auto ret = cnt.insert({"a", {1, 2, 3}});
    pair<map<string, vector<int>>::iterator, bool> ret2 = cnt.insert({"b", {1, 2, 3}});

}

void q_11_23() {
    multimap<string, vector<string>> families = {
        {"Jones", {"Tom", "Jack"}},
        {"Smith", {"James", "Bill"}},
        };
    families.insert({"Jones", {"Sin"}});
    for (const auto &item : families) {
        cout << item.first << ": ";
        for (const auto &child: item.second) {
            cout << child << " ";
        }
        cout << endl;
    }
}

void test_erase() {
    map<string, size_t> word_cnt = {{"a", 1}, {"b", 22}};
    multiset<string> c{"a", "c", "a", "d"};
    word_cnt.erase("a");
    word_cnt.erase("A");

    c.erase("a");
    println(c);
}

void test_subscript() {
    map<string, size_t> word_cnt = {{"a", 1}, {"b", 22}};
    // word_cnt.at("x"); // out of range

    word_cnt["x"] = 1;
    ++word_cnt["Y"];  // lvalue
    cout << word_cnt["Y"] << endl;

}

void q_11_26() {
    map<int, string> m{{1, "a"}};
    using key_type = map<int, string>::key_type;
    using ret_type =  map<int, string>::mapped_type;
}

void test_find() {
    map<string, size_t> word_cnt = {{"a", 1}, {"b", 22}};
    if (word_cnt.find("foo") == word_cnt.end())
        cout << "foo is not in the map" << endl;

    multimap<string, string> authors{
        {"Alain de Botton", "Book1"},
        {"Alice", "Book2"},
        {"Alice", "Book3"},
        {"Bob", "Book4"}
    };
    string search_item("Alice");
    auto entries = authors.count(search_item);
    auto iter = authors.find(search_item);
    while (entries) {
        cout << iter->second << endl;
        ++iter;  // 有序，相同key的放在一起
        --entries;
    }

    // 使用迭代器
    // lower_bound : not less than, 开始位置 [
    // upper_bound : great than 结束位置 )
    for (auto beg = authors.lower_bound(search_item), end = authors.upper_bound(search_item); beg != end; ++beg)
        cout << beg->second << endl;

    // equal range
    for (auto pos = authors.equal_range(search_item); pos.first != pos.second; ++pos.first)
        cout << pos.first->second << endl;
}

void q_11_27() {
    // count : multimap, multiset 有多个相同的key
    // find : set, map 相同的key只有一个
}

void q_11_28() {
    map<string, vector<int>> m{{"a", {1, 2, 3, 4}}};
    map<string, vector<int>>::iterator result = m.find("a");
}

void q_11_29() {
    //set: a b c e f  ,  search_item d
    // upper_bound 第一个大于search_item的位置 e
    // lower_bound 第一个不小于 的位置， e
    // equal_range  e e
    set<string> s{"a", "b", "c", "e", "f"};
    auto lower = s.lower_bound("d");
    auto upper = s.upper_bound("d");
    auto pos = s.equal_range("d");
    cout << *lower << " " << *upper << endl;
    cout << *pos.first << " " << *pos.second << endl;
}

void q_11_30() {
    // pos.first->second
    // pos 是pair
    // pos.first  equal_range的找到的第一个迭代器，
    // pos.first->second 访问第二个成员 val
}

void q_11_31() {
    multimap<string, string> authors{
            {"Alain de Botton", "Book1"},
            {"Alice", "Book2"},
            {"Alice", "Book3"},
            {"Bob", "Book3"}
    };
    string name("Alice");
    string word("Book3");
    auto entries = authors.count(name);
    auto iter = authors.find(name);
    while (entries) {
        if (iter->second == word) {
            authors.erase(iter);
            break;
        }
        --entries;
        ++iter;
    }
    for (auto &item : authors) {
        cout << item.first << " : " << item.second << endl;
    }
}

void q_11_32() {
    multimap<string, string> authors{
		    { "alan", "DMA" },
            { "pezy", "LeetCode" },
            { "alan", "CLRS" },
            { "wang", "FTP" },
            { "pezy", "CP5" },
            { "wang", "CPP-Concurrency" } };
    map<string, multiset<string>> ordered_authors;  // name， work都有序
    for (auto &item : authors)
        ordered_authors[item.first].insert(item.second);
    for (auto &item: ordered_authors) {
        cout << "author name : " << item.first << "\n";
        cout << "works: ";
        for (auto &work: item.second) {
            cout << work << " " ;
        }
        cout << endl;
    }
}

std::unordered_map<string, string> build_map(std::ifstream &map_file) {
    // map<string, string> trans_map;
    std::unordered_map<string, string> trans_map;
    for (string key, value; map_file >> key && std::getline(map_file, value); ) {
        if (value.size() > 1)  // key空格v  value的长度要大于1
            trans_map[key] = value.substr(1);  // 跳过leading space
        // 多个相同key， 使用下标运算符会保留最后一次添加的规则，而用insert则保留第一次添加的规则
        //  trans_map.insert({key, value.substr(1)});
        else
            throw std::runtime_error("no rule for " + key);
    }
    return trans_map;
}

const string &transform(const string &s, const std::unordered_map<string, string> &m) {
    auto map_it = m.find(s);  // 使用 m[s] s若不在m中，会额外插入
    return map_it == m.cend() ? s : map_it->second;
}


void word_transform(std::ifstream &map_file, std::ifstream &input) {
    auto trans_map = build_map(map_file);
    for (string text; std::getline(input, text);) {  // 读每一行
        std::istringstream stream(text);   // 字符串流，
        for (string word; stream >> word;) {
            cout << transform(word, trans_map) << " ";
        }
        cout << endl;   // 行结束
    }
}

size_t hasher(const Sales_Data &sd) {
    return std::hash<string>() (sd.isbn());
}

bool eqOP(const Sales_Data &lhs, const Sales_Data &rhs) {
    return lhs.isbn() == rhs.isbn();
}

void test_unordered_containers() {
    /* 使用hash function
     * key没有顺序关系, 必须支持hash处理，int long float double pointer string
     */
    std::unordered_map<string, size_t> word_cnt;
    for (string word; cin >> word; ) {
        ++word_cnt[word];
    }
    for (auto &item : word_cnt) {
        cout << item.first << " : " << item.second << endl;
    }
    cout << word_cnt.bucket_count() << endl;

    using SD_multiset = std::unordered_set<Sales_Data, decltype(hasher) *, decltype(eqOP) *>;
    SD_multiset bookStore(42, hasher, eqOP);
}

void q_11_37() {
    // ordered vs unordered
    // 无序容器拥有更好的性能，有序容器使得元素始终有序。
}


int main(int argc, char *argv[]) {
    // test_unordered_containers();
    std::ifstream map_file("/mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch11/rule");
    std::ifstream text("/mnt/d/wjl/wjl_workspace/Cpp_Primer_Practice/cpp_source/ch11/text");
    word_transform(map_file, text);
    q_11_32();
    q_11_31();
    q_11_29();
    test_find();
    test_subscript();
    test_erase();
    q_11_23();
    // test_return_from_insert();
    q_11_19();
    q_11_17();
    test_associative_container_iterators();
    // q_11_14();
    // q_11_12_13();
    test_pair();
    // q_11_8();
    q_11_7();
    test_associative_container();
    // q_11_4();
    // test_map_set();
    return 0;
}
