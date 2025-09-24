//
// Created by bruce on 2025/9/13.
//

#ifndef QUOTE_H
#define QUOTE_H
#include <string>
#include <iostream>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price): bookNo(book), price(sales_price) {};
    std::string isbn() const { return bookNo; }
    Quote(const Quote &) = default;  // memberwise copy
    Quote(Quote &&) = default;
    Quote &operator=(const Quote &) = default;  // copy assign
    Quote &operator=(Quote &&) = default;  // move assign
    virtual ~Quote() = default;   // 确保在使用基类指针或引用删除派生类对象时， 能够正常调用派生类的析构函数
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() {std::cout << "Quote info ... " << std::endl;}

private:
    std::string bookNo;
protected:
    double price = 0.0;
};



#endif //QUOTE_H
