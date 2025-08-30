#include  <iostream>
#include "../ch08/Sales_Data.h"
#include "../ch13/String.h"
#include "Book.h"
#include "../ch13/StrVec.h"

using std::cout;
using std::endl;
using std::cin;


void q_14_1() {
    /*
    * In what ways does an overloaded operator differ from a built-in operator?
In what ways are overloaded operators the same as the built-in operators?
不同：
1，可以直接调用重载运算符函数  operator+()
2. 重载运算符的要么是class的member，要么至少一个参数是对应类类型
3. 一些操作符保证操作数的求值顺序。这些操作符的重载版本不保留求值顺序和/或短路求值（short-circuit）  logical and/or: &&, ||
相同：
    重载的运算符和built-in的运算符右相同的优先级和结合性
     */
}

void q_14_2() {
    Sales_Data data1, data2;
    cin >> data1 >> data2;
    data1 += data2;
    cout << data1 << endl;
    Sales_Data data3 = data1 + data2;
    cout << data3 << endl;
}

void q_14_3() {
    /*
    * (a) "cobble" == "stone"    const char * 的 ==
    * (b) svec1[0] == svec2[0]   string的  ==
    * (c) svec1 == svec2   vector 的 ==
    * (d) svec1[0] == "stone"  string 的 ==
     */
}

void q_14_4() {
    /*
    * Explain how to decide whether the following should be class members:
    (a) %  Symmetric operators: non-member function
    (b) %=  修改了对象本身（that change the state of their object ） member function
    (c) ++  修改了对象本身 member function
    (d) ->  = [] () ->   must be defined as members
    (e) <<  Symmetric operators:  non-member
    (f) &&  Symmetric operators: non-member function
    (g) ==  Symmetric operators: non-member function
    (h) ()  = [] () ->   must be defined as members
     */
}

void q_14_7() {
    String s{"abcdef"};
    // cin >> s >> endl;
    cout << s << endl;
}

void q_14_15() {
    Book b1(0, "Book1", "Alice", "2024", 15);
    Book b2(0, "Book1", "Alice", "2024", 24);
    Book b3(1, "Book2", "Alice", "2024", 50);
    std::cout << std::boolalpha;
    cout << (b1 > b3) << endl;
    cout << (b1 == b2) << endl;
    cout << (b1 != b3) << endl;
    cout << (b1 + b2) << endl;
    Book b4(cin);
    std::cout << b4 << endl;

}

void q_14_23() {
    StrVec v;
    v = {"1", "2", "3"};
    cout << v;
}

void q_14_22() {
    Sales_Data s1("aa", 1, 2.5);
    s1 = "bbbb";
    cout << s1 << endl;
}

void q_14_26() {
    StrVec svec{"a", "b", "c"};
    const StrVec csvec = svec;
    svec[1] = 'a';
    cout << "svec: " << svec << endl;
    cout << "csvec: " <<  csvec << endl;
}


int main(int argc, char *argv[]) {
    int a = 1 + 2;
    q_14_26();
    q_14_22();
    q_14_23();
    // q_14_15();
    // q_14_2();
    // q_14_7();
}
