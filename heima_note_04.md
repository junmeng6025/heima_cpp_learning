# Part 4 函数高阶

## 默认参数
- 在C++中，函数形参列表中的形参是可以有默认值的。
- 调用函数时，有默认值的参数可以被缺省；也可以传入参数覆写默认值
- 语法：`返回值类型 函数名 （参数 = 默认值）{函数体}`
- 如果某个位置的参数有默认值，那么它后面位置的参数都必须有默认值
- 如果函数声明有默认值，函数定义的时候就不能再赋有默认参数
    - 声明和定义只能有一处给出默认参数
    - 分文件时，默认参数只能写在声明里（头文件），否则默认参数没有意义，编译器不认

```cpp
int func1(int a, int b, int c)
{
    return a + b + c;
}

// 如果某个位置的参数有默认值，那么它后面位置的参数都必须有默认值
int func2(int a, int b = 10, int c = 20)
{
    return a + b + c;
}

// 如果函数声明有默认值，函数定义的时候就不能再赋有默认参数
int func3(int a = 10, int b = 20);  // 声明

int func3(int a, int b);  // 定义
{
    return a + b;
}

int main()
{
    cout << func1(10, 20, 30) << endl;
    cout << func2(10) << endl;  // a = 10
    cout << func2(10, 30) << endl;  // a = 10, b = 30
}
```

## 占位参数
- C++中函数的形参列表里可以有占位参数，调用函数时必须填补该位置
- 在形参列表中只给出返回值类型，不定义参数名
- 由于没有参数名，这个参数在函数体中并不会被使用，故名 “占位”
- 占位参数也可以有默认值
  > 目前看起来没啥用。。。  
  > 有默认值的占位参数，调用函数时不用传值，函数体内部也不使用

```cpp
int func4(int a, int )
{
    return a + 10;
}

int func5(int a, int = 10)
{
    return a + 10;
}

int main()
{
    cout << func4(10，10) << endl;
    cout << func5(10) << endl;
}
```

# 函数重载
- 作用：函数名可以相同，提高复用性
## 函数重载的条件：
- 同一个作用域下
- 函数名相同
- 函数形参列表不同：参数 **类型不同**，或 **个数不同**，或 **顺序不同**
- ！函数的返回值不可以作为函数重载的条件
    > 重载函数的返回值可以不同，但并不是重载的条件
  
```cpp
double func(int a, double b)
{
    cout << "call A: func(int a, double b)" << endl;
    return a + b;
}

double func(double a, int b)
{
    cout << "call B: func(double a, int b)" << endl;
    return a + b;
}

int main()
{
    cout << func(10, 3.14) << endl;  // call A: func(int a, double b) 13.14
    cout << func(3.14, 10) << endl;  // call B: func(double a, int b) 13.14
}
```

## 函数重载注意事项

### **引用作为重载条件**

```cpp
void func(int & a)
{
    cout << "call: func(int &a)" << endl;
}

void func(const int & a)
{
    cout << "call: func(const int &a)" << endl;
}

int main()
{
    int a = 10;
    func(a);  // call: func(int &a)
              // int &a = 10; ——> ERROR

    func(10); // call: func(const int &a)
              // const int &a = 10; ——> PASS

    const int b = 20;
    func(b); // call: func(const int &a)
}
```

### **函数重载碰到函数默认参数**

```cpp
void func(int a)
{
    cout << "call: func(int &a)" << endl;
}

void func(int a, int b = 10)
{
    cout << "call: func(const int &a)" << endl;
}

int main()
{
    
    func(10);  // ERROR：函数重载遇到默认参数，出现歧义
    // 函数重载应尽量避免使用默认参数
}
```