#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
#include <iostream>

class Sales_Data {
    friend std::istream &read(std::istream &is, Sales_Data &item);
    friend std::ostream &print(std::ostream &os, const Sales_Data &item);
    friend Sales_Data add(const Sales_Data &lhs, const Sales_Data &rhs);

public:
    Sales_Data(const std::string &s, unsigned n, double p):bookNo(s), units_sold(n), revenue(n*p)
    { std::cout << "Sales_data(const std::string&, unsigned, double)" << std::endl; }

    Sales_Data() : Sales_Data("", 0, 0.0f)
    { std::cout << "Sales_data()" << std::endl; }

    Sales_Data(const std::string &s) : Sales_Data(s, 0, 0.0f)
    { std::cout << "Sales_data(const std::string&)" << std::endl; }

    Sales_Data(std::istream &is);

    std::string isbn() const { return bookNo; }
    Sales_Data& combine(const Sales_Data&);

private:
    inline double avg_price() const;

private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

inline
double Sales_Data::avg_price() const
{
    return units_sold ? revenue/units_sold : 0;
}

// declarations for nonmember parts of the Sales_data interface.
std::istream &read(std::istream &is, Sales_Data &item);
std::ostream &print(std::ostream &os, const Sales_Data &item);
Sales_Data add(const Sales_Data &lhs, const Sales_Data &rhs);
#endif