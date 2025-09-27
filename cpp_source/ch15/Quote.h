//
// Created by bruce on 2025/9/13.
//

#ifndef QUOTE_H
#define QUOTE_H
#include <string>
#include <iostream>

class Quote {
public:
    Quote() {std::cout << "Quote default constructor" << std::endl;};
    Quote(const std::string &book, double sales_price): bookNo(book), price(sales_price) {
        std::cout << "Quote constructor" << std::endl;
    };
    std::string isbn() const { return bookNo; }
    Quote(const Quote &rhs): bookNo(rhs.bookNo), price(rhs.price) {std::cout << "Quote copy constructor " << std::endl;};  // memberwise copy
    Quote(Quote &&rhs): bookNo(rhs.bookNo), price(rhs.price) {std::cout << "Quote Move constructor " << std::endl;};
    Quote &operator=(const Quote &rhs) {
        bookNo = rhs.bookNo;
        price = rhs.price;
        std::cout << "Quote copy assignment operator " << std::endl;
        return *this;
    };  // copy assign
    Quote &operator=(Quote &&rhs) {
        if (this != &rhs) {
            bookNo = std::move(rhs.bookNo);
            price = std::move(rhs.price);
        }
        std::cout << "Quote move assignment operator " << std::endl;
        return *this;
    };  // move assign
    virtual ~Quote() {
        std::cout << "Quote destructor" << std::endl;
    };   // 确保在使用基类指针或引用删除派生类对象时， 能够正常调用派生类的析构函数
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() {std::cout << "Quote info ... " << std::endl;}

private:
    std::string bookNo;
protected:
    double price = 0.0;
};



#endif //QUOTE_H
