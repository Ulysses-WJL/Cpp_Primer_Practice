//
// Created by bruce on 2025/9/13.
//

#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H
#include "Quote.h"

class Bulk_quote : public Quote{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& , double, std::size_t, double);
    double net_price(std::size_t) const override;
    void debug() override {std::cout << "Bulk_quote" << std::endl;}
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};



#endif //BULK_QUOTE_H
