#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <cctype>
#include <vector>
#include <list>
#include <utility>

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


int main(int argc, char *argv[]) {
    q_11_14();
    // q_11_12_13();
    test_pair();
    // q_11_8();
    q_11_7();
    test_associative_container();
    // q_11_4();
    // test_map_set();
    return 0;
}