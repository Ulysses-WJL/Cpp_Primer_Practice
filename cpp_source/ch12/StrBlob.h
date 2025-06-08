//
// Created by bruce on 2025/6/7.
//

#ifndef STRBLOB_H
#define STRBLOB_H

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>
#include <stdexcept>


class StrBlob {
public:
    using size_type = std::vector<std::string>::size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);  // 使用 {""} 初始化
    size_type size() const {return data->size();};  // 不修改非静态成员的 定义为const
    bool empty() const {return data->empty(); };
    void push_back(const std::string &t);
    void pop_back();
    std::string &front() const;
    std::string &back() const;

private:
    std::shared_ptr<std::vector<std::string>> data;

    void check(size_type i, const std::string &msg) const;
};

inline StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) {

}

inline StrBlob::StrBlob(std::initializer_list<std::string> il): data(std::make_shared<std::vector<std::string>>(il)) {

}


inline void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

inline void StrBlob::push_back(const std::string &t) {
    data->push_back(t);
}

inline void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

inline std::string &StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

inline std::string &StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}


#endif //STRBLOB_H
