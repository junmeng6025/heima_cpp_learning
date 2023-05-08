# 5.2 对象的初始化和清理
对象的初始化和清理是重要的安全问题
- 一个对象或变量没有初始状态，对其使用后果是未知的
- 使用完一个对象或变量，没有及时清理，也会引发一些安全问题


C++利用了构造函数和析构函数处理对象的初始化和清理，这两个函数将会被编译器自动调用。  
- **构造函数：** 创建对象时为对象的成员属性赋值，由编译器自动调用。
- **析构函数：** 对象销毁前由系统自动调用，执行清理工作。

初始化和清理是编译器强制要求我们做的事情，如果我们不提供，编译器会提供。  
编译器提供的构造函数和析构函数是空的实现。

## 2.1 构造函数 Constructor 
`类名称(){}`
1. 构造函数没有返回值也不写 void
2. 函数名称与类名称相同
3. 构造函数可以有输入参数，因此可以重载
4. 程序在调用对象时会自动调用构造函数，且只调用一次，无需手动调用。
## 2.2 析构函数 Destructor
`~类名称(){}`
1. 析构函数没有返回值也不写 void
2. 函数名与类名称相同，前面加上 ~
3. 析构函数不可以有输入参数，因此不能重载
4. 程序在对象销毁前会自动调用析构函数，且只调用一次，无需手动调用。

eg
```cpp
class Person
{
public:
    Person()
    {
        cout << "- Call Person constructor" << endl;
    }

    ~Person()
    {
        cout << "- Call Person destructor" << endl;
    }
};

void test()
{
    Person p0;
}

int main()
{   
    cout << "create Person in test():" << endl;
    test();
    cout << "create Person in main():" << endl;
    Person p1;
    system("pause");
    return 0;
}
```
输出
```
create Person in test():
- Call Person constructor
- Call Person destructor
create Person in main():
- Call Person constructor
Press any key to continue . . .
- Call Person destructor
```
- 在 test() 函数中实例化一个Person类的对象p0，随着test()函数执行完毕，存放在栈区的p0也被释放；  
- 在 main() 函数中实例化一个Person类的对象p1，main函数暂停在 system("pause") 这一行，所以p1还没有被释放，不会被调用析构函数。按下任意键之后，main函数结束，p1才会被释放，p1的析构才会被调用

## 2.3 构造函数的分类及调用
两种构造方式：
- 按参数分为：有参构造 & 无参构造
- 按类型分为：普通构造 & 拷贝构造

三种调用方式：
- 括号法
- 显式法
- 隐式转换法


```cpp
class Person
{
int m_age;
string m_name;

public:
    // Constructor-Without-param
    Person()
    {   
        m_age = 0;
        m_name = "Default";
        cout << "- Call Person constructor: Without-param" << endl;
    }

    // Constructor-With-param
    Person(int age, string name)
    {
        m_age = age;
        m_name = name;
        cout << "- Call Person constructor: With-param 2" << endl;
    }

    Person(int age)
    {
        m_age = age;
        m_name = "Default";
        cout << "- Call Person constructor: With-param 1" << endl;
    }

    // Constructor-Copy
    Person(const Person &p)
    {
        m_age = p.m_age;
        m_name = p.m_name;
        cout << "- Call Person constructor: Copy" << endl;
    }
    // Destructor: only one 
    ~Person()
    {
        cout << "- Call Person destructor" << endl;
    }
    // Methods:
    void prt()
    {
        cout << "Name: " << m_name << ";\tAge: " << m_age << endl;
    }
};

// Call Constructor
void test01()
{
    // 1. Bracket
    Person p1;
    p1.prt();

    Person p2(10, "MJ");
    p2.prt();

    Person p3(p2);
    p3.prt();
    // 2. Explicit
    Person p4;
    Person p5 = Person(10, "MJ");
    Person p6 = Person(p5);

    Person(10, "MJ");  // anonym obj
    cout << "Anonym object destructed?" << endl;

    // 3. Implicit transform
    Person p7 = 10;  // Person p7 = Person(10);
    Person p8 = p5;
}

int main()
{   
    test01();
    system("pause");
    return 0;
}
```


注意事项：
- **拷贝构造函数：** `Person(const Person &p)`  
  > 这里必须这样写而不用值传递，是因为值传递操作本身就调用了一次拷贝函数，而拷贝函数里又有值传递操作，就会形成无限递归出错
- 调用默认的无参构造函数时候，不要加 ( )。
  > 加了括号会被认为是函数声明，不会在此实例化对象。
- 显式法创建对象，等号右侧是一个**匿名对象**。
  > 当前执行结束后，系统会立即回收匿名对象。
- 不要使用拷贝构造函数初始化一个匿名对象。
  > 编译器会把语句解释为对象的声明，导致重定义报错： Person(p3); <=> Person p3;
- *问题：隐式转换接受多参数吗？*

## 2.4 拷贝构造函数的使用场景
- 使用一个已经创建好的对象初始化一个新的对象
- 值传递的方式给函数参数传值
- 以值的方式返回局部对象

## 2.5 构造函数调用规则
默认情况下，C++编译器会给一个类添加至少三个函数
- 默认构造函数（无参，空函数体）
- 默认析构函数（无参，空函数体）
- 默认拷贝构造函数，对属性进行值拷贝

构造函数调用规则：
- 如果用户定义了有参构造函数，C++不再提供默认无参构造函数，但提供默认拷贝构造函数
- 如果用户定义了拷贝构造函数，C++不会再提供其他构造函数

## 2.6 深拷贝、浅拷贝
- 浅拷贝：简单的赋值拷贝操作
- 深拷贝：在堆区重新申请空间，进行拷贝操作
  
```cpp
class Person
{
public:
    Person(int age, int height)
    {
        m_Age = age;
        m_pHeight = new int(height);
        cout << "Person constroctor called" << endl;
    }
    ~Person()
    {
        if (m_pHeight != NULL)
        {
            delete m_pHeight;
            m_pHeight = NULL;
        }
        cout << "Person destroctor called" << endl;
    }

    int m_Age;
    int *m_pHeight;
};

void test()
{
    Person p1(18, 160);
    Person p2(p1);
}

int main()
{
    test();
    system("pause");
    return 0;
}
```
1. p1在进行有参初始化时，在堆区申请了一个空间，p1的height指针就指向这个空间
2. p2在进行拷贝初始化时使用的是编译器提供的浅拷贝（默认的拷贝构造函数）
3. 浅拷贝是对成员变量的简单赋值，所以p2的height指针=p1的height指针,即两个height指针指向堆区的同一个地址
4. 函数test01结束后，p1和p2把同一个空间释放了两次，所以程序崩了

### 浅拷贝带来的问题：堆区内存重复释放  
> **解决方法：** 深拷贝，开辟另一个堆区地址，存放一样的数据  
> ！注意：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，避免编译器默认浅拷贝带来的问题。

```cpp
class Person
{
public:
    Person(const Person & p)
    {
        cout << "Person constroctor called: COPY" << endl;
        m_Age = p.m_Age;
        // m_pHeight = p.m_pHeight; -- default COPY 
        m_pHeight = new int(*p.m_pHeight);  // deep COPY
        
    }
    ~Person()
    {
        if (m_pHeight != NULL)
        {
            delete m_pHeight;
            m_pHeight = NULL;
        }
        cout << "Person destroctor called" << endl;
    }

    int m_Age;
    int *m_pHeight;
};
```

> 来自 ChatGPT 的回答：  

Q： 

C++当中深拷贝和浅拷贝是什么意思？
***

A：  

在C++中，深拷贝和浅拷贝是用来描述对象拷贝时的两种不同方式。

浅拷贝是指将一个对象的值复制到另一个对象中，而不复制它所指向的堆内存空间。这意味着如果原始对象的数据成员是指针类型，并且指向一个内存块，那么在浅拷贝后，两个对象将共享相同的内存块，从而可能导致潜在的问题。如果其中一个对象释放了内存，另一个对象仍然会引用这块内存，这会导致内存泄漏或访问无效内存的错误。

深拷贝是指将一个对象的值复制到另一个对象中，同时也复制指针所指向的内存块。这意味着在深拷贝后，两个对象将拥有完全不同的内存空间，不会相互干扰或共享内存，从而避免了潜在的问题。

为了实现深拷贝，通常需要自定义一个复制构造函数或者赋值运算符重载函数，用于在对象创建或者赋值时创建新的内存空间并拷贝数据，从而确保两个对象拥有不同的内存空间。

总之，在C++中，如果类中存在指针类型的成员变量，那么在进行拷贝操作时，应该慎重考虑采用深拷贝还是浅拷贝。如果采用浅拷贝，需要注意内存共享的问题，而深拷贝则可以避免这些问题。

***
<br>  


## 2.7 初始化列表
在构造函数后面添加成员属性的初始值信息  
**格式：** `构造函数(): 属性1(值1), 属性2(值2), ... {构造函数体}`
```cpp
class Person
{
public:
    int m_Id;
    int m_Age;
    double m_Height;

    // 传统方法：定义有参构造函数，在构造函数内对属性赋值
    Person(int id, int age, double height)
    {
        // 已进入构造函数
        m_Id = id;
        m_Age = age;
        m_Height = height;
    }
    // 无参构造函数+初始化列表：所有对象只有唯一的一套初始化值
    Person(): m_Id(0), m_Age(25), m_Height(1.75)
    {}
    // 有参构造函数+初始化列表：初始化值可以定义
    Person(int id, int age, double height): m_Age(id), m_Age(age), m_Height(height)
    {}

    ~Person(){}
};
```
初始化列表相当于（直接声明一个有初始值的类型），省略了赋值操作。传统赋值初始化是相当于（先声明类，再做赋值操作）；在大型项目中，class类中成员变量极多的情况下，初始化列表效率更高。  

**这么写比创建变量赋初值的好处是什么？**
> 真正的初始化发生在构造函数语句前，即初始化列表处。这个方法可以用在类嵌套中直接对类中类进行赋值，只需要调用一次函数实现多个类不同属性初始化。所以用传统方法需要一次初始化和一次拷贝（赋值）的开销。对于大的对象成员（下一节），这种开销会影响程序性能

## 2.8 类对象作为类成员
C++类中的成员可以是另一个类的实例对象，这种成员称为 `对象成员`，例如：
```cpp
class A {};
class B
{
    A a;
};
```
当创建B对象时，A和B的构造和析构顺序是谁先谁后？
```cpp
// class A: member object
class Phone
{
public:
    Phone(string brand)
    {
        m_Brand = brand;
        cout << "-- Phone constroctor called" << endl;
    }
    ~Phone()
    {
        cout << "-- Phone destroctor called" << endl;
    }

    string m_Brand;
};

// class B:
class Person
{
public:
    Person(string name, string phoneBrand):m_Name(name), m_Phone(phoneBrand)
    {
        /* initialization list: */
        // m_Name = name;
        // m_Phone = phoneBrand;  implicit transform
        //   m_Phone = Phone(phoneBrand)
        cout << "- Person constroctor called" << endl;
    }
    ~Person()
    {
        cout << "- Person destroctor called" << endl;
    }

    string m_Name;
    Phone m_Phone;
};

void test()
{
    Person p("MJ", "Huawei");
    cout << p.m_Name << " has a phone of: " << p.m_Phone.m_Brand << endl;
}

int main()
{
    test();
    system("pause");
    return 0;
}
```
输出
```
-- Phone constroctor called
- Person constroctor called
MJ has a phone of: Huawei
- Person destroctor called
-- Phone destroctor called
```
**结论：内层的类对象会先构造、后析构**

## 2.9 静态成员
在成员函数或成员变量前加上 `static` 关键字修饰  
- **静态成员变量**
  - 所有对象共享同一份数据
  - 在编译阶段分配内存，在全局区
  - 类内声明，类外初始化：必须给一个初始值
- **静态成员函数**
  - 所有对象共享同一个函数
  - 静态成员函数只能访问静态成员变量

### 2.9.1 静态成员变量
```cpp
class Person
{
public:
    static int m_Age;
};

int Person::m_Age = 10;

void test()
{
    Person p1;
    cout << p1.m_Age << endl;  // 10

    Person p2;
    p2.m_Age = 20;

    cout << p1.m_Age << endl;  // 20
}

int main()
{
    test();
    return 0;
}
```
静态成员变量不专属于某个对象上，所有对象都共享同一份数据。静态成员变量有两种访问方式：
- 通过对象访问
  ```cpp
  Person p1;
  cout << p1.m_Age << endl;
  ```
- 通过类名访问
  ```cpp
  cout << Person::m_Age << endl;
  ```

静态成员变量也是有访问权限设定的。
> 对于设为私有的静态成员变量，需要通过类内的 get() / set() 函数来访问

### 2.9.1 静态成员函数
静态成员函数只能访问静态成员变量
```cpp
class Person
{
public:
    static int m_A;
    int m_B;

    static void func_st()
    {
        m_A = 200;
        //m_B = 200; // ERR
        cout << "static func called, static attr m_Age is " << m_Age << endl;
    }
};

int Person::m_A = 100;
```

静态成员函数不可以访问非静态成员变量：
> 静态函数在内存中只有一份，所有该类实例化的对象都会共享这个函数；而非静态成员变量是依附于各个实例化对象的。  
> 因此，在所有同类对象所共享的静态函数中，访问由具体对象专有的非静态变量，函数体会不明白访问的是哪一个对象的成员变量。  
> 而静态成员变量就不存在这种歧义问题，因为它也不依附于具体对象，是相对于整个类而存在的。

静态成员函数也可以通过两种方式访问：
- 通过对象访问
  ```cpp
  Person p;
  p.func_st();
  ```
- 通过类名访问
  ```cpp
  Person::func_st();
  ```
  需要注意的是，非静态成员函数也不依附于具体的对象，但只能通过实例化的对象被调用