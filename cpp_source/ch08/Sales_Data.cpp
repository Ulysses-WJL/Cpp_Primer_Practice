#include "Sales_Data.h"

// constructor
Sales_Data::Sales_Data(std::istream &is) : Sales_Data()
{
    std::cout << "Sales_data(istream &is)" << std::endl;
    read(is, *this);
}

// member functions.
Sales_Data& Sales_Data::combine(const Sales_Data& rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

Sales_Data & Sales_Data::operator+=(const Sales_Data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// friend functions
std::istream &read(std::istream &is, Sales_Data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_Data &item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue;
    return os;
}

Sales_Data add(const Sales_Data &lhs, const Sales_Data &rhs)
{
    Sales_Data sum = lhs;
    sum.combine(rhs);
    return sum;
}

std::istream & operator>>(std::istream &is, Sales_Data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    // item.revenue = price * item.units_sold;
    if (is) {
        item.revenue = price * item.units_sold;
    } else {
        item = Sales_Data();
    }
    return is;
}

std::ostream & operator<<(std::ostream &os, const Sales_Data &item) {
    os << item.isbn() << " " << item.units_sold << " " << item.revenue;
    return os;
}

Sales_Data operator+(const Sales_Data &sales_data, const Sales_Data &sales_data1) {
    Sales_Data sales_data2(sales_data);
    return sales_data2 += sales_data1;
}

bool operator==(const Sales_Data &lhs, const Sales_Data &rhs) {
    return lhs.isbn() == rhs.isbn() && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
}

bool operator!=(const Sales_Data &lhs, const Sales_Data &rhs) {
    return !(lhs == rhs);
}
