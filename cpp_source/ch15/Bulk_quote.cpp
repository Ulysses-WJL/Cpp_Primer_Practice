//
// Created by bruce on 2025/9/13.
//

#include "Bulk_quote.h"
//  use a base-class constructor to initialize its base-class part.
// Bulk_quote::Bulk_quote(
//     const std::string &book, double p, std::size_t qty, double disc) : Disc_quote(book, p, qty, disc) {
//     std::cout << "Bulk_quote constructor" << std::endl;
// }

Bulk_quote::Bulk_quote() {
    {std::cout << "Bulk_quote default constructor" << std::endl;}
}
Bulk_quote::Bulk_quote(const Bulk_quote &rhs) : Disc_quote(rhs) {
    std::cout << "Bulk_quote copy constructor" << std::endl;
}

Bulk_quote::Bulk_quote(Bulk_quote &&rhs) noexcept: Disc_quote(std::move(rhs)) {
    std::cout << "Bulk_quote move constructor" << std::endl;
}

Bulk_quote &Bulk_quote::operator=(const Bulk_quote &rhs) {
    if (this != &rhs) {
        Disc_quote::operator=(rhs);

    }
    std::cout << "Bulk_quote copy assignment operator" << std::endl;
    return *this;
}
Bulk_quote &Bulk_quote::operator=(Bulk_quote &&rhs) noexcept {
    if (this != &rhs) {
        Disc_quote::operator=(std::move(rhs));

    }
    std::cout << "Bulk_quote move assignment operator" << std::endl;
    return *this;
}

Bulk_quote::~Bulk_quote() {
    std::cout << "Bulk_quote destructor" << std::endl;
}

double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= quantity) {
        return quantity * price * (1-discount) +  price * (cnt - quantity) ;
    } else {
        return cnt * price * (1-discount);
    }
}

Bulk_quote * Bulk_quote::clone() const & {
    return new Bulk_quote(*this);
}

Bulk_quote * Bulk_quote::clone() && {
    return new Bulk_quote(std::move(*this));
}
