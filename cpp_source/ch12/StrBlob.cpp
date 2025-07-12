#include "StrBlob.h"
#include <stdexcept>

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

void StrBlob::push_back(const std::string &t) {
    data->push_back(t);
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
