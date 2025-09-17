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
    string name() { return basename; }
    virtual void print(std::ostream &os) { os << "base" << basename << endl;; }
private:
    string basename;
};
class derived : public base {
public:
    void print(std::ostream &os) override { base::print(os); os << " " << i << endl; }
private:
    int i;
};

void q_15_13() {
    derived d;
    d.print(cout);
}

int main(int argc, char *argv[]) {
    q_15_13();
    q_15_11();
    circumventing_virtual_mechanism();
    test_virtual_function();
    q_15_6();
    test_dynamic_binding();
    Quote q("aaa", 25.5);
    auto due = print_total(cout, q, 100);
}
