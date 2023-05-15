# 6. 继承
**继承是面向对象三大特性之一**（封装、继承、多态）  

在现实生活中，对事物的分类有父类、子类的情况。例如

```
动物  
├── 猫  
|   ├── 狸花猫 
|   ├── 布偶猫 
|   ├── 橘猫
|   ├── 波斯猫
|   └── ...
├── 狗  
|   ├── 哈士奇
|   ├── 萨摩耶
|   ├── 德牧
|   ├── 金毛
|   └── ...
├── 马
|   └── ...
└── ...
```
子类成员除了拥有父类包含的共性特征，在此基础上又拥有各自的特性。因此可以使用 **继承** 来复用代码，减少程序的冗余。

## 6.1 继承的基本语法
例如网站一般都有公共的头部、底部以及左侧目录列表，只有内容不同。  

接下来分别用一般的方法和继承的方法实现网页内容，来看一下继承存在的意义和好处

### **1）普通实现** 
分别定义 Java教程网站的类 和 Python教程网站的类 
```cpp
// JavaPage -------------------------------------------------------
class JavaPage
{
public:
	// common
	void header()
	{
		cout << "Home | Login | Regist" << endl;
	}
	void footer()
	{
		cout << "Help | Contact | WebMap" << endl;
	}
	void leftBar()
	{
		cout << " Java\n Python\n C++" << endl;
	}
	// java feature
	void content()
	{
		cout << "\t_______________________" << endl;
		cout << "\t|--< Java TUTORIAL >--|" << endl;
		cout << "\t|_____________________|" << endl;
	}
};

// PythonPage ----------------------------------------------------
class PythonPage
{
public:
	// common
	void header()
	{
		cout << "Home | Login | Regist" << endl;
	}
	void footer()
	{
		cout << "Help | Contact | WebMap" << endl;
	}
	void leftBar()
	{
		cout << " Java\n Python\n C++" << endl;
	}
	// python feature
	void content()
	{
		cout << "\t_________________________" << endl;
		cout << "\t|--< Python TUTORIAL >--|" << endl;
		cout << "\t|_______________________|" << endl;
	}
};
```
测试代码：
```cpp
void test01()
{
	cout << "This is webpage of JAVA Tutorial" << endl;
	JavaPage jp;
	jp.header();
	jp.leftBar();
	jp.content();
	jp.footer();

	cout << "----------------------------------" << endl;

	cout << "This is webpage of PYTHON Tutorial" << endl;
	PythonPage py;
	py.header();
	py.leftBar();
	py.content();
	py.footer();
}
```

***

### **2）继承实现**
先定义一个 BasePage，设计一个网站模板，把公用的顶部栏、侧边栏和底部栏包括进去
```cpp
// BasePage -------------------------------------------------------
class BasePage
{
public:
	// common part
	void header()
	{
		cout << "Home | Login | Regist" << endl;
	}
	void footer()
	{
		cout << "Help | Contact | WebMap" << endl;
	}
	void leftBar()
	{
		cout << " Java\n Python\n C++" << endl;
	}
};
```
再分别定义 java 和 python 网站的子类。声明时继承父类 BasePage 即可共享网站模板，子类里只需要声明自己特有的部分即可
```cpp
// INHERIT ========================================================
// JavaPageIn -----------------------------------------------------
class JavaPageIn : public BasePage
{
public:
	// java feature
	void content()
	{
		cout << "\t_______________________" << endl;
		cout << "\t|--< Java TUTORIAL >--|" << endl;
		cout << "\t|_____________________|" << endl;
	}
};
// PythonPageIn ---------------------------------------------------
class PythonPageIn : public BasePage
{
public:
	// python feature
	void content()
	{
		cout << "\t_________________________" << endl;
		cout << "\t|--< Python TUTORIAL >--|" << endl;
		cout << "\t|_______________________|" << endl;
	}
};
```
测试代码：和普通方式一样
```cpp
void test02()
{
	cout << "This is webpage of JAVA Tutorial" << endl;
	JavaPageIn jp;
	jp.header();
	jp.leftBar();
	jp.content();
	jp.footer();

	cout << "----------------------------------" << endl;

	cout << "This is webpage of PYTHON Tutorial" << endl;
	PythonPageIn py;
	py.header();
	py.leftBar();
	py.content();
	py.footer();
}
```

### **归纳：**
- 继承的语法： `class 子类名称 : 继承方式 父类名称`  
- 本节示例采用的是 **公共继承** 的方式  
- 子类也被称为 派生类
- 父类也被称为 基类
- 派生类当中的成员有两部分：
  - 从基类继承来的 共性部分
  - 自己额外专属的 个性部分

## 6.2 继承的方式
- 继承的语法： `class 子类名称 : 继承方式 父类名称`  
- 继承的方式有三种
  - 公共继承 public
  - 保护继承 protected
  - 私有继承 private

> 复习：成员属性  
> 类在设计时，可以把属性和行为放在不同的权限下，加以管理
> - public &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;公共：类内可以读写 $\sqrt{}$； 类外可以读写 $\sqrt{}$； 子类可以访问 $\sqrt{}$
> - protected &nbsp;保护：类内可以读写 $\sqrt{}$； 类外不可读写  $\times$； 子类可以访问 $\sqrt{}$
> - private &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;私有：类内可以读写 $\sqrt{}$； 类外不可读写 $\times$； 子类不能访问 $\times$

***
父类：
```cpp
class A
{
public:
    int a;
protected:
    int b;
private:
    int c;
};
```
***
子类：
- 1）公共继承 public
  > 父类里的 public、protected 属性在子类里保持原样；  
  > 父类里的 private 属性在子类里不可访问

    ```cpp
    class B: public A
    {
    public:
        int a;
    protected:
        int b;
    
        // int c;  inaccessible
    };
    ```

- 2）保护继承 protected
  > 父类里的 public、protected 属性在子类里都变为 protected；  
  > 父类里的 private 属性在子类里不可访问

    ```cpp
    class B: protected A
    {
    protected:
        int a;
    protected:
        int b;
    
        // int c;  inaccessible
    };
    ```
- 3）私有继承 private
  > 父类里的 public、protected 属性在子类里都变为 private；  
  > 父类里的 private 属性在子类里不可访问

    ```cpp
    class B: private A
    {
    private:
        int a;
    private:
        int b;
    
        // int c;  inaccessible
    };
    ```

## 6.3 继承中的对象模型
**Q:** 从父类继承过来的成员，哪些属于子类对象中？  

**A:** 父类中所有非静态成员属性都会被子类继承下去。父类中的私有属性只是被编译器隐藏了，因此只是访问不到，而并不是没有被继承。

使用开发人员命令行窗口查看对象模型
- 跳转到盘符
- 跳转到文件路径 cd
- 查看命令
  ```
  cl /d1 reportSingleClassLayout类名 "文件名.cpp"
  ```

> **结论：** 父类当中的私有属性在子类中只是被隐藏了，本质上还是被继承下去的

## 6.4 继承中构造和析构的顺序
子类继承父类，当创建子类对象时，父类的构造函数也会被调用。那么父类和子类的构造和析构顺序是谁先谁后？

编写一个简单的测试案例：
```cpp
#include <iostream>
#include <string>
using namespace std;

class Base
{
public:
	Base()
	{
		cout << "Base class constructed" << endl;
	}
	~Base()
	{
		cout << "Base class destructed" << endl;
	}
};

class Son:public Base
{
public:
	Son()
	{
		cout << "\tSon class constructed" << endl;
	}
	~Son()
	{
		cout << "\tSon class destructed" << endl;
	}
};

void test()
{
	Son son;
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
Base class constructed
        Son class constructed
        Son class destructed
Base class destructed
```
> **结论：** 构造时父类先构造；析构时父类后析构

## 6.5 同名成员处理方式
当子类与父类包含同名的成员，如何通过子类对象正确访问到子类或父类当中的重名成员呢？  

- 访问子类成员：通过子类对象直接访问 
  ```cpp
  son.m_A
  son.func()
  ```
- 访问父类成员：加上父类名作为作用域访问
  ```cpp
  son.Base::m_A
  son.Base::func()
  ```

注意，对于成员函数，函数重载也会涉及到同名调用的情况。如果同名成员函数在父类里存在重载，只要调用父类的成员函数都需要加上父类作用域

例程：
```cpp
class Base
{
public:
	Base()
	{
		m_A = 100;
	}

	void func()
	{
		cout << "Base func() called" << endl;
	}
	void func(int a)
	{
		cout << "Base func(int a) called" << endl;
	}

	int m_A;
};

class Son:public Base
{
public:
	Son()
	{
		m_A = 200;
	}

	void func()
	{
		cout << "Son  func() called" << endl;
	}

	int m_A;
};

void test()
{
	Son son;
	cout << "son.m_A = " << son.m_A << endl;  // 200
	cout << "son.Base::m_A = " << son.Base::m_A << endl;  // 100
	son.func();  // Son  func() called
	son.Base::func();  // Base func() called
	//son.func(100);  // ERR
	son.Base::func(100);  // Base func(int a) called
	
}
```

## 6.6 同名静态成员处理方式
静态成员：
- 静态成员变量：类内声明，类外初始化
- 静态成员函数：只能访问静态成员变量，不能访问非静态成员变量

静态成员可以通过类名访问
```cpp
Son::m_A
Son::func()

Son::Base::m_A
Son::Base::func()
```

## 6.7 多继承语法
允许一个子类继承多个父类。语法 `class 子类：继承方式 父类1， 继承方式 父类2 ...`

多继承可能会出现同名成员的情况，调用时需要加上作用域进行区分

**实际开发中不建议使用多继承**

## 6.8 菱形继承

```
	Base
	/  \
Son1    Son2
    \  /
	Son3
```

可以看到，Son3 类会把 Base 类的成员继承两次，分别是通过 Son1 和 Son2，导致冗余和二义性。

解决方法是让 Son1 和 Son2 继承 Base 时使用 **虚继承**。这样，中间子类 Son1 和 Son2 持有的仅仅是指针 vbptr，最终指向唯一的数据，即 Son3 当中的成员

编写例程：
```cpp
#include <iostream>
#include <string>
using namespace std;

class Base
{
public:
	int m_A;
};

class Son1 : virtual public Base {};  // virtual inherit
class Son2 : virtual public Base {};  // virtual inherit
class Son3 : public Son1, public Son2 {};

void test()
{
	Son3 son3;
	son3.Son1::m_A = 100;
	son3.Son2::m_A = 200;

	cout << "son3.Son1::m_A = " << son3.Son1::m_A << endl;
	cout << "son3.Son2::m_A = " << son3.Son2::m_A << endl;
	cout << "son3.m_A = " << son3.m_A << endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}
```

在 `开发者命令行窗口 (Developer Command Prompt)` 运行指令：
```
cd <path/to/the/script>
cl /d1 reportSingleClassLayoutSon3 main.cpp
```
得到类结构的分析：
```
class Son3      size(12):
        +---
 0      | +--- (base class Son1)
 0      | | {vbptr}
        | +---
 4      | +--- (base class Son2)
 4      | | {vbptr}
        | +---
        +---
        +--- (virtual base Base)
 8      | m_A
        +---

Son3::$vbtable@Son1@:
 0      | 0
 1      | 8 (Son3d(Son1+0)Base)

Son3::$vbtable@Son2@:
 0      | 0
 1      | 4 (Son3d(Son2+0)Base)
vbi:       class  offset o.vbptr  o.vbte fVtorDisp
            Base       8       0       4 0

```
***
<br> 

而如果不使用虚继承：
```cpp
...
class Son1 : public Base {};
class Son2 : public Base {};
class Son3 : public Son1, public Son2 {};
...
```
类结构的分析结果：
```
class Son3      size(8):
        +---
 0      | +--- (base class Son1)
 0      | | +--- (base class Base)
 0      | | | m_A
        | | +---
        | +---
 4      | +--- (base class Son2)
 4      | | +--- (base class Base)
 4      | | | m_A
        | | +---
        | +---
        +---

```