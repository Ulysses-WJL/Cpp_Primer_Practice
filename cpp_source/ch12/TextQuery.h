#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include <map>
#include <memory>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include "StrBlob.h"

class QueryResult;  // 用来保存查询结果，出现次数，行号，文本内容

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);  // 构造函数，输入文本
    QueryResult query(const std::string &) const;  // 查询接口
private:
    // 使用 shared_ptrs 同步管理 lifetime
    // std::shared_ptr<std::vector<std::string>> file_text;  // 文本 句子
    StrBlob file_text;
    std::map<std::string, std::shared_ptr<std::set<line_no>>>  word_map;  // word: {出现的line_no}
};


class QueryResult {
public:
    // 打印结果
    friend std::ostream& print(std::ostream&, const QueryResult&);
    using Iterator = std::set<TextQuery::line_no>::iterator;
    // constructor
    QueryResult(
        std::string s,
        std::shared_ptr<std::set<StrBlob::size_type>> n,
        const StrBlob &l) : word(s), numbers(n), file_text(l) {};
    Iterator begin() const {return numbers->begin();}
    Iterator end() const {return numbers->end();}
    std::shared_ptr<StrBlob> get_file() const {return std::make_shared<StrBlob>(file_text);}
private:
    std::string word;  //
    std::shared_ptr<std::set<TextQuery::line_no>> numbers;  // word对应行号
    // std::shared_ptr<std::vector<std::string>> file_text; // 原始文本
    StrBlob file_text;
};

std::ostream& print(std::ostream&, const QueryResult&);
std::string toLowerCase(const std::string& input);
#endif //TEXTQUERY_H
