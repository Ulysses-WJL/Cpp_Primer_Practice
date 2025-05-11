//
//
//
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::endl;
using std::string;

struct Sales_Data;

std::istream &read(std::istream &is, Sales_Data &item);

class Sales_Data {
    // 友元， 当其他类或者函数想要访问当前类的私有变量时，这个时候应该用友元。
    // 友元 影响访问，但不是真正的声明
    friend std::ostream &print(std::ostream &, const Sales_Data &);

    friend std::istream &read(std::istream &, Sales_Data &);

    friend Sales_Data add(const Sales_Data &, const Sales_Data &);

public:
    // constructors
    // Sales_Data() = default; // 默认构造函数，它不接受任何参数
    // Constructor Initializer List
    // Sales_Data(const string &s) : bookNo(s) {} // 带有一个参数的构造函数 初始化bookNo
    Sales_Data(const string &s, const unsigned n, const double p) : bookNo(s), units_sold(n), revenue(p * n) {
        cout << "三个参数" << endl;
    } // 三个参数的构造函数
    // Sales_Data(std::istream &is) { read(is, *this);};  // 从输入流读取 进行构造
    // q_7_38 cin as a default argument to the constructor
    // Sales_Data(std::istream &is = std::cin) { read(is, *this); };

    // delegating constructor
    Sales_Data(): Sales_Data("", 0, 0) {
        cout << "无参数" << endl;
    }
    Sales_Data(const string &s) : Sales_Data(s, 0, 0) {
        cout << "一个参数" << endl;
    }
    // single argument 才能使用explict防止隐式转换
    // 只能使用direct initialization ，不能使用copy form
    explicit Sales_Data(std::istream &is): Sales_Data() {
        read(is, *this);
        cout << "istream 初始化" << endl;
    }

    // member function
    // this 是const pointer 指向nonconst， 添加const 不修改对象的任何非静态成员变量
    // （即 this 指针指向的对象的状态不会被改变）。
    //非const 函数，不能被 const 对象调用
    string isbn() const { return bookNo; } // this->bookNo
    Sales_Data &combine(const Sales_Data &);

    double avg_price() const;

private:
    string bookNo;
    unsigned units_sold = 0; // in-class initializer 无需通过构造函数初始化
    double revenue = 0.0;
};

// nonmember Sales_data interface functions
Sales_Data add(const Sales_Data &, const Sales_Data &);

std::ostream &print(std::ostream &, const Sales_Data &);

std::istream &read(std::istream &, Sales_Data &);

// Sales_Data::Sales_Data(std::istream &is) {
//     read(is, *this);
// }

inline
double Sales_Data::avg_price() const {
    return units_sold ? revenue / units_sold : 0;
}

Sales_Data &Sales_Data::combine(const Sales_Data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this; // return the object on which the function was called
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
private: // 在public前的默认是 private， 在struct里第一个access specifier前的就是public
    string name;
    string address;

public:
    auto get_name() const -> string const & { return name; }
    string const &get_address() const { return address; }
    void set_name(const std::string &n) { name = n; }
    void set_address(const std::string &a) { address = a; }
    // Person(const string &n, const string &a) {name = n; address = a;}  // 先构造再赋值
    Person(const string n, const string a) : name(n), address(a) {
    } // 使用初始化列表
    explicit Person(std::istream &is) {read(is, *this); }
    std::istream &read(std::istream &is, Person &person);
    std::ostream &print(std::ostream &os, const Person &person);
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


// int q_7_1_1(){
//     Sales_Data total;
//     if (cin >> total.bookNo >> total.units_sold >> total.revenue) {
//         Sales_Data trans;
//         while(cin >> trans.bookNo >> trans.units_sold >> trans.revenue) {
//             if (total.bookNo == trans.bookNo) {
//                 total.units_sold += trans.units_sold;
//                 total.revenue += trans.revenue;
//             } else {
//                 cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
//                 total = trans;
//             }
//         }
//         cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
//     } else {
//         std::cerr << "No data?!" << std::endl;
//         return -1;
//     }
//     return 0;
// }
//
//
// int q_7_2(){
//     Sales_Data total;
//     if (cin >> total.bookNo >> total.units_sold >> total.revenue) {
//         Sales_Data trans;
//         while(cin >> trans.bookNo >> trans.units_sold >> trans.revenue) {
//             if (total.isbn() == trans.isbn()) {
//                 total.combine(trans);
//             } else {
//                 cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
//                 total = trans;
//             }
//         }
//         cout << total.bookNo << " " << total.units_sold << " " << total.revenue << endl;
//     } else {
//         std::cerr << "No data?!" << std::endl;
//         return -1;
//     }
//     return 0;
// }

int q_7_7() {
    Sales_Data total;
    if (read(cin, total)) {
        Sales_Data trans;
        while (read(cin, trans)) {
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

class Screen;

class WindowMgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;

    inline void clear(ScreenIndex);

    ScreenIndex addScreen(const Screen &);

private:
    std::vector<Screen> screens;
};

class Screen {
    friend void WindowMgr::clear(WindowMgr::ScreenIndex); // 友元
public:
    // type members 先定义
    using pos = std::string::size_type;

    Screen() = default; // 有其他构造函数时，需要显式声明一个default
    Screen(pos ht, pos wd) : height(ht), width(wd) {
    }

    Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {
    }

    char get() const { return contents[cursor]; } // 类内定义 是内联
    // overload member function
    inline char get(pos ht, pos wd) const; // explicitly inline
    Screen &mov(pos r, pos c);

    void some_member() const;

    Screen &set(char);

    Screen &set(pos, pos, char);

    Screen &display(std::ostream &os) {
        do_display(os);
        return *this;
    }

    const Screen &display(std::ostream &os) const {
        do_display(os);
        return *this;
    }

    // error: extra qualification ‘Screen::’ on member ‘size’ [-fpermissive]
    // pos Screen::size() const
    pos size() const {
        return height * width;
    }

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable size_t access_ctr; // may change even in a const object
    void do_display(std::ostream &os) const { os << contents; }
};

// 返回值类型 指定class
WindowMgr::ScreenIndex WindowMgr::addScreen(const Screen &s) {
    screens.push_back(s);
    return screens.size() - 1;
}


void WindowMgr::clear(ScreenIndex index) {
    Screen &s = screens[index];
    s.contents = string(s.height * s.width, ' ');
}

void Screen::some_member() const {
    ++access_ctr; // keep a count of the calls to any member function
    // whatever other work this member needs to do
}

inline
Screen &Screen::mov(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}

char Screen::get(pos r, pos c) const {
    pos row = r * width;
    return contents[row + c];
}

inline
Screen &Screen::set(char c) {
    this->contents[cursor] = c;
    return *this;
}

inline
Screen &Screen::set(pos r, pos col, char c) {
    contents[r * width + col] = c;
    return *this;
}


void q_7_31() {
    class X;
    class Y;
    class X {
        Y *link_y = nullptr;
    };
    class Y {
        X x;
    };
}

//q_7_35
typedef string Type;

Type initVal(); // use `string`
class Exercise {
public:
    typedef double Type;

    Type setVal(Type); // use `double`
    Type initVal() {val = 0; return 0.1;}; // use `double`
private:
    int val;
};

Exercise::Type Exercise::setVal(Type parm) {
    // first is `string`, second is `double`
    val = parm + initVal(); // Exercise::initVal()
    return val;
}


class ConstRef {
public:
    ConstRef(int ii);

private:
    int i;
    const int ci;
    int &ri;
};

// const、引用或没有默认构造函数的类类型的成员, 需要使用constructor
ConstRef::ConstRef(int ii) : i(ii), ci(ii), ri(ii) {
}

void test_initialize_order() {
    class X {
        int i;
        int j;

    public:
        // 按照member出现的顺序进行初始化
        // undefined: i is initialized before j
        X(int val): j(val), i(j) {
        }
    };
}


// q_7_40
class Book {
public:
    Book(const string &author, const string &name, const string publish_date, const unsigned isbn) : author_(author),
        name_(name), isbn_(isbn), publish_date_(publish_date) {}
    // 编译器不会自动将其他类型转换为该类型。这可以防止意外的类型转换导致的错误。
    explicit Book(std::istream &is) {
        is >> isbn_ >> author_ >> name_ >> publish_date_;
    }
    explicit Book(const unsigned isbn) : Book("", "", "", isbn) {}

private:
    string author_;
    string name_;
    unsigned isbn_{};
    string publish_date_;
};

void q_7_41() {
    cout << "===============================" << endl;
    Sales_Data sale1("sale1", 5, 0.5);
    cout << "===============================" << endl;
    // Declarator is disambiguated as a function declaration. Make sure a variable definition is not intended instead.
    // 定义的是一个函数 而不是object
    // Sales_Data sale_2();
    Sales_Data sale2;
    cout << "===============================" << endl;
    Sales_Data sale3("sale3");
    cout << "===============================" << endl;
    Sales_Data sale4(cin);
    cout << "===============================" << endl;
}

// q_7_43
class NoDefault {
public:
    explicit NoDefault(const int a) : val(a) {cout << "NoDefault 定义： " << val << endl; }
private:
    int val;
};

class C {
public:
    explicit C() : no_default_(0) {cout << "c 定义： " << endl;}
private:
    NoDefault no_default_;
};

void q_7_43() {
    C c;
}

void q_7_44() {
    // NoDefault没有默认构造函数
    // vector<NoDefault> vec(10);  // 10个元素
}

void test_implicated_constructor() {
    // Sales_Data(const string &s) 非 explicit
    string null_book = "9-999-99999-9";
    Sales_Data item("9-999-99999-9", 5, 0.5);
    item.combine(null_book);  // 使用Sales_Data(const string &s) 将string转为了Sales_Data
    print(cout, item) << endl;

    // ok: explicit conversion to string, implicit conversion to Sales_data
    item.combine(string("9-999-99999-9"));
    // ok: implicit conversion to string, explicit conversion to Sales_data
    item.combine(Sales_Data("9-999-99999-9"));
    // static_cast can use an explicit constructor
    item.combine(static_cast<Sales_Data>(cin));
    print(cout, item) << endl;
}

void test_string_add(const string &str1, const string &str2) {
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << str1 + str2 << endl;
}

void q_7_49() {
    // Sales_Data &combine(Sales_Data); // ok
    // Sales_Data &combine(Sales_Data&); // error C2664: 无法将参数 1 从“std::string”转换为“Sales_data &”	因为隐式转换只有一次
    // Sales_Data &combine(const Sales_Data&) const; // 该成员函数是const 的，意味着不能改变对象。而 combine函数的本意就是要改变对象
}

void test_aggregate_class() {
    // members public
    // no constructors
    // no in-class initializer
    // no base class or virtual functions
    struct Data {
        int val;
        string s;
    };
    Data val1 = {0, "Tom"};
}

// literal class
class Debug {
public:
    // 至少一个 constexpr constructor
    constexpr Debug(bool b = true) : hw(b), io(b), other(b) { }
    constexpr Debug(bool h, bool i, bool o) : hw(h), io(i), other(o) { }

    // 添加 const  允许在 const 对象上调用该方法
    constexpr bool any() const { return hw || io || other; }
    void set_hw(bool b) { hw = b; }
    void set_io(bool b) { io = b; }
    void set_other(bool b) { other = b; }

private:
    // member都是 literal type
    bool hw;        // runtime error
    bool io;        // I/O error
    bool other;     // the others
};

void test_literal_class() {

    constexpr Debug io_sub(false, true, false); // debugging IO
    if (io_sub.any()) // equivalent to if(true)
        std::cerr << "print appropriate error messages" << endl;
    constexpr Debug prod(false); // no debugging during production
    if (prod.any()) // equivalent to if(false)
        std::cerr << "print an error message" << endl;

}

class Point {
public:
    constexpr Point(double x, double y) : x_(x), y_(y) {}
    constexpr double getX() const { return x_; }
    constexpr double getY() const { return y_; }

private:
    double x_;
    double y_;
};

// static class members
class Account {
public:
    void calculate() {amount += amount * interest_rate;}
    static void rate(double);
    static double rate() {return interest_rate;};

private:
    std::string owner;
    double amount;
    // associated with the class, rather than with individual objects
    static double interest_rate;
    static double init_rate();
    static constexpr int period = 30;  // 只有integral type的static member 可以在类内 初始化
    double daily_tbl[period];
};

double Account::init_rate() {
    return 0.01;
}

void Account::rate(double r) {
    interest_rate = r;
}

// 定义静态成员变量, 必须在类外进行定义，确保它在任何地方都能被访问。
double Account::interest_rate = init_rate(); // 进行定义
constexpr int Account::period;  // 类里面初始化了，也应该在类外定义


void test_static_member() {
    double r;
    Account::rate(0.1);
    r = Account::rate();
    cout << "rate: " << r << endl;
    Account ac1;
    Account *ac2 = &ac1;
    r = ac1.rate();
    r = ac2->rate();
}


int main() {
    test_static_member();
    constexpr Point p2(1.0, 2.0);
    constexpr double x = p2.getX(); // 编译时计算
    test_literal_class();
    cout << x << endl;
    string s1 = "xxxx";
    const char c1 = 'a';
    test_string_add(s1, &c1);
    // test_implicated_constructor();
    q_7_44();
    q_7_43();
    // q_7_41();
    Screen::pos ht = 24, wd = 80;
    Screen scr(ht, wd, ' ');
    Screen *p = &scr;
    char c = scr.get();
    c = p->get(); // (*p).get();

    Screen my_screen(8, 6, 'X');
    const Screen blank(5, 3);
    WindowMgr mgr;
    my_screen.mov(4, 0).set('#').display(cout);

    cout << "\n";
    my_screen.display(cout);

    blank.display(cout);
    cout << "\n";

    Person p1("Jack", "Tokyo");
    cout << p1.get_name() << " " << p1.get_address() << endl;
    // q_7_11();
    // q_7_7();
    return 0;
}
