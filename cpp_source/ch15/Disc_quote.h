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
    Disc_quote() {std::cout << "Disc_quote default constructor" << std::endl;};
    Disc_quote(
        std::string name, double price, std::size_t qty, double disc
        ): Quote(name, price), quantity(qty), discount(disc) {
        std::cout << "Disc_quote constructor" << std::endl;
    };
    Disc_quote(const Disc_quote& rhs): Quote(rhs), quantity(rhs.quantity), discount(rhs.discount) {
        std::cout << "Disc_quote copy constructor" << std::endl;
    }
    ~Disc_quote() override {std::cout << "Disc_quote destructor" << std::endl;};
    Disc_quote(Disc_quote &&rhs) noexcept :
        Quote(std::move(rhs)), quantity(std::move(rhs.quantity)), discount(std::move(rhs.discount)) {
        std::cout << "Disc_quote move constructor" << std::endl;
    }
    Disc_quote& operator=(const Disc_quote& rhs) {
        if (this != &rhs) {
            Quote::operator=(rhs);
            quantity = rhs.quantity;
            discount = rhs.discount;

        }
        std::cout << "Disc_quote copy assignment operator" << std::endl;
        return *this;
    }
    Disc_quote& operator=(Disc_quote&& rhs) {
        if (this != &rhs) {
            Quote::operator=(std::move(rhs));
            quantity = std::move(rhs.quantity);
            discount = std::move(rhs.discount);

        }
        std::cout << "Disc_quote move assignment operator" << std::endl;
        return *this;
    }
    // pure virtual function, 无需定义， 无函数体
    double net_price(std::size_t n) const = 0;
protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};



#endif //DISC_QUOTE_H
