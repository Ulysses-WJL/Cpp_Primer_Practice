#include <iostream>
#include "Quote.h"
#include "Bulk_quote.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

// test dynamic binding

class Animal {
    public:
    virtual void speak() {cout << "Animal say 'Hello World'" << endl;};
};

class Dog : public Animal {
public:
    void speak() override {cout << "Dog say 'Hello World'" << endl;};
};

void test_dynamic_binding() {
    Animal a;
    Dog d;
    // 使用reference 或ptr ， 运行时 动态绑定
    Animal &ref1 = a;
    Animal &ref2 = d;
    Animal *ptr = &d;
    ref1.speak();
    ref2.speak();
    ptr->speak();
    // 直接使用对象，编译器使用静态绑定
    Animal b = Dog();
    b.speak();
}

double print_total(std::ostream &os, const Quote &item, size_t n) {
    double ret = item.net_price(n);  // static type是 Quote &, dynamic type运行时才知道
    os << "ISBN: " << item.isbn()
        << " # sold: " << n
        << " total due: " << ret << endl;
    return ret;
}


void derived_to_base_conversion() {
    Quote item;
    Bulk_quote bulk;
    Quote *p = &item;
    //  derived-to-base
    p = &bulk;
    Quote &r = bulk;
}

void base_to_derived_conversion() {
    // Base 类不能自动转为 派生类， 编译时 编译器决定
    Quote base;
    // Bulk_quote* bulkP = &base;  // Cannot initialize a variable of type 'Bulk_quote *' with an rvalue of type 'Quote *'
    // Bulk_quote& bulkP = base;  // Non-const lvalue reference 'bulkP' to type Bulk_quote cannot bind to lvalue of type Quote‘

    Bulk_quote bulk;
    Quote *itemP = &bulk; // ok: dynamic type is Bulk_quote
    // Bulk_quote *bulkP = itemP; // error: can’t convert base to derived
}


class Base {
public:
    static void statmem() {cout << "Base stat" << endl;};
    virtual void foo() {cout << "Base foo" << endl;}
};
class Derived : public Base {
public:
    void f(const Derived & d);
    void foo() override {
        Base::foo();
        cout << "Derived foo" << endl;
    }
};

void Derived::f(const Derived &d) {
    Base::statmem();  // 通过Base类调用
    Derived::statmem();  // 通过Derived类调用
    d.statmem();  // 通过 派生类对象调用
    statmem();  // 通过 this 调用
}

// preventing inheritance
class NoDerived final {};  // NoDerived can’t be a base class

class Last final: Base {};

void test_preventing_inheritance() {
    // class Bad : NoDerived {};
    // class Bad2 : Last {};
}

void q_15_6() {
    Quote item("book1", 11.5);
    Bulk_quote bulk("book2", 11.5, 50, 0.2);
    print_total(cout, item, 100);
    print_total(cout, bulk, 80);
}

void q_15_8() {
    // Define static type and dynamic type
    // 静态类型，编译时已知的；动态类型是内存中的对象的类型，运行时才知道
}

void q_15_9() {
    // When is it possible for an expression’s static type to differ from its dynamic type?
    // Give three examples in which the static and dynamic type differ.
    // 指向基类的指针或引用， 它的静态类型可能与其动态类型不同。
}

void q_15_10() {
    // Recalling the discussion from §8.1 (p. 311), explain how the program on page 317
    // that passed an ifstream to the Sales_data read function works.

    // std::ifstream 是 std::istream 的派生基类，因此 read 函数能够正常工作。
}


void test_virtual_function() {
    Quote base("aaa", 21);
    Bulk_quote derived("aaa", 21, 10, 0.2);
    print_total(cout, base, 15);
    print_total(cout, derived, 15);
    // 只有当使用指针或引用调用virtual function 才会有 dynamic binding
    base = derived;  // plain type, 编译时就绑定了
    cout << "due : " << base.net_price(20) << endl;   // calls Quote::net_price

}

struct B {
    virtual void f1(int) const;
    virtual void f2();
    void f3();
};
struct D1 : B {
    void f1(int) const override; // ok: f1 matches f1 in the base
    // void f2(int) override; // error: B has no f2(int) function
    // void f3() override; // error: f3 not virtual
    // void f4() override; // error: B doesn’t have a function named f4
};

struct D2 : B {
    // inherits f2() and f3() fromB and overrides f1(int)
    // 函数使用final后，子类不能重载这个函数了
    void f1(int) const final; // subsequent classes can’t override f1(int)
};
struct D3 : D2 {
    void f2(); // ok: overrides f2 inherited from the indirect base, B
    // void f1(int) const; // error: D2 declared f2 as final
};

void circumventing_virtual_mechanism() {
    Bulk_quote derived("aaa", 10.5, 15, 0.2);
    Quote* baseP = &derived;
    // 使用 scope operator  编译时 决定调用的函数
    double undiscounted = baseP->Quote::net_price(20);
    // 成员函数（或友元函数）内部的代码才需要 scope operator，
    // 派生类的virtual function调用基类的函数，做一些common work
    cout << "due : " << undiscounted << endl;

    Derived derived_derived;
    derived_derived.foo();

}

void q_15_11() {
    Quote base;
    Bulk_quote derived;
    base.debug();
    derived.debug();
}

void q_15_12() {
    // Is it ever useful to declare a member function as both override and final ?
    // Why or why not ?
    // 有必要，声明为override是为了表示重写基类的virtual function， final是为了阻止其派生类重写该函数，
}


// q_15_13
class base {
public:
    base() = default;
    string name() { return basename; }
    virtual void print(std::ostream &os) { os << "base" << basename << endl;; }
private:
    string basename;
};
class derived : public base {
public:
    derived() = default;
    void print(std::ostream &os) override { base::print(os); os << " " << i << endl; }
private:
    int i;
};

void q_15_13() {
    derived d;
    d.print(cout);
}

void q_15_14() {
    cout << "===============q_15_14================" << endl;
    base bobj;
    base *bp1 = &bobj;
    base &br1 = bobj;
    derived dobj;
    base *bp2 = &dobj;
    base &br2 = dobj;

    bobj.print(cout);  // 编译时，基类对象调用
    dobj.print(cout);  // 编译时，派生类对象调用
    bp1->name();  // 编译时，基类的指针 调用
    bp2->name();  //  编译时，派生类指针 调用base的 name
    br1.print(cout);  // 运行时，调用virtual function
    br2.print(cout);  // 运行时， 调用virtual function
    cout << "===============q_15_14================" << endl;
}

void q_15_17() {
    // error: cannot declare variable ‘d’ to be of abstract type
    // Disc_quote d;
}

class Base1 {
    friend class Pal;
protected:
    int prot_mem; // protected member
};
class Sneaky : public Base1 {
    friend void clobber(Sneaky&); // can access Sneaky::prot_mem
    friend void clobber(Base1&); // can’t access Base::prot_mem
    int j;  // j is private by default
};


// 派生类的成员和友类只能访问嵌入在派生类型对象中的基类对象中的受保护成员
void clobber(Sneaky &s) { s.j = s.prot_mem = 0; }
// clobber 不是Base1的友元
// void clobber(Base1 &b) {b.prot_mem = 0;} // Member is inaccessible

// 派生类能否访问基类的member，由基类的access specifier控制
class Base2 {
public:
    void pub_mem() {}; // public member
protected:
    int prot_mem; // protected member
private:
    char priv_mem; // private member
};


struct Pub_Derv: public Base2 {
    int f() {return prot_mem;}
    // char g() {return priv_mem;}
    void memfcn(Base2 &b) { b = *this; }
};

// derivation access specifier 控制派生类如何使用
// 继承自基类的member
struct Priv_Derv : private Base2 {
    // private derivation doesn’t affect access in the derived class
    int f1() const { return prot_mem; }
    void memfcn(Base2 &b) { b = *this; }
};

void test_inheritance() {
    Pub_Derv pub;
    Priv_Derv priv;
    pub.pub_mem();
    // priv.pub_mem();  // pub_mem is private in the derived class
}


// friendship 无法转换或继承
class Pal {
public:
    int f(Base1 b) {return b.prot_mem;}
    // Pal 不是Sneaky的友元，无法访问Sneaky的private成员j
    // int f2(Sneaky s) {return s.j;}
    // Pal是Base1的友元，可以访问Base1的protect成员prot_mem, 包括对嵌入在派生自Base的类型的对象中的Base对象的访问
    int f3(Sneaky s) {return s.prot_mem;}
};

// Exempting Individual Members
class Base3 {
public:
    std::size_t size() const {return n;}
protected:
    std::size_t n = 0;
};

// 使用using 后 访问控制由using前的 access specifier 控制
class Derived3 : private Base3 {
public:
    // maintain access levels for members related to the size of the object
    using Base3::size;
protected:
    using Base3::n;
};

void test_exempting_individual_members() {
    Derived3 derived;
    cout << derived.size() << endl;
}

class Prot_derv: protected Base2 {
    void memfcn(Base2 &b) { b = *this; }
};

class Derived_from_Public: public Pub_Derv {
    void memfcn(Base2 &b) { b = *this; }
};

class Derived_from_Private: public Priv_Derv {
    // 派生类D的派生类的成员函数和友元需要public、protect继承D才能使用 derived-to-base的转换；
    // void memfcn(Base2 &b) { b = *this; }
};

class Derived_from_Protected: public Prot_derv {
    void memfcn(Base2 &b) { b = *this; }
};

void q_15_18() {
    /*
    *
    只有在派生类是使用public的方式继承基类时，user code 才可以使用派生类到基类（derived-to-base）的转换
     */
    Pub_Derv d1;
    Priv_Derv d2;
    Prot_derv d3;
    Derived_from_Public dd1;
    Derived_from_Private dd2;
    Derived_from_Protected dd3;
    Base2 *p = &d1; // d1 has type Pub_Derv  合法
    // p = &d2; // d2 has type Priv_Derv  不合法
    // p = &d3; // d3 has type Prot_Derv  不合法
    p = &dd1; // dd1 has type Derived_from_Public  合法
    // p = &dd2; // dd2 has type Derived_from_Private  不合法
    // p = &dd3; // dd3 has type Derived_from_Protected  不合法
}

void q_15_19() {
    /**
     * 类成员函数中执行 dervied-to-base的conversion，
    * 派生类D的成员函数和友元总是可以执行derived-to-base的转换；
    * void memfcn(Base &b) { b = *this; }
    派生类D的派生类的成员函数和友元需要public、protect继承D才能使用 derived-to-base的转换；
     * 合法： Pub_Derv， Priv_Derv， Prot_Derv, Derived_from_Public, Derived_from_Protected
     * 不合法： Derived_from_Private
     */
}

// 15_21: 2Dshape


class Shape {
public:
    typedef std::pair<double, double > Coordinate;
    Shape() = default;
    Shape(const string &n) : name(n) {};
    virtual double perimeter() const = 0;  // 抽象基类，pure virtual function 不需要实现
    virtual double area() const = 0;
    virtual ~Shape() = default;

private:
    string name;
};

class Rectangle : public Shape {
public:
    Rectangle() = default;
    Rectangle(
        const string &n,
        const Coordinate &d, const double w, const double h) : Shape(n), left_up(d), width(w), height(h) {};
    double area() const override {return width * height;};
    double perimeter() const override {return 2 * (width + height);};
    ~Rectangle() override = default;
protected:
    Coordinate left_up;
    double width;
    double height;
};

class Square : public Rectangle {
public:
    Square() = default;
    Square(const string &n, const Coordinate &d, double w): Rectangle(n, d, w, w) {};
    ~Square() override = default;
};

void q_15_21() {
    Square square("正方形", std::pair<double, double>(0.0, 0.0), 10.0);

    cout << "area: " << square.area() << endl;
    cout << "perimeter: " << square.perimeter() << endl;
}

// name collisions
struct BaseName {
    BaseName(): mem(0){};
    int memfunc() {return mem;}
protected:
    int mem;
};

struct DerivedName : public BaseName {
    DerivedName(int i): mem(i) {};
    int get_mem() const {return  BaseName::mem;}  // 使用scope operator
    int memfunc(int i) const {return mem;}
protected:
    int mem;
};

void test_name_collisions() {
    DerivedName d(42);
    BaseName b;
    cout << d.get_mem() << endl;
    b.memfunc();  // 基类的 memfunc
    d.memfunc(10);  // 派生类的memfunc
    // name lookup happens before type checking

    // d.memfunc();  // 基类的memfunc被覆盖， 即时参数列表都不一样
    d.BaseName::memfunc();
}


class BaseFunc {
public:
    virtual int fcn() {return 0;};
};
class D1Func : public BaseFunc {
public:
    // hides fcn in the base; this fcn is not virtual
    // D1 inherits the definition of Base::fcn()
    int fcn(int i) {return i;}; // parameter list differs from fcn in Base
    virtual void f2() {}; // new virtual function that does not exist in Base
};
class D2Func : public D1Func {
public:
    int fcn(int i) {return i;}; // nonvirtual function hides D1::fcn(int)
    int fcn() {return 1001;}; // overrides virtual fcn from Base
    void f2() {}; // overrides virtual f2 from D1
};

void test_hidden_virtual_func() {
    BaseFunc bobj; D1Func d1obj; D2Func d2obj;
    // 使用基类的指针
    BaseFunc *bp1 = &bobj, *bp2 = &d1obj, *bp3 = &d2obj;
    bp1->fcn(); // virtual call, will call Base::fcn at run time
    bp2->fcn(); // virtual call, will call Base::fcn at run time
    bp3->fcn(); // virtual call, will call D2::fcn at run time
    D1Func *d1p = &d1obj; D2Func *d2p = &d2obj;
    // derived-to-base, 基类中没有f2
    // bp2->f2(); // error: Base has no member named f2
    d1p->f2(); // virtual call, will call D1::f2() at run time
    d2p->f2(); // virtual call, will call D2::f2() at run time
    BaseFunc *p1 = &d2obj;
    D1Func *p2 = &d2obj;
    D2Func *p3 = &d2obj;
    // p1->fcn(42);  // base 中的fcn 是无参数的


    p2->fcn(42);
    p3->fcn(42);
}


int main(int argc, char *argv[]) {
    test_name_collisions();
    q_15_21();
    q_15_17();
    q_15_14();
    q_15_13();
    q_15_11();
    circumventing_virtual_mechanism();
    test_virtual_function();
    q_15_6();
    test_dynamic_binding();
    Quote q("aaa", 25.5);
    auto due = print_total(cout, q, 100);
}
