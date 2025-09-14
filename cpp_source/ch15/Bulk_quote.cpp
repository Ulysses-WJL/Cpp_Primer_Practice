//
// Created by bruce on 2025/9/13.
//

#include "Bulk_quote.h"
//  use a base-class constructor to initialize its base-class part.
Bulk_quote::Bulk_quote(
    const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc) {
}

double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= min_qty) {
        return min_qty * price * (1-discount) +  price * (cnt - min_qty) ;
    } else {
        return cnt * price * (1-discount);
    }
}
