#ifndef STRBLOB_H
#define STRBLOB_H

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

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
    void push_back(std::string &&);   // q_13_55
    void pop_back();
    std::string &front() const;
    std::string &back() const;
    long count() const {return data.use_count();}

    StrBlob(const StrBlob &);
    StrBlob& operator=(const StrBlob &rhs);
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
    long count() const {return wptr.use_count();}
private:
    // check returns a shared_ptr to the vector if the check succeeds
    // 函数不会修改类的任何非 `mutable` 成员变量； 支持常量对象调用
    std::shared_ptr<std::vector<std::string>> check(size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr_idx;
};
#endif //STRBLOB_H
