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

**父类当中的私有属性在子类中只是被隐藏了，本质上还是被继承下去的**

## 6.4 继承中构造和析构的顺序

## 6.5 继承同名成员处理方式

## 6.6 继承同名静态成员处理方式

## 6.7 多继承语法

## 6.8 菱形继承
