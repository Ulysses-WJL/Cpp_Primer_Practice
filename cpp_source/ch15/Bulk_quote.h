//
// Created by bruce on 2025/9/13.
//

#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H
#include "Disc_quote.h"

class Bulk_quote : public Disc_quote{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& , double, std::size_t, double);
    double net_price(std::size_t) const override;
    void debug() override {std::cout << "Bulk_quote" << std::endl;}
};



#endif //BULK_QUOTE_H
