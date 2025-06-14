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

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob {
public:
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;
    StrBlobPtr begin();
    StrBlobPtr end();
    ConstStrBlobPtr cbegin() const;
    ConstStrBlobPtr cend() const;
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

class StrBlobPtr {
public:
    friend bool operator==(const StrBlobPtr &, const StrBlobPtr &);
    friend bool operator!=(const StrBlobPtr &, const StrBlobPtr &);
    StrBlobPtr() : curr_idx(0) {}; // wptr 为null
    // a.data 需要在StrBlob中定义友元
    explicit StrBlobPtr(StrBlob &a, size_t sz=0): wptr(a.data), curr_idx(sz) {}  // wptr指向对应的shared_ptr
    std::string& deref() const;
    StrBlobPtr& incr();
private:
    // check returns a shared_ptr to the vector if the check succeeds
    // 函数不会修改类的任何非 `mutable` 成员变量； 支持常量对象调用
    std::shared_ptr<std::vector<std::string>> check(size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr_idx;
};

class ConstStrBlobPtr {
public:
    friend bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    ConstStrBlobPtr() : curr_idx(0) {}; // wptr 为null
    // a.data 需要在StrBlob中定义友元
    explicit ConstStrBlobPtr(const StrBlob &a, size_t sz=0): wptr(a.data), curr_idx(sz) {}  // wptr指向对应的shared_ptr
    std::string& deref() const;
    ConstStrBlobPtr& incr();
private:
    // check returns a shared_ptr to the vector if the check succeeds
    // 函数不会修改类的任何非 `mutable` 成员变量； 支持常量对象调用
    std::shared_ptr<std::vector<std::string>> check(size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr_idx;
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

inline StrBlobPtr StrBlob::begin() {
    // StrBlobPtr的wptr 指向 StrBlob对象
    return  StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end() {
    return StrBlobPtr(*this, data->size());
}

inline ConstStrBlobPtr StrBlob::cbegin() const {
    return ConstStrBlobPtr(*this);
}

inline ConstStrBlobPtr StrBlob::cend() const {
    return ConstStrBlobPtr(*this, data->size());
}


inline std::shared_ptr<std::vector<std::string> > StrBlobPtr::check(size_t i, const std::string &msg) const {
    // 先check StrBlob
    auto ret = wptr.lock();
    if (!ret) {
        throw std::runtime_error("Unbound StrBlobPtr");
    }
    if (i >= ret->size()) {
        // StrBlob 没有这么多元素
        throw std::out_of_range(msg);
    }
    return ret;
}

inline std::string &StrBlobPtr::deref() const {
    // auto p = check(curr_idx, "deref on empty StrBlobPtr");
    // return (*p)[curr_idx];
    return (*check(curr_idx, "dereference past end"))[curr_idx];  // 作用相同，可读性较差
}

inline StrBlobPtr &StrBlobPtr::incr() {
    check(curr_idx, "increment past end of StrBlobPtr");
    ++curr_idx;
    return *this;  // return a reference to the incremented object
}

inline bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    // 检查use_count
    if (!lhs.wptr.expired() && !rhs.wptr.expired()) {
        // 两个ptr指向同一个，index也要相同
        return (lhs.wptr.lock() == rhs.wptr.lock()) &&( lhs.curr_idx == rhs.curr_idx);
    } else {
        return false;
    }
}

inline bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return !(lhs == rhs);
}

inline bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    // 检查use_count
    if (!lhs.wptr.expired() && !rhs.wptr.expired()) {
        // 两个ptr指向同一个，index也要相同
        return (lhs.wptr.lock() == rhs.wptr.lock()) &&( lhs.curr_idx == rhs.curr_idx);
    } else {
        return false;
    }
}

inline bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return !(lhs == rhs);
}

inline std::shared_ptr<std::vector<std::string> > ConstStrBlobPtr::check(size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret) {
        throw std::runtime_error("Unbound ConstStrBlobPtr");
    }
    if (i >= ret->size()) {
        throw std::out_of_range(msg);
    }
    return ret;
}

inline std::string &ConstStrBlobPtr::deref() const {
    auto p = check(curr_idx, "deref on empty StrBlobPtr");
    return (*p)[curr_idx];
}

inline ConstStrBlobPtr &ConstStrBlobPtr::incr() {
    check(curr_idx, "increment past end of ConstStrBlobPtr");
    ++curr_idx;
    return *this;
}


#endif //STRBLOB_H
