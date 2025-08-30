#include "Book.h"


Book & Book::operator+=(const Book &book) {
    // number 相加， 判断是否相等， isbn相同
    if (*this == book)
        number_ += book.number_;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Book &book) {
    os << book.isbn_ << " "<< book.name_ << " " << book.author_ << " " << book.publish_date_ << " " << book.number_ << std::endl;
    return os;
}

std::istream & operator>>(std::istream &is, Book &book) {
    is >> book.isbn_ >> book.name_ >> book.author_ >> book.publish_date_ >> book.number_;
    return is;
}

bool operator==(const Book &book1, const Book &book2) {
    return book1.isbn_ == book2.isbn_;
}

bool operator!=(const Book &book1, const Book &book2) {
    return !(book1 == book2);
}

bool operator<(const Book &book1, const Book &book2) {
    return book1.number_ < book2.number_;
}

bool operator>(const Book &book1, const Book &book2) {
    return book2 < book1;
}

Book operator+(const Book &book1, const Book &book2) {
    Book book(book1);
    return book += book2;
}
