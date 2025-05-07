//
//
//
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl; using std::string;

struct Sales_Data;
std::istream &read(std::istream &is, Sales_Data &item);

struct Sales_Data {
    // constructors
    Sales_Data() = default;  // 默认构造函数，它不接受任何参数
    // Constructor Initializer List
    Sales_Data(const string &s) : bookNo(s) {}  // 带有一个参数的构造函数 初始化bookNo
    Sales_Data(const string &s, unsigned n, double p) :
                bookNo(s), units_sold(n), revenue(p * n) {}  // 三个参数的构造函数
    Sales_Data(std::istream &is) { read(is, *this);};  // 从输入流读取 进行构造
    // member function
    // this 是const pointer 指向nonconst， 添加const 不修改对象的任何非静态成员变量
    // （即 this 指针指向的对象的状态不会被改变）。
    //非const 函数，不能被 const 对象调用
    string isbn() const {return bookNo;}  // this->bookNo
    Sales_Data& combine(const Sales_Data&);
    double avg_price() const;
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
// nonmember Sales_data interface functions
Sales_Data add(const Sales_Data&, const Sales_Data&);
std::ostream &print(std::ostream&, const Sales_Data&);
std::istream &read(std::istream&, Sales_Data&);

// Sales_Data::Sales_Data(std::istream &is) {
//     read(is, *this);
// }

double Sales_Data::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Sales_Data &Sales_Data::combine(const Sales_Data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;  // return the object on which the function was called
}

std::istream &read(std::istream &is, Sales_Data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_Data &item) {
    os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
    return os;
}

Sales_Data add(const Sales_Data &item1, const Sales_Data &item2) {
    Sales_Data sum = item1;
    sum.combine(item2);
    return sum;
}

class Person {
private:
    string name;
    string address;
public:
    auto get_name() const -> string const& {return name;}
    string const &get_address() const {return address;}
    void set_name(const std::string &n) { name = n; }
    void set_address(const std::string &a) { address = a; }
};

std::istream &read(std::istream &is, Person &person) {
    string name, addr;
    is >> name >> addr;
    person.set_name(name);
    person.set_address(addr);
    return is;
}

std::ostream &print(std::ostream &os, const Person &person) {
    return os << person.get_name() << " " << person.get_address();
}


int q_7_1_1(){
    Sales_Data total;
    if (cin >> total.bookNo >> total.units_sold >> total.revenue) {
        Sales_Data trans;
        while(cin >> trans.bookNo >> trans.units_sold >> trans.revenue) {
            if (total.bookNo == trans.bookNo) {
                total.units_sold += trans.units_sold;
                total.revenue += trans.revenue;
            } else {
                cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
                total = trans;
            }
        }
        cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
    } else {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;
}


int q_7_2(){
    Sales_Data total;
    if (cin >> total.bookNo >> total.units_sold >> total.revenue) {
        Sales_Data trans;
        while(cin >> trans.bookNo >> trans.units_sold >> trans.revenue) {
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);
            } else {
                cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
                total = trans;
            }
        }
        cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
    } else {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;
}

int q_7_7(){
    Sales_Data total;
    if (read(cin, total)) {
        Sales_Data trans;
        while(read(cin, trans)) {
            if (total.isbn() == trans.isbn()) {
                total.combine(trans);
            } else {
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
    } else {
        std::cerr << "No data?!" << std::endl;
        return -1;
    }
    return 0;
}

void q_7_11() {
    Sales_Data item1;
    print(cout, item1) << endl;

    Sales_Data item2("book1");
    print(cout, item2) << endl;

    Sales_Data item3("book1", 10, 4);
    print(cout, item3) << endl;

    Sales_Data item4(cin);
    print(cout, item4) << endl;

}

int main() {
    q_7_11();
    // q_7_7();
    return 0;
}
