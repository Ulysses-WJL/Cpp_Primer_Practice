#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ch12/StrBlob.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

class Sales_data {
public:
    // other members and constructors as before
    // declaration equivalent to the synthesized copy constructor 合成复制构造函数

    Sales_data(string book, int units, double r) : bookNo(book), units_sold(units), revenue(r) {
        cout << "new instance" << endl;
    }
    Sales_data() : Sales_data("", 0, 0.0f) {}
    Sales_data(const Sales_data&);    // 自定义复制构造函数
    Sales_data& operator=(const Sales_data &);
private:
    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
};
// 等同于默认的复制构造函数
// memberwise copies: built-in直接复制，array 复制里面的元素。，class使用 copy constuctor
Sales_data::Sales_data(const Sales_data &orig):
    bookNo(orig.bookNo), // uses the string copy constructor
    units_sold(orig.units_sold), // copies orig.units_sold
    revenue(orig.revenue) // copies orig.revenue
    { cout << "use copy constructor" << endl; } // empty body

// 等同于默认的 synthesized copy-assignment operator
// Sales_data &Sales_data::operator=(const Sales_data &rhs) = default;
Sales_data &Sales_data::operator=(const Sales_data &rhs) {
    cout << "use Copy-Assignment" << endl;
    // this.bookNo
    bookNo = rhs.bookNo;  // call string::operator=
    // 调用built-in int double 赋值操作
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;  // return a reference to this object
}

void f1(vector<int> vi) {
    cout << "Function f1!!" << endl;
}

void test_copy_initialization() {
    string aaa(10, 'a');  //direct init, 直接调用构造函数
    // copy init，创建临时对象，然后copy，可能需要类型转换，
    // 调用copy constructor或者move constructor
    string bbb = "bbbbb";
    // 出现场景：
    // 用=定义变量时。
    // 将一个对象作为实参传递给一个非引用类型的形参。
    // 从一个返回类型为非引用类型的函数返回一个对象。
    // 用花括号列表初始化一个数组中的元素或者一个聚合类中的成员。
    // 如library containers使用copy initialization时，push, insert

    // emplace就使用direct initialization

    string dots(10, '.'); // direct initialization
    string s(dots); // direct initialization
    string s2 = dots; // copy initialization
    string null_book = "9-999-99999-9"; // copy initialization complier可能会忽略复制构造而使用直接构造
    string nines = string(100, '9'); // copy initialization

    vector<int> v1(10); // ok: direct initialization
    // vector<int> v2 = 10; //  vector接受一个参数的构造函数 是explict的(阻止仅一步的类型转换)， 只能使用direct initialization
    void f(vector<int>);  // 参数是非引用类型，会使用copy initialization
    // f(10); // error: can’t use an explicit constructor to copy an argument
    f1(vector<int>(10));  // 构造了一个临时的vector
}

void q_13_1() {
    // What is a copy constructor? When is it used?
    // 如果一个构造函数的第一个参数是自身类类型的引用，且任何额外参数都有默认值，
    // 则此构造函数是拷贝构造函数。当使用拷贝初始化时，我们会用到拷贝构造函数。
    /*
     * 用=定义变量时。
     * 将一个对象作为实参传递给一个非引用类型的形参。
     * 从一个返回类型为非引用类型的函数返回一个对象。
     * 用花括号列表初始化一个数组中的元素或者一个聚合类中的成员。
     */
}

void q_13_2() {
    // Sales_data::Sales_data(Sales_data &rhs);
}

void q_13_3() {
    // What happenswhenwe copy a StrBlob? What about StrBlobPtrs?
    /*
     * StrBlob中的 share_ptr会加一，
     * StrBlobPtrs copy时share_ptr不会改变 （weak_ptr）
     */
}

class Point {
public:
    explicit Point(int xx = 0, int yy = 0 ): x(xx), y(yy) {}
    Point(const Point&) = default;

private:
    int x;
    int y;
};

// q_13_4
Point global;  // 直接构造
Point foo_bar(Point xx)  // 非引用参数， 复制构造
{
    Point local = xx, *heap = new Point(global);  // 使用= 复制构造
    *heap = local;


    Point pa[ 4 ] = { local, *heap };  // {}初始化，复制构造
    return *heap;  // 函数返回非引用类型， 复制构造
}

// q_13_5 添加 copy constructor
// dynamically allocate a new string
// and copy the object to which ps points, rather than copying ps itself.
// q_13_8 添加 assignment operator， copy ps所指的对象
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()): ps(new std::string(s)), i(0) {}
    // 动态分配一个新的string，并将对象拷贝到ps所指向的位置，而不是拷贝ps本身
    HasPtr(const HasPtr &other): ps(new string(*other.ps)), i(other.i) {};
    HasPtr& operator=(const HasPtr &rhs) {
        if (this != &rhs) {
            i = rhs.i;
            // 深拷贝
            string *temp_ps = new string(*rhs.ps);
            delete ps;  // 删除当前ps原指向的字符串
            ps = temp_ps;
        }
        return *this;
    };
private:
    std::string *ps;
    int i;
};

void q_13_6() {
   /*
     Q: What is a copy-assignment operator?
     A: operator= 函数
     Q: When is this operator used?
     A: 发生赋值运算时
     Q: What does the synthesized copy-assignment operator do?
     A: 将源对象（rhs）的每个成员变量的值复制到当前对象（*this）的对应成员中. 合成拷贝赋值运算符可以用来禁止该类型对象的赋值
     Q:When is it synthesized?
     A: 类没有定义自己的拷贝复制运算符，编译器为它生成合成拷贝赋值运算符
    */
}

void q_13_7() {
    /*
    * What happens when we assign one StrBlob to another?
    * What about StrBlobPtrs?
    * shallow copy, 只会复制指针本身， 实际资源不会复制
     */
    StrBlob str({"hello", "world!"});
    cout << "before: " << str.count() << endl;
    StrBlob str_copy = str;
    cout << "after: " << str.count() << endl;

    ConstStrBlobPtr p(str);
    cout << "before: " << p.count() << endl;
    ConstStrBlobPtr p_copy = p;
    cout << "after: " << p.count() << endl;
}


/*
 * 析构函数， destructor， 与初始化的顺序(出现顺序) 相反 destroy
 * class type就调用类的析构函数，
 * built-in types没有析构函数，nothing is done
 * 隐式的析构函数不会delete built-in pointer所指的对象
 * smart pointers是class type， 所以会销毁，对象会被释放
 */

void test_destructor() {
    for (int i = 0; i < 1; ++i){ // new scope
        // p and p2 point to dynamically allocated objects
        Sales_data *p = new Sales_data; // p is a built-in pointer
        auto p2 = std::make_shared<Sales_data>(); // p2 is a shared_ptr
        Sales_data item(*p); // copy constructor copies *p into item
        vector<Sales_data> vec; // local object
        vec.push_back(*p2); // copies the object to which p2 points
        delete p; // destructor called on the object pointed to by p
    } // exit local scope; destructor called on item, p2, and vec
        // destroying p2 decrements its use count; if the count
}

int main(int argc, char *argv[]) {
    test_destructor();
    q_13_7();
    return 0;
}
