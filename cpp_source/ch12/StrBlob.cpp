#include "StrBlob.h"
#include <stdexcept>
#include <iostream>

StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) {

}

StrBlob::StrBlob(const StrBlob &rhs) : data(std::make_shared<std::vector<std::string>>(*rhs.data)) {}

StrBlob& StrBlob::operator=(const StrBlob &rhs) {
    if (&rhs != this) {
        data = std::make_shared<std::vector<std::string>>(*rhs.data);
    }
    return *this;
}

StrBlob::StrBlob(std::initializer_list<std::string> il): data(std::make_shared<std::vector<std::string>>(il)) {

}


void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size())
        throw std::out_of_range(msg);
}

bool operator==(const StrBlob &lhs, const StrBlob &rhs)
{
    return *lhs.data == *rhs.data;
}

bool operator!=(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(lhs == rhs);
}

bool operator< (const StrBlob &lhs, const StrBlob &rhs)
{
    return std::lexicographical_compare(lhs.data->begin(), lhs.data->end(), rhs.data->begin(), rhs.data->end());
}

bool operator> (const StrBlob &lhs, const StrBlob &rhs)
{
    return rhs < lhs;
}

bool operator<=(const StrBlob &lhs, const StrBlob &rhs)
{
    return !(rhs < lhs);
}

bool operator>=(const StrBlob &lhs, const StrBlob &rhs) {
    return !(lhs < rhs);
}

std::string& StrBlob::operator[](size_t n)
{
    check(n, "out of range");
    return data->at(n);
}

const std::string& StrBlob::operator[](size_t n) const
{
    check(n, "out of range");
    // return data->at(n);
    return (*data)[n];
}


void StrBlob::push_back(const std::string &t) {
    std::cout << "using lvalue version" << std::endl;
    data->push_back(t);
}

void StrBlob::push_back(std::string &&t) {
    std::cout << "using rvalue version" << std::endl;
    data->push_back(std::move(t));
}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::string &StrBlob::front() const {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string &StrBlob::back() const {
    check(0, "back on empty StrBlob");
    return data->back();
}

StrBlobPtr StrBlob::begin() {
    // StrBlobPtr的wptr 指向 StrBlob对象
    return  StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end() {
    return StrBlobPtr(*this, data->size());
}

ConstStrBlobPtr StrBlob::cbegin() const {
    return ConstStrBlobPtr(*this);
}

ConstStrBlobPtr StrBlob::cend() const {
    return ConstStrBlobPtr(*this, data->size());
}


std::shared_ptr<std::vector<std::string> > StrBlobPtr::check(size_t i, const std::string &msg) const {
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

std::string &StrBlobPtr::deref() const {
    // auto p = check(curr_idx, "deref on empty StrBlobPtr");
    // return (*p)[curr_idx];
    return (*check(curr_idx, "dereference past end"))[curr_idx];  // 作用相同，可读性较差
}

StrBlobPtr &StrBlobPtr::incr() {
    check(curr_idx, "increment past end of StrBlobPtr");
    ++curr_idx;
    return *this;  // return a reference to the incremented object
}

StrBlobPtr & StrBlobPtr::operator++() {
    // if curr already points past the end of the container, can’t increment it
    check(curr_idx, "increment past end of StrBlobPtr");
    ++curr_idx;
    return *this;
}

StrBlobPtr & StrBlobPtr::operator--() {
    --curr_idx;  // 当curr_index 为0， 会变为一个large positive value
    // if curr is zero, decrementing it will yield an invalid subscript
    check(curr_idx, "decrement past begin of StrBlobPtr");
    return *this;
}

StrBlobPtr StrBlobPtr::operator++(int) {
    // postfix, 返回的是 old value，返回值类型不能是reference
    StrBlobPtr ret = *this;
    ++*this;  // 调用prefix 的++
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int) {
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

StrBlobPtr & StrBlobPtr::operator+=(size_t n) {
    curr_idx += n;
    check(curr_idx, "increment past end of StrBlobPtr");
    return *this;
}

StrBlobPtr & StrBlobPtr::operator-=(size_t n) {
    curr_idx -= n;
    check(curr_idx, "decrement past begin of StrBlobPtr");
    return *this;
}

StrBlobPtr StrBlobPtr::operator+(size_t n) const {
    StrBlobPtr ret = *this;
    return ret += n;
}

StrBlobPtr StrBlobPtr::operator-(size_t n) const {
    StrBlobPtr ret = *this;
    return ret -= n;
}

std::string & StrBlobPtr::operator*() const {
    // dereference: 访问当前ptr（curr_idx 所指的string）
    auto p = check(curr_idx, "dereference past end");
    // 返回对应的string
    return (*p)[curr_idx];  // *p：vector<string>，
}

std::string * StrBlobPtr::operator->() const {
    // 实际使用deference 操作, 返回地址
    return &this->operator*();
}

std::string & StrBlobPtr::operator[](size_t n) {
    auto p = check(n, "iterator past end of StrBlobPtr");
    return (*p)[n];
}

const std::string & StrBlobPtr::operator[](size_t n) const {
    auto p = check(n, "iterator past end of StrBlobPtr");
    return (*p)[n];
}

bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    // 检查use_count
    if (!lhs.wptr.expired() && !rhs.wptr.expired()) {
        // 两个ptr指向同一个，index也要相同
        return (lhs.wptr.lock() == rhs.wptr.lock()) &&( lhs.curr_idx == rhs.curr_idx);
    } else {
        return false;
    }
}

bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
    return !(lhs == rhs);
}

bool operator< (const StrBlobPtr &x, const StrBlobPtr &y)
{
    return x.curr_idx < y.curr_idx;
}

bool operator>(const StrBlobPtr &x, const StrBlobPtr &y)
{
    return x.curr_idx > y.curr_idx;
}

bool operator<=(const StrBlobPtr &x, const StrBlobPtr &y)
{
    return x.curr_idx <= y.curr_idx;
}

bool operator>=(const StrBlobPtr &x, const StrBlobPtr &y)
{
    return x.curr_idx >= y.curr_idx;
}

StrBlobPtr & StrBlobPtr_Ptr::operator*() const {
    // 返回指向的 StrBlobPtr 的引用
    return *pointer;
}

StrBlobPtr * StrBlobPtr_Ptr::operator->() const {
    // 返回指向的 StrBlobPtr 的指针
    return pointer;
}

bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    // 检查use_count
    if (!lhs.wptr.expired() && !rhs.wptr.expired()) {
        // 两个ptr指向同一个，index也要相同
        return (lhs.wptr.lock() == rhs.wptr.lock()) &&( lhs.curr_idx == rhs.curr_idx);
    } else {
        return false;
    }
}

bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
    return !(lhs == rhs);
}

const std::string & ConstStrBlobPtr::operator[](size_t n) const {
    auto p = check(n, "iterator past end of StrBlobPtr");
    return (*p)[n];
}

ConstStrBlobPtr & ConstStrBlobPtr::operator+=(size_t n) {
    curr_idx += n;
    check(curr_idx, "increment past end of StrBlobPtr");
    return *this;
}

ConstStrBlobPtr & ConstStrBlobPtr::operator-=(size_t n) {
    curr_idx -= n;
    check(curr_idx, "decrement past begin of StrBlobPtr");
    return *this;
}

ConstStrBlobPtr ConstStrBlobPtr::operator+(size_t n) {
    ConstStrBlobPtr ret = *this;
    return ret += n;
}

ConstStrBlobPtr ConstStrBlobPtr::operator-(size_t n) {
    ConstStrBlobPtr ret = *this;
    return ret -= n;
}

std::string & ConstStrBlobPtr::operator*() const {
    auto p = check(curr_idx, "iterator past end of StrBlobPtr");
    return (*p)[curr_idx];
}

std::string * ConstStrBlobPtr::operator->() const {
    return &this->operator*();
}

std::shared_ptr<std::vector<std::string> > ConstStrBlobPtr::check(size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    if (!ret) {
        throw std::runtime_error("Unbound ConstStrBlobPtr");
    }
    if (i >= ret->size()) {
        throw std::out_of_range(msg);
    }
    return ret;
}

std::string &ConstStrBlobPtr::deref() const {
    auto p = check(curr_idx, "deref on empty StrBlobPtr");
    return (*p)[curr_idx];
}

ConstStrBlobPtr &ConstStrBlobPtr::incr() {
    check(curr_idx, "increment past end of ConstStrBlobPtr");
    ++curr_idx;
    return *this;
}

bool operator< (const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.curr_idx < rhs.curr_idx;
}

bool operator>(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.curr_idx > rhs.curr_idx;
}

bool operator<=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.curr_idx <= rhs.curr_idx;
}

bool operator>=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
    return lhs.curr_idx >= rhs.curr_idx;
}