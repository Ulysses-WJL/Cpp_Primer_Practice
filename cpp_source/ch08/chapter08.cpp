//
// Created by w30065676 on 2025/5/12.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Sales_Data.h"

using std::cin;
using std::cin;
using std::cout;
using std::endl;
using std::flush;
using std::ends;
using std::unitbuf;
using std::nounitbuf;
using std::cerr;
using std::vector;
using std::string;


std::istream &q_8_1(std::istream &is) {
    std::string s;
    while (is >> s) {
        std::cout << s << std::endl;
    }
    is.clear();  // Reset the condition of s to flags
    return is;
}


void test_flushing() {
    cout << "hi" << endl;
    cout << "hi" << flush;  // adds no data
    cout << "hi" << ends;  // 插入一个null character 再flush

    cout << unitbuf;  // all writes will be flushed immediately
    cout << 123;
    cout << 456;
    cout << nounitbuf;  // 恢复buffering
    cout << 789;
    cout << 110;
    cout << endl;
    // 如何确保崩溃时输出被刷新？ 显式调用 flush， 使用cerr stderr

    // cin and cerr are both tied to cout
    // cin 读取时，buffer会刷新
    // cin.tie(&cout);
    std::ostream *old_tie = cin.tie(nullptr);  // cin is no longer tied
    cin.tie(&std::cerr);  // reading cin flushes cerr, not cout
    cin.tie(old_tie);  // reestablish normal tie between cin and cout

}


void q_8_4_reading_file() {
    std::string file_name = "in";
    std::vector<std::string> vec;
    std::ifstream in(file_name);
    std::string s = "";
    while (getline(in, s)) {
        vec.push_back(s);
    }
    for (auto &item: vec) {
        cout << item << "\n";
    }
}

void q_8_5_reading_file() {
    std::string file_name = "in";
    std::vector<std::string> vec;
    std::ifstream in(file_name);
    std::string s = "";
    while (in >> s) {
        vec.push_back(s);
    }
    for (auto &item: vec) {
        cout << item << "\n";
    }
}

void q_8_6(std::ifstream &input) {
    Sales_Data total;
    if (read(input, total)) {
        Sales_Data trans;
        while (read(input, trans)) {
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);
            } else {
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
    } else {
        std::cerr << "No data?!" << std::endl;
    }
}

void q_8_7(std::ifstream &input, std::ofstream &out) {
    Sales_Data total;
    if (read(input, total)) {
        Sales_Data trans;
        while (read(input, trans)) {
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);
            } else {
                print(out, total) << endl;
                total = trans;
            }
        }
        print(out, total) << endl;
    } else {
        std::cerr << "No data?!" << std::endl;
    }
}

void q_8_9() {
    std::istringstream str("hello");
    q_8_1(str);
}

int q_8_10() {
    std::ifstream ifs("input_data");
    if (!ifs) {
        cerr << "no data" << endl;
        return -1;
    }
    vector<string> vec;
    string line;
    while (getline(ifs, line)) {
        vec.push_back(line);
    }
    // 每一行的 每个单词
    for (auto &item: vec) {
        std::istringstream istr(item);
        string word;
        while (istr >> word) {
            cout << word << " ";
        }
        cout << '\n';
    }
    return 0;
}


struct PersonInfo {
    string name;
    vector<string> phones;
};


void q_8_11() {
    string line, word; // will hold a line and word from input, respectively
    vector<PersonInfo> people; // will hold all the records from the input
    // read the input a line at a time until cin hits end-of-file (or another error)
    std::istringstream record;
    while (getline(cin, line)) {
        PersonInfo info; // create an object to hold this record’s data
        record.clear();
        record.str(line);
        record >> info.name; // read the name
        while (record >> word) // read the phone numbers
            info.phones.push_back(word); // and store them
        people.push_back(info); // append this record to people
    }
    for (auto &p : people)
    {
        std::cout << p.name << " ";
        for (auto &s : p.phones)
            std::cout << s << " ";
        std::cout << std::endl;
    }
}

void q_8_12(std::ifstream &ifs) {
    string line, word; // will hold a line and word from input, respectively
    vector<PersonInfo> people; // will hold all the records from the input
    // read the input a line at a time until cin hits end-of-file (or another error)
    std::istringstream record;
    while (getline(ifs, line)) {
        PersonInfo info; // create an object to hold this record’s data
        record.clear();
        record.str(line);
        record >> info.name; // read the name
        while (record >> word) // read the phone numbers
            info.phones.push_back(word); // and store them
        people.push_back(info); // append this record to people
    }
    for (const auto &p : people)
    {
        std::cout << p.name << " ";
        for (const auto &s : p.phones)
            std::cout << s << " ";
        std::cout << std::endl;
    }
}


int main(int argc, char **argv) {
    std::ifstream ifs("info");
    q_8_12(ifs);
    // q_8_11();
    q_8_10();
    q_8_9();
    // std::ofstream out("output_data");  // out trunc implict
    // std::ofstream out("output_data", std::ios::app);  // append模式
    // out << "/n test";
    // std::ifstream input(argv[1]);
    // std::ofstream output(argv[2]);
    // q_8_7(input, output);
    // q_8_6(input);
    // 清除failbit 和 badbit
    q_8_5_reading_file();
    q_8_4_reading_file();
    test_flushing();
    cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit);
    // std::istream &is = q_8_1(std::cin);
    // std::cout << is.rdstate() << std::endl;
    return 0;
}
