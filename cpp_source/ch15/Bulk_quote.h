//
// Created by bruce on 2025/9/13.
//

#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H
#include "Disc_quote.h"

class Bulk_quote : public Disc_quote{
public:
    Bulk_quote() ;
    // Bulk_quote(const std::string& , double, std::size_t, double);
    // 继承直接父类 Disc_quote的constructor， default, copy and move constructors这些不能继承
    // 具有相同parameter list的构造函数 能继承，Bulk_quote自己的成员都是默认初始化
    // access level 由父类构造函数的access level决定
    using Disc_quote::Disc_quote;

    Bulk_quote(const Bulk_quote &);

    Bulk_quote(Bulk_quote &&) noexcept;

    Bulk_quote &operator=(const Bulk_quote &);

    Bulk_quote &operator=(Bulk_quote&&) noexcept ;
    ~Bulk_quote() override;
    double net_price(std::size_t) const override;
    void debug() override {std::cout << "Bulk_quote" << std::endl;}
};



#endif //BULK_QUOTE_H
