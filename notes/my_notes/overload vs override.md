在C++中，**overload（重载）** 和 **override（重写）** 是两个重要的概念，它们都与函数相关但有着本质的区别。

## Overload（重载）

### 定义
在**同一个作用域内**，函数名相同但**参数列表不同**的多个函数。

### 特点
- 在同一个类或命名空间内
- 函数名必须相同
- 参数列表必须不同（参数类型、个数或顺序）
- 返回类型可以相同也可以不同
- 编译时多态（静态多态）

### 示例
```cpp
class Calculator {
public:
    // 重载示例：函数名相同，参数列表不同
    int add(int a, int b) {
        return a + b;
    }
    
    double add(double a, double b) {
        return a + b;
    }
    
    int add(int a, int b, int c) {
        return a + b + c;
    }
    
    // 错误：仅返回类型不同，不能构成重载
    // double add(int a, int b); // 编译错误
};

int main() {
    Calculator calc;
    calc.add(1, 2);        // 调用 int add(int, int)
    calc.add(1.5, 2.5);    // 调用 double add(double, double)
    calc.add(1, 2, 3);     // 调用 int add(int, int, int)
    return 0;
}
```

## Override（重写）

### 定义
在**继承关系**中，**派生类**重新定义**基类**的**虚函数**。

### 特点
- 必须有继承关系
- 基类函数必须是虚函数（`virtual`）
- 函数名、参数列表、返回类型必须完全相同
- C++11可以使用`override`关键字明确表示重写
- 运行时多态（动态多态）

### 示例
```cpp
class Animal {
public:
    virtual void makeSound() {
        std::cout << "Animal sound" << std::endl;
    }
    
    // 纯虚函数，必须被重写
    virtual void eat() = 0;
    
    // 非虚函数，可以被隐藏但不能被重写
    void sleep() {
        std::cout << "Animal sleeping" << std::endl;
    }
};

class Dog : public Animal {
public:
    // 重写基类的虚函数
    void makeSound() override {  // C++11 override关键字
        std::cout << "Woof!" << std::endl;
    }
    
    void eat() override {
        std::cout << "Dog eating" << std::endl;
    }
    
    // 隐藏基类的sleep函数（不是重写）
    void sleep() {
        std::cout << "Dog sleeping" << std::endl;
    }
};

class Cat : public Animal {
public:
    void makeSound() override {
        std::cout << "Meow!" << std::endl;
    }
    
    void eat() override {
        std::cout << "Cat eating" << std::endl;
    }
};

int main() {
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();
    
    animal1->makeSound();  // 输出: Woof! (多态调用)
    animal2->makeSound();  // 输出: Meow! (多态调用)
    
    delete animal1;
    delete animal2;
    return 0;
}
```

## 对比表格

| 特性 | Overload（重载） | Override（重写） |
|------|------------------|------------------|
| **作用域** | 同一个类或命名空间 | 继承关系的不同类 |
| **函数关系** | 同名函数 | 基类和派生类的虚函数 |
| **参数列表** | 必须不同 | 必须完全相同 |
| **返回类型** | 可以不同 | 必须相同（协变返回类型除外） |
| **virtual关键字** | 不需要 | 基类函数必须有 |
| **多态类型** | 编译时多态（静态） | 运行时多态（动态） |
| **C++11关键字** | 无 | `override`（可选但推荐） |

## 重要注意事项

### 1. 使用`override`关键字的好处
```cpp
class Base {
public:
    virtual void func(int) const;
};

class Derived : public Base {
public:
    // 如果没有override，下面的错误不会被编译器发现
    void func(int) override;        // 正确
    // void func(float) override;   // 编译错误：不是基类的虚函数
    // void Func(int) override;     // 编译错误：函数名拼写错误
};
```

### 2. 重载解析的优先级
```cpp
class Example {
public:
    void process(int x) { cout << "int: " << x << endl; }
    void process(double x) { cout << "double: " << x << endl; }
};

int main() {
    Example ex;
    ex.process(5);      // 调用 process(int)
    ex.process(5.0);    // 调用 process(double)
    ex.process('A');    // 调用 process(int) - char提升为int
    return 0;
}
```

### 3. 避免重写非虚函数
```cpp
class Base {
public:
    void nonVirtual() { cout << "Base" << endl; }
};

class Derived : public Base {
public:
    void nonVirtual() { cout << "Derived" << endl; }  // 隐藏，不是重写
};

int main() {
    Derived d;
    Base* b = &d;
    d.nonVirtual();  // 输出: Derived
    b->nonVirtual(); // 输出: Base (不是多态调用)
    return 0;
}
```

## 总结

- **Overload**：同一作用域内的函数多样性，编译时确定
- **Override**：继承体系中的多态行为，运行时确定
- 使用`override`关键字可以提高代码的安全性和可读性
- 理解两者的区别对于设计良好的面向对象程序至关重要
