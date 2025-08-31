#ifndef STRBLOB_H
#define STRBLOB_H

#include <string>
#include <vector>
#include <memory>
#include <initializer_list>

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob {
    friend class ConstStrBlobPtr;
    friend class StrBlobPtr;
    friend bool operator==(const StrBlob&, const StrBlob&);
    friend bool operator!=(const StrBlob&, const StrBlob&);
    friend bool operator< (const StrBlob&, const StrBlob&);
    friend bool operator> (const StrBlob&, const StrBlob&);
    friend bool operator<=(const StrBlob&, const StrBlob&);
    friend bool operator>=(const StrBlob&, const StrBlob&);
public:
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
    std::string& operator[](size_type i);
    const std::string& operator[](size_type i) const;
private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

bool operator==(const StrBlob&, const StrBlob&);
bool operator!=(const StrBlob&, const StrBlob&);
bool operator< (const StrBlob&, const StrBlob&);
bool operator> (const StrBlob&, const StrBlob&);
bool operator<=(const StrBlob&, const StrBlob&);
bool operator>=(const StrBlob&, const StrBlob&);

/* q_14_31
* Our StrBlobPtr class does not define the copy constructor, assignment
operator, or a destructor. Why is that okay?
使用Synthesized ones 就可以了，因为没有需要动态分配相关的处理
 */
class StrBlobPtr {
    friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator< (const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator> (const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
    friend bool operator>=(const StrBlobPtr&, const StrBlobPtr&);
public:
    StrBlobPtr() : curr_idx(0) {}; // wptr 为null
    // a.data 需要在StrBlob中定义友元
    explicit StrBlobPtr(StrBlob &a, size_t sz=0): wptr(a.data), curr_idx(sz) {}  // wptr指向对应的shared_ptr
    std::string& deref() const;
    StrBlobPtr& incr();
    // prefix
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    // postfix，
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);
    StrBlobPtr& operator+=(size_t);
    StrBlobPtr& operator-=(size_t);
    StrBlobPtr operator+(size_t) const;
    StrBlobPtr operator-(size_t) const;
    // member access  * ->
    std::string& operator*() const;
    std::string* operator->() const;

    std::string& operator[](size_t);
    const std::string& operator[](size_t) const;
private:
    // check returns a shared_ptr to the vector if the check succeeds
    // 函数不会修改类的任何非 `mutable` 成员变量； 支持常量对象调用
    std::shared_ptr<std::vector<std::string>> check(size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr_idx;
};

bool operator==(const StrBlobPtr&, const StrBlobPtr&);
bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
bool operator< (const StrBlobPtr&, const StrBlobPtr&);
bool operator> (const StrBlobPtr&, const StrBlobPtr&);
bool operator<=(const StrBlobPtr&, const StrBlobPtr&);
bool operator>=(const StrBlobPtr&, const StrBlobPtr&);

// q_14_32
class StrBlobPtr_Ptr {
public:
    StrBlobPtr_Ptr() = default;
    explicit StrBlobPtr_Ptr(StrBlobPtr* p) : pointer(p) {}

    StrBlobPtr& operator*() const;
    StrBlobPtr* operator->() const;
private:
    StrBlobPtr* pointer=nullptr;
};

class ConstStrBlobPtr {
    friend bool operator< (const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator> (const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator<=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator>=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
    friend bool operator==(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
    friend bool operator!=(const ConstStrBlobPtr &, const ConstStrBlobPtr &);
public:
    ConstStrBlobPtr() : curr_idx(0) {}; // wptr 为null
    // a.data 需要在StrBlob中定义友元
    explicit ConstStrBlobPtr(const StrBlob &a, size_t sz=0): wptr(a.data), curr_idx(sz) {}  // wptr指向对应的shared_ptr
    std::string& deref() const;
    ConstStrBlobPtr& incr();
    long count() const {return wptr.use_count();}
    const std::string &operator[](size_t) const;
    ConstStrBlobPtr& operator+=(size_t);
    ConstStrBlobPtr& operator-=(size_t);
    ConstStrBlobPtr operator+(size_t);
    ConstStrBlobPtr operator-(size_t);
    std::string& operator*() const;
    std::string* operator->() const;
private:
    // check returns a shared_ptr to the vector if the check succeeds
    // 函数不会修改类的任何非 `mutable` 成员变量； 支持常量对象调用
    std::shared_ptr<std::vector<std::string>> check(size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    size_t curr_idx;
};
bool operator==(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator!=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator< (const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator> (const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator<=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
bool operator>=(const ConstStrBlobPtr&, const ConstStrBlobPtr&);
#endif //STRBLOB_H
