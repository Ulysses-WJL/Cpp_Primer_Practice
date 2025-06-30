#include <complex>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

class Sales_data {
public:
    // other members and constructors as before
    // declaration equivalent to the synthesized copy constructor 合成复制构造函数
    Sales_data(const Sales_data&);    // 自定义复制构造函数
private:
    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
};
// equivalent to the copy constructor that would be synthesized for Sales_data
// memberwise copies: built-in直接复制，array 复制里面的元素。，class使用 copy constuctor
Sales_data::Sales_data(const Sales_data &orig):
    bookNo(orig.bookNo), // uses the string copy constructor
    units_sold(orig.units_sold), // copies orig.units_sold
    revenue(orig.revenue) // copies orig.revenue
    { } // empty body

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
    f(vector<int>(10));  // 构造了一个临时的vector
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
    Point(const Point&);

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
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()): ps(new std::string(s)), i(0) {}
    // 动态分配一个新的string，并将对象拷贝到ps所指向的位置，而不是拷贝ps本身
    HasPtr(const HasPtr &other): ps(new string(*other.ps)), i(other.i) {};
private:
    std::string *ps;
    int i;
};



int main(void) {
    return 0;
}