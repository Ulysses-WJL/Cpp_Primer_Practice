#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <iostream>


class Book {
    // >> << > < != == +
    friend std::ostream& operator<<(std::ostream& os, const Book& book);
    friend std::istream& operator>>(std::istream& is, Book& book);
    friend bool operator==(const Book& book1, const Book& book2);
    friend bool operator!=(const Book& book1, const Book& book2);
    friend bool operator<(const Book& book1, const Book& book2);
    friend bool operator>(const Book& book1, const Book& book2);
    friend Book operator+(const Book& book1, const Book& book2);

public:
    Book() = default;
    Book(const unsigned isbn,  const std::string &name, const std::string &author, const std::string publish_date, const unsigned number) : author_(author),
        name_(name), isbn_(isbn), publish_date_(publish_date), number_(number) {}
    // 编译器不会自动将其他类型转换为该类型。这可以防止意外的类型转换导致的错误。
    explicit Book(std::istream &is) {
        is >> *this;
    }
    explicit Book(const unsigned isbn) : Book(isbn, "", "", "",  0) {}
    Book &operator+=(const Book &book);
private:
    std::string author_;
    std::string name_;
    std::string publish_date_;
    unsigned isbn_{};
    unsigned number_;
};
std::ostream& operator<<(std::ostream& os, const Book& book);
std::istream& operator>>(std::istream& is, Book& book);
bool operator==(const Book& book1, const Book& book2);
bool operator!=(const Book& book1, const Book& book2);
bool operator<(const Book& book1, const Book& book2);
bool operator>(const Book& book1, const Book& book2);
Book operator+(const Book& book1, const Book& book2);
#endif //BOOK_H
