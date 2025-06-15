#include "TextQuery.h"

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // std::transform


std::string toLowerCase(const std::string& input) {
    std::string result = input; // 创建一个副本以避免修改原始字符串
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

TextQuery::TextQuery(std::ifstream &ifs) : file_text(new std::vector<std::string>) {
    for (std::string s; getline(ifs, s);) {
        file_text->push_back(s);
        int n = file_text->size() - 1;  // 当前行，行号
        std::istringstream line(s);  // 字符串种读取单词
        for (std::string word; line >> word; ) {
            std::string lower_word = toLowerCase(word);
            auto &line_nos = word_map[lower_word];  // 单词对应的行号
            if (!line_nos)
                // nullptr, 没找到，重置
                line_nos.reset(new std::set<line_no>);
            line_nos->insert(n);  // set中插入当前行
        }
    }
}

QueryResult TextQuery::query(const std::string &word) const{

    // 查询的结果，静态变量，初始为空
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = word_map.find(word);
    if (loc == word_map.end()) {
        // not find
        return QueryResult(word, nodata, file_text);
    } else {
        return QueryResult(word, loc->second, file_text);
    }
}

std::ostream &print(std::ostream &os, const QueryResult &res) {
    os << res.word << " occurs " << res.numbers->size() << " time" << (res.numbers->size() > 1 ? "s":"") << std::endl;
    for (auto num : *res.numbers) {
        os << "\t(line " << num + 1 << ") " << *(res.file_text->begin() + num) << std::endl;
    }
    return os;
}
