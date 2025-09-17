//
// Created by bruce on 2025/9/17.
//

#ifndef DISC_QUOTE_H
#define DISC_QUOTE_H
#include "Quote.h"

// 包含 pure virtual function 的是抽象基类Abstract Base Classes
// 不能直接创建抽象基类的对象
class Disc_quote : public Quote{
public:
    Disc_quote() = default;
    Disc_quote(
        std::string name, double price, std::size_t qty, double disc
        ): Quote(name, price), quantity(qty), discount(disc){};
    // pure virtual function, 无需定义， 无函数体
    double net_price(std::size_t n) const = 0;
protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};



#endif //DISC_QUOTE_H
