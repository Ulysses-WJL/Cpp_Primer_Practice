#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include "../ch12/StrBlob.h"

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
    // no work to do other than destroying the members, which happens automatically
    // members不是在析构函数里进行销毁的，在后面隐式销毁阶段中被销毁。
    ~Sales_data() { cout << "调用析构函数" << endl;}
    string isbn() {return bookNo;}
private:
    std::string bookNo;  // 调用string destructor释放
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
    // What happens when we copy a StrBlob? What about StrBlobPtrs?
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

// 先确认自己的类是否需要定义自己的析构函数.
// HasPtr的合成析构函数不会delete ps， 所以需要定义一个析构函数来释放构造函数分配的内存。
// 如果不自己定义，使用编译器合成的，拷贝构造和拷贝赋值时，ps指向的就会是同一个
// valuelike behavior
class HasPtr {
    // reorder elements时 algorithm调用
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const std::string &s = std::string(), int v = 0): ps(new std::string(s)), i(v) {}
    // 动态分配一个新的string，并将对象拷贝到ps所指向的位置，而不是拷贝ps本身
    HasPtr(const HasPtr &other): ps(new string(*other.ps)), i(other.i) {};
    HasPtr& operator=(const HasPtr &rhs) {
        if (this != &rhs) {
            i = rhs.i;
            // 深拷贝
            // 1. copy the right-hand operand into a local temporary
            // 2. destroy the existing members of the left-hand operand
            string *temp_ps = new string(*rhs.ps);
            // 如果rhs 和 this 是一个，直接delete 就会有undefined 错误
            delete ps;  // 删除当前ps原指向的字符串
            ps = temp_ps;
        }
        return *this;
    };
    HasPtr& operator=(HasPtr);
    // q13.11 Add a destructor
    ~HasPtr() {delete ps;}
    void show() const {cout << "i : " << i << endl; cout << "*ps: " << *ps << endl; }
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
// 当对象的引用或指针超出作用域时，不会调用destructor
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

void q_13_9() {
    /*
     * Q： What is a destructor?
     * A：~+类名 构成的成员函数 没有返回值，也不接受参数
     * Q: What does the synthesized destructor do?
     * A: 合成析构函数可被用来阻止该类型的对象被销毁。
     * Q: When is a destructor synthesized?
     * A：当一个类没有定义自己的析构函数时，编译器会为它生成一个合成析构函数
     */
}

void q_13_10() {
    /*
    *  Q: What happens when a StrBlob object is destroyed?
    *  A: data 的 use_count会减少，如果没有share_ptr指向它，会被释放
    *  Q: What about a StrBlobPtr?
    *  A: StrBlobPtr被销毁时，不会影响引用计数，动态内存不会被释放
     */
}


bool fcn(const Sales_data *trans, Sales_data accum)
{
    Sales_data item1(*trans), item2(accum);
    return item1.isbn() != item2.isbn();
}

void q_13_12() {
    //How many destructor calls occur in the following code fragment?
    Sales_data s1("aaa", 12, 0.5);
    Sales_data s2("bbb", 10, 24);
    cout << "=================片段================" << endl;
    // accum 参数值传递，拷贝构造，函数结束时销毁，析构调用一次
    // item1是通过trans指针拷贝构造的，函数内部局部变量，在函数结束时销毁，析构一次。
    // item2是通过accum拷贝构造的，同样在函数结束时销毁，析构一次。
    // trans指向的对象生命周期由外部决定，在函数内部不会被销毁。
    fcn(&s1, s2);
    cout << "=================片段================" << endl;
}

struct X {
    X() {std::cout << "X()" << std::endl;}
    X(const X&) {std::cout << "X copy constructor" << std::endl;}
    X& operator=(const X &x) {cout << "X copy assignment" << endl; return *this;}
    ~X() {cout << "X destructor" << endl;}
};

void q_13_13(const X &x, X x1) {
    cout << "拷贝构造2个" << endl;
    X x2(x), x3(x1);
    vector<X> vec;
    vec.reserve(3);
    cout << "加入到container，" << endl;
    vec.push_back(x1);
    vec.push_back(x2);
    vec.push_back(x3);
    cout << "=操作，调用copy assignment" << endl;
    x3 = x1;
    cout << "函数结束，调用destructor vec中3个+x1 x2 x3"<< endl;
}

class numbered {
public:
    numbered(int v = 0) : value(v) {
        std::random_device rd;  // seed
        std::mt19937 gen(rd());  // 梅森旋转算法
        std::uniform_int_distribution<> dis(0, 999999);  // uniform
        mysn = dis(gen);
    }
    numbered(const numbered &other): numbered(other.value){}
    numbered& operator=(const numbered &other) {
        // mysn 还是自己的
        value = other.value;
        return *this;
    }
    int mysn;
    int value;
};

void f (const numbered &s) { cout << s.mysn << endl; }

void q_13_14() {
    // numbered 是一个类，默认构造函数生成mysn（每个对象的序列号） 使用了synthesized copy-control
    // void f (numbered s) { cout << s.mysn << endl; }
    numbered a, b = a, c = b;   // a, b, c 的mysn相同，不符合预期 655705
    f(a);
    f(b);
    f(c);
}

void q_13_15() {
    // 添加了 copy constructor 上述会如何
    numbered a, b = a, c = b;  // 3者mysn不同
    cout << a.mysn << endl;
    cout << b.mysn << endl;
    cout << c.mysn << endl;
    // 但f输出结果与它们自己的mysn不同，值传递会使用copy-constructor生成新的对象
    f(a);
    f(b);
    f(c);
}

void q_13_16() {
    // 修改 f参数类型 为const numbered & 结果如何
    // f输出的与它们的mysn相同
    numbered a, b = a, c = b;
    cout << a.mysn << endl;
    cout << b.mysn << endl;
    cout << c.mysn << endl;
    f(a);
    f(b);
    f(c);
}

// complier 生成default的 synthesized copy-control
class Sales_data_default {
public:
    Sales_data_default() = default;  //在类内使用的default 是 implicitly inline
    Sales_data_default(const Sales_data_default&) = default;
    Sales_data_default& operator=(const Sales_data_default &);
    ~Sales_data_default() = default;
    string isbn() {return bookNo;}
private:
    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
};
Sales_data_default &Sales_data_default::operator=(const Sales_data_default &) = default;


// prevent copies, 使用deleted functions
struct Nocopy {
    Nocopy() = default;
    Nocopy(const Nocopy&) = delete;  // 不定义，否则complier会自动合成
    Nocopy& operator=(const Nocopy&) = delete;
    ~Nocopy() = default;  // 析构函数不能为delete， 否则就无法destory或create
};
/*
* if a class has a datamember that cannot be default
constructed, copied, assigned, or destroyed, then the corresponding member will
be a deleted function.
如类成员是reference 类型或是const类型，就不能使用编译器合成的copy-assignment
 */

// 旧版本使用private 来阻止拷贝
class PrivateCopy {

    PrivateCopy(const PrivateCopy&);
    PrivateCopy& operator=(const PrivateCopy&);
public:
    PrivateCopy() = default;
    ~PrivateCopy();
};


// q_13_18
// q_13_19: 每个Employee的id不同，需要copy-constructor和copy-assignment；使用delete 显式阻止
class Employee {
public:
    Employee();
    Employee(string n);
    Employee(const Employee &) = delete;
    Employee& operator=(const Employee &) = delete;
    const int my_id() {return id_; }
private:
    string name;
    int id_;
    static int uid;
};
int Employee::uid = 0;
Employee::Employee() {
    id_ = uid++;
}

Employee::Employee(string n) : name(n){
    id_ = uid++;
}

// Employee::Employee(const Employee &rhs) {
//     name = rhs.name;
//     id_ = uid++;
// }
//
// Employee &Employee::operator=(const Employee &rhs) {
//     name = rhs.name;
//     id_ = uid++;
//     return *this;
// }

void q_13_18() {
    Employee e1, e2("Jack");
    cout << e1.my_id() << endl;
    cout << e2.my_id() << endl;
}

// void q_13_19() {
//     Employee e1, e2("Jack"), e3(e2);
//     e1 = e3;
//     cout << e1.my_id() << endl;
//     cout << e2.my_id() << endl;
//     cout << e3.my_id() << endl;
// }

void q_13_20() {
    /*
    * Explainwhat happens when we copy, assign, or destroy objects of our
TextQuery and QueryResult classes from § 12.3 (p. 484).
     */
    // 使用编译器合成的 copy-control, 成员会被复制
}

void q_13_21() {
    // TextQuery and QueryResult 使用系统合成的copy-control就能满足需求
}

// 管理不在类中的资源 需要定义 copy-control members.
// 如类中使用了 string *
/*
* 类的行为可以像一个值，也可以像一个指针。
行为像值：对象有自己的状态，副本和原对象是完全独立的。
行为像指针：共享状态，拷贝一个这种类的对象时，副本和原对象使用相同的底层数据。
 */

void q_13_24() {
    /*
    *  Q: What would happen if the version of HasPtr in this section didn’t define a destructor?
    *  A: 编译器会合成一个destructor，不会释放ps所指的对象的内存，最后导致memory leaky
       Q: What if HasPtr didn’t define the copy constructor?
       A: 会使用编译器合成的copy constructor， pointerlike behavior， 2个实例的ps指向的是同一个对象
     */
}

void q_13_25() {
    /*
     *  StrBlob 如果要改成valuelike behavior
     *  需要定义自己的copy constructor 和 copy assignment， 动态分配每个实例自己内存
     *  不需要自己定义destructor， synthesized destructor 能够正确处理 smart pointer
     */
}

void q_13_26() {
    StrBlob s1{"a", "b", "cded"};
    StrBlob s2(s1);
    StrBlob s3;
    s3 = s1;
    cout << s1.size() << endl;
    cout << s2.size() << endl;
    cout << s3.size() << endl;
}

// pointerlike 的 类, 通常使用shared_ptr
// 自定义reference count
class HasPtr1 {
public:
    // 构造函数, i初始化为0，ps指针初始化指，use 存在dynamic memory
    HasPtr1(const string &s = string()): ps(new string(s)), i(0), use(new std::size_t (1)) {}
    // copy constructor, pointerlike 直接复制指针, use直接复制（使用同一块地址） 再计数+1
    HasPtr1(const HasPtr1 &other): ps(other.ps), i(other.i), use(other.use) {++*use;}
    // copy assignment, 右边的计数增加， 左边的计数减少， 处理self-assignment
    HasPtr1& operator=(const HasPtr1 &rhs) {
        ++*rhs.use;  // 先加右边，rhs和this相同时，如果先减左边就会出问题
        if (--*use == 0) {
            delete ps;
            delete use;
        }
        // 复制
        ps = rhs.ps;
        i = rhs.i;
        use = rhs.use;
        return *this;
    }
    // destructor
    ~HasPtr1() {
        // 每次调用use 计数减1， 为0时，销毁ps
        if (--*use == 0) {
            delete ps;
            delete use;
        }
    }
private:
    string *ps;
    int i;
    std::size_t *use;  // 自定义的counter
};


// q_13_28
// pointerlike
class TreeNode {
public:
    TreeNode(): value(0), count(new int(1)), left(nullptr), right(nullptr)  {}
    TreeNode(const TreeNode &rhs);
    TreeNode& operator=(const TreeNode &rhs);
    ~TreeNode();
private:
    std::string value;
    int *count;  // 节点使用计数
    TreeNode *left;
    TreeNode *right;
};

TreeNode::TreeNode(const TreeNode &rhs) : value(rhs.value), count(rhs.count), left(rhs.left), right(rhs.right) {
    ++*count;
}

TreeNode& TreeNode::operator=(const TreeNode &rhs) {
    ++*rhs.count;
    if (--*count == 0) {
        delete left;
        delete right;
        delete count;
    }
    value = rhs.value;
    left = rhs.left;
    right = rhs.right;
    count = rhs.count;
    return *this;
}

TreeNode::~TreeNode() {
    if (--*count == 0) {
        delete left;
        delete right;
        delete count;
    }
}

// valuelike
class BinStrTree{
public:
    // 构造函数，一个默认的root Node
    BinStrTree(): root(new TreeNode()){};
    BinStrTree(const BinStrTree &rhs) : root(new TreeNode(*rhs.root)){};
    BinStrTree& operator=(const BinStrTree &rhs);
    ~BinStrTree() {delete root;}
private:
    TreeNode *root;
};

BinStrTree &BinStrTree::operator=(const BinStrTree &rhs) {
    // 先创建临时变量，再删除原来的root，再赋值
    TreeNode *tmp = new TreeNode(*rhs.root);
    delete root;
    root = tmp;
    return *this;
}

// swap
inline
void swap(HasPtr &lhs, HasPtr &rhs) {
    // 交换 i和ps 而不是整个对象
    using std::swap;
    cout << "执行swap" << endl;
    // 不要使用 std::swap(lhs.i, rhs.i)
    swap(lhs.ps, rhs.ps);  // 会自己寻找是使用library版本的swap还是自定义的swap
    swap(lhs.i, rhs.i);
}

// Using swap in Assignment Operators
HasPtr& HasPtr::operator=(HasPtr rhs) {  // 值传递，会使用copy constructor创建local variable
    swap(*this, rhs);  // 使用上述定义的swap，交换当前和rhs，i和ps都交换
    return *this;   // rhs临时变量删除，其ps被删除
}

void q_13_29() {
    /*
    * Explain why the calls to swap inside swap(HasPtr&, HasPtr&) do
not cause a recursion loop.
     swap(HasPtr&, HasPtr&) 里面是三个不同的函数
     参数类型 HasPtr&, string & 和 int &
     */
}

void q_13_30() {
    HasPtr p1("这是p1"), p2("这是p2", 24);
    p1.show();
    p2.show();
    swap(p1, p2);
    p1.show();
    p2.show();
}

int main(int argc, char *argv[]) {
    /*
     * 1. 需要destructor的基本需要copy-constructor 和 copy-assignment
     * 2. 需要copy constructor的基本需要copy-assignment， vice versa
     */
    q_13_30();
    q_13_26();
    q_13_18();
    q_13_16();
    // q_13_15();
    // q_13_14();
    cout << "=================" << endl;
    cout << "使用new 创建" << endl;
    X *px = new X;
    cout << "参数传递，引用/值, 值传递调用一次copy constructor" << endl;
    q_13_13(*px, *px);
    cout << "结束q_13_13 delete px,释放所指向的对象" << endl;
    delete px;
    cout << "=================" << endl;
    q_13_12();
    test_destructor();
    q_13_7();
    return 0;
}
