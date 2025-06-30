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

TextQuery::TextQuery(std::ifstream &ifs) //: file_text(new std::vector<std::string>)
{
    for (std::string s; getline(ifs, s);) {
        file_text.push_back(s);
        auto n = file_text.size() - 1;  // 当前行，行号
        std::istringstream line(s);  // 字符串种读取单词

        for (std::string word, clean_word, lower_word; line >> word; clean_word.clear()) {
            lower_word = toLowerCase(word);
            std::remove_copy_if(lower_word.begin(), lower_word.end(), std::back_inserter(clean_word), ispunct);
            auto &line_nos = word_map[clean_word];  // 单词对应的行号 引用类型
            if (!line_nos)
                // nullptr, 新单词，新分配一个set
                    line_nos.reset(new std::set<StrBlob::size_type>);
            line_nos->insert(n);  // set中插入当前行
        }
    }
}

QueryResult TextQuery::query(const std::string &word) const{

    // 查询的结果，静态变量，初始为空
    static std::shared_ptr<std::set<StrBlob::size_type>> nodata(new std::set<StrBlob::size_type>);
    auto loc = word_map.find(word);
    if (loc == word_map.end()) {
        // not found
        return QueryResult(word, nodata, file_text);
    } else {
        return QueryResult(word, loc->second, file_text);
    }
}

std::ostream &print(std::ostream &os, const QueryResult &res) {
    os << res.word << " occurs " << res.numbers->size() << " time" << (res.numbers->size() > 1 ? "s":"") << std::endl;
    // for (auto num : *res.numbers) {
    //     ConstStrBlobPtr p(res.file_text, num);  // 需要使用Blob时，使用对应weak_ptr
    //     os << "\t(line " << num + 1 << ") " << p.deref() << std::endl;
    // }
    for (auto it = res.begin(); it != res.end(); ++it) {
        ConstStrBlobPtr p(res.file_text, *it);
        os << "\t(line " << *it + 1 << ") " << p.deref() << std::endl;
    }
    return os;
}
