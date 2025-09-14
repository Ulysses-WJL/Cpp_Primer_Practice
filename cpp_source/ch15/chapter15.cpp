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
    ref1.speak();
    ref2.speak();
    // 直接使用对象，编译器使用静态绑定
    Animal b = Dog();
    b.speak();
}

double print_total(std::ostream &os, const Quote &item, size_t n) {
    double ret = item.net_price(n);
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

class Base {
public:
    static void statmem() {cout << "Base stat" << endl;};
};
class Derived : public Base {
public:
    void f(const Derived & d);
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

int main(int argc, char *argv[]) {
    q_15_6();
    test_dynamic_binding();
    Quote q("aaa", 25.5);
    auto due = print_total(cout, q, 100);
}