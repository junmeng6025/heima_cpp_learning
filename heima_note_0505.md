# 5.5 运算符重载 (Overload)
对已有的运算符重新定义，赋予其另一种功能，以适应不同的数据类型  

对于内置的数据类型，例如 int、double，C++编译器知道如何做运算；但对于自定义类型的数据，例如类、结构体，编译器并不知道运算符该如何处理数据。

> ### Overload vs. Override
> - **Overload（重载）** 指的是在同一个作用域中定义多个函数，这些函数具有相同的名称但是参数列表不同，以此实现函数的重载。重载可以发生在成员函数之间，也可以发生在成员函数和非成员函数之间。当程序调用一个重载函数时，编译器会根据函数名和传递给函数的参数数量和类型来确定应该调用哪个函数。
> 
> - **Override（覆盖）** 指的是派生类中重新定义了基类中的虚函数。当派生类重新定义一个基类中的虚函数时，必须使用 override 关键字来确保该函数与基类中的虚函数具有相同的函数签名（即相同的函数名、参数列表和返回类型）。如果派生类中的函数与基类中的虚函数函数签名不同，编译器将视其为一个新函数，而不是一个覆盖函数。  
>
> 
<br>  

***

<br> 

## 5.5.1 加号运算符 `+` 重载
> 对自定义的数据类型相加  

运算符重载本质上就是声明一个函数，只不过声明方法比较特殊，把函数体的含义 “浓缩” 到了运算符身上
```cpp
class Rectangle
{
public:
	int m_A;
	int m_B;
public:
	Rectangle() {};
	Rectangle(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}

	// Define a member function
	Rectangle addRectangle(Rectangle & rect)
	{
		Rectangle sum;
		sum.m_A = this->m_A + rect.m_A;  // "this->" is optional
		sum.m_B = this->m_B + rect.m_B;
		return sum;
	}
    // Overload the operator in member func
	Rectangle operator+ (Rectangle & rect)
	{
		Rectangle sum;
		sum.m_A = this->m_A + rect.m_A;
		sum.m_B = this->m_B + rect.m_B;
		return sum;
	}
};
// Overload the operator in global func
Rectangle operator+ (Rectangle &rect1, Rectangle rect2)
{
	Rectangle sum;
	sum.m_A = rect1.m_A + rect2.m_A;
	sum.m_B = rect1.m_B + rect2.m_B;
	return sum;
}

void test()
{
	Rectangle rect1(1, 2);
	Rectangle rect2(10, 20);

    // call the custom member func
	Rectangle rect3 = rect1.addRectangle(rect2);
	cout << "rect3 members: " << rect3.m_A << "; " << rect3.m_B << endl;

    // call the overload inside class
	Rectangle rect4 = rect1.operator+(rect2);  // function call
    Rectangle rect4 = rect1 + rect2;  // simplified call
	cout << "rect4 members: " << rect4.m_A << "; " << rect4.m_B << endl;

    // call the overload out of class
    Rectangle rect5 = operator+(rect1, rect2);  // function call
    Rectangle rect5 = rect1 + rect2;  // simplified call
	cout << "rect5 members: " << rect5.m_A << "; " << rect5.m_B << endl;
}
```
需要注意的是，通过重载运算符的函数名做加法，两个函数体可以共存：因为传入参数个数不一样，相当于函数名重载；  

但是通过重载运算符直接做加法，定义重载的成员函数和全局函数必须注释掉其中一个。否则因为语句一样，编译器不知道要调用哪一个。

> **注意**
> - 对于内置的数据类型，运算符不可以重载  
> - 不要滥用运算符重载

***
<br>  


## 5.5.2 左移运算符 `<<` 重载 (取代 get() 函数)
> 输出自定义的数据类型

一般不用成员函数重载左移运算符，为了方便调用一般用全局函数

```cpp
class Rectangle
{
public:
	int m_A;
	int m_B;
public:
	Rectangle() {};
	Rectangle(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}
};

Rectangle operator+ (Rectangle &rect1, Rectangle &rect2)
{
	Rectangle sum;
	sum.m_A = rect1.m_A + rect2.m_A;
	sum.m_B = rect1.m_B + rect2.m_B;
	return sum;
}

ostream& operator<< (ostream &output, Rectangle &rect)
{
	output << rect.m_A << "; " << rect.m_B;
	return output;
}

void test()
{
	Rectangle rect1(1, 2);
	Rectangle rect2(10, 20);

    // call overload +
	Rectangle rect5 = rect1 + rect2;

	// call overload <<
	cout << "rect5 members: " << rect5 << endl;
}
```
> 注意，将重载返回类型定为 ostream&，在调用时就可以使用链式法则  

<br>  

另外，如果成员 m_A、m_B 设置为私有，可以把 << 声明为类的友元而直接做输出，取代 get()函数的功能
```cpp
class Rectangle
{
friend ostream& operator<< (ostream &output, Rectangle &rect);
private:
	int m_A;
	int m_B;
public:
	Rectangle() {};
	Rectangle(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}
};

ostream& operator<< (ostream &output, Rectangle &rect)
{
	output << rect.m_A << "; " << rect.m_B;
	return output;
}

void test()
{
	Rectangle rect2(10, 20);

	// call overload <<
	cout << "rect2 members: " << rect2 << endl;
}
```

***
<br>  

## 5.5.3 递增运算符 `++` 重载
先来了解一下内置数据类型的递增机制
```cpp
int a = 0;
cout << "a: init = 0" << endl;
cout << a << endl;  // 0
cout << ++a << endl;// 1
cout << a << endl;	// 1

int b = 0;
cout << "b: init = 0" << endl;
cout << b << endl;	// 0
cout << b++ << endl;// 0
cout << b << endl;	// 1
```
从输出对比可以看到：
- 前置自增：先自增，再调用
- 后置自增：先调用，再自增


由于需要操作类内私有成员，并且运算符也要依赖自定义变量本身，我们把重载函数定义在类内


```cpp
class MyInt
{
friend ostream& operator<< (ostream &output, MyInt myint);  // MyInt myint
private:
	int m_Num;

public:
	MyInt() { m_Num = 0; }
	MyInt(int init_num) { m_Num = init_num; }
	void set(int input) { m_Num = input; }
	int get() { return m_Num; }

	// overload `++i` ---------------------------------
	MyInt& operator++()
	{
		m_Num++;
		return *this;
	}
    // ----------------------------------------------

	// overload `i++` ---------------------------------
	MyInt operator++(int)
	{
		MyInt mytemp = *this;
		m_Num++;                			// do the operation
		return mytemp;          			// return the recorded data
	}
    // ----------------------------------------------
};

// overload `<<`
ostream& operator<< (ostream &output, MyInt myint)  // MyInt myint
{
	output << myint.m_Num;
	return output;
}

// TEST =======================================================
void test()
{
	MyInt myint1;
	cout << "myint1 =   " << myint1 << endl;	// 0
	cout << "++myint1 = " << ++myint1 << endl;	// 1
	cout << "myint1 =   " << myint1 << endl;	// 1

	MyInt myint2;
	cout << "myint2 =       " << myint2 << endl;		// 0
	cout << "++(++myint2) = " << ++(++myint2) << endl;	// 2
	cout << "myint2 =       " << myint2 << endl;		// 2

	MyInt myint3;
	cout << "myint3 =   " << myint3 << endl;	// 0
	cout << "myint3++ = " << myint3++ << endl;	// 0
	cout << "myint3 =   " << myint3 << endl;	// 1
}
```
***

代码解析：  
<br>  

### **前置自增**
```cpp
// overload ++i
MyInt& operator++()
{
    m_Num++;
    return *this;
}
```
- **返回引用:** 是为了一直对同一个数据进行操作。
- 如果返回的是值，那么 ++(++myint) 输出是2，但是myint输出是1
- 以值形式返回局部对象会调用拷贝构造函数，进行第二步递增时已经不是原来的对象了

下面是内置数据类型的连续前置自增的结果，这也是我们期望达到的效果
```cpp
int c = 0;
cout << "c: init = 0" << endl;
cout << c << endl;       // 0
cout << ++(++c) << endl; // 2
cout << c << endl;		 // 2
```

可以用这一段测试代码来对比 **返回值** 和 **返回引用** 的结果
```cpp
MyInt myint2;                                       // &:  no &:
cout << "myint2 =       " << myint2 << endl;		// 0     0
cout << "++(++myint2) = " << ++(++myint2) << endl;	// 2     2
cout << "myint2 =       " << myint2 << endl;		// 2     1
```

### **后置自增**
```cpp
// overload i++
MyInt operator++(int)
{
    MyInt mytemp = *this;
    m_Num++;
    return mytemp;
}
```
- 占位参数int: 对函数做重载，用来区分前置自增和后置自增

- 虽然逻辑上是“先返回，后自增”，但代码不能这么写。因为先写了返回的话，后面的语句都会被跳过。所以先用一个中间变量 temp 把自增前的数据保存下来，等到最后再做返回。

- 值返回而非引用返回：因为返回的 temp 是一个局部变量，函数执行结束就被释放掉了，
  - 值返回：相当于是进行了一次拷贝构造函数，从而使得生成了一个新的 MyInt 类型的数据
  - 引用返回：temp 是一个局部变量，函数执行结束后会被释放掉，导致空引用，是非法的

- 要注意的是，输出符号 `<<` 重载定义，MyInt 的传入要采用值传入；友元声明处也要一致。

<br>  


或者：后置递增重载的定义里，把 temp 改为手动开辟，存放在堆区，就可以以引用返回
```cpp
MyInt& operator++(int)
{
	MyInt* p_temp = new MyInt(*this); 	// record the data before operation
	m_Num++;                // do the operation
	return *p_temp;          // return the recorded data
}
```
> **注意:**   
输出符号 `<<` 重载 MyInt 的传入采用值传入或引用传入都可以，只要保证 *重载定义* 和 *友元声明* 两处一致即可。

***
下面是修改完成之后的完整 .cpp 脚本：
```cpp
#include <iostream>
#include <string>
using namespace std;

class MyInt
{
friend ostream& operator<< (ostream &output, MyInt& myint);  // MyInt& myint
private:
	int m_Num;

public:
	MyInt() { m_Num = 0; }
	MyInt(int init_num) { m_Num = init_num; }
	void set(int input) { m_Num = input; }
	int get() { return m_Num; }

	// overload `++i` ---------------------------------
	MyInt& operator++()
	{
		m_Num++;
		return *this;
	}
    // ----------------------------------------------

	// overload `i++` ---------------------------------
	MyInt& operator++(int)
	{
		MyInt* p_temp = new MyInt(*this); 	// record the data before operation
		m_Num++;                // do the operation
		return *p_temp;         // return the recorded data
	}
    // ----------------------------------------------
};

// overload `<<`
ostream& operator<< (ostream &output, MyInt& myint)  // MyInt& myint
{
	output << myint.m_Num;
	return output;
}


// TEST =======================================================
void test()
{
	MyInt myint1;
	cout << "myint1 =   " << myint1 << endl;	// 0
	cout << "++myint1 = " << ++myint1 << endl;	// 1
	cout << "myint1 =   " << myint1 << endl;	// 1

	MyInt myint2;
	cout << "myint2 =       " << myint2 << endl;		// 0
	cout << "++(++myint2) = " << ++(++myint2) << endl;	// 2
	cout << "myint2 =       " << myint2 << endl;		// 2

	MyInt myint3;
	cout << "myint3 =   " << myint3 << endl;	// 0
	cout << "myint3++ = " << myint3++ << endl;	// 0
	cout << "myint3 =   " << myint3 << endl;	// 1
}

// MAIN =======================================================
int main()
{
	test();
	system("pause");
	return 0;
}
```
输出：
```
myint1 =   0
++myint1 = 1
myint1 =   1
myint2 =       0
++(++myint2) = 2
myint2 =       2
myint3 =   0
myint3++ = 0
myint3 =   1
Press any key to continue . . .

```

***
<br>  

## 5.5.4 赋值运算符 `=` 重载 (取代 set() 函数)
C++编译器至少给一个类添加4个函数
1. 默认构造函数（无参，函数体为空）
2. 默认析构函数（无参，函数体为空）
3. 默认拷贝构造函数，对属性进行值拷贝
4. 赋值运算符 operator=，对属性进行值拷贝

如果类中有属性指向堆区，做赋值操作也会涉及深拷贝/浅拷贝的问题  

示例：类的成员变量是指向堆区的指针
```cpp
class Person
{
public:
	Person(int age)
	{
		m_pAge = new int(age);
	}

	int* m_pAge;
};

// TEST ==============================================================
void test()
{
	Person p1(18);
	cout << "p1's Age: " << *p1.m_pAge << endl;  // 18
	Person p2(20);
	cout << "p2's Age: " << *p2.m_pAge << endl;  // 20
	
	p2 = p1;
	cout << "After p2 = p1;\tp1's Age: " << *p1.m_pAge << endl; // 18
	cout << "After p2 = p1;\tp2's Age: " << *p2.m_pAge << endl; // 18

	*p2.m_pAge = 22;
	cout << "After *p2.m_pAge = 22;\tp2's Age: " << *p2.m_pAge << endl;
	// 22, right
	cout << "After *p2.m_pAge = 22;\tp1's Age: " << *p1.m_pAge << endl;
	// 22, which suppossed to be 18
}
```
可以看到，赋值操作之后，p2 和 p1 的成员变量指向同一块内存空间，此后对其一的改动都将“粘连”给另一方，这不是我们所期待的。  

### **内存泄漏**

更严重的问题是，当我们再写一个析构函数去释放这块空间时，会导致内存泄漏

```cpp
class Person
{
public:
	Person(int age)
	{
		m_pAge = new int(age);
	}

	~Person()
	{
		if (m_pAge != NULL)
		{
			delete m_pAge;
			m_pAge = NULL;
		}
	}

	int* m_pAge;
};

void test()
{
	Person p1(18);
	cout << "p1's Age: " << *p1.m_pAge << endl;  // 18
	Person p2(20);
	cout << "p2's Age: " << *p2.m_pAge << endl;  // 20
	
	p2 = p1; // default `=`: shallow copy
	cout << "After p2 = p1;\tp1's Age: " << *p1.m_pAge << endl; // 18
	cout << "After p2 = p1;\tp2's Age: " << *p2.m_pAge << endl; // 18

	*p2.m_pAge = 22;
	cout << "After *p2.m_pAge = 22;\tp2's Age: " << *p2.m_pAge << endl;
	// 22, right
	cout << "After *p2.m_pAge = 22;\tp1's Age: " << *p1.m_pAge << endl;
	// 22, which suppossed to be 18
}
```
系统默认赋值号 `=` ：浅拷贝  

p2 成员直接拷贝自 p1，因为此处成员变量为指针，则两者指向了同一块堆区内存；程序结束，对 p1、p2 运行析构函数，导致这块内存被重复释放，引发错误。  

> 解决方案：  
> 将赋值号重载为深拷贝方式：p2 成员变量开辟新的内存空间，把p1成员指针的内容写入

```cpp
class Person
{
public:
	Person(int age)
	{
		m_pAge = new int(age);
	}

	~Person()
	{
		if (m_pAge != NULL)
		{
			delete m_pAge;
			m_pAge = NULL;
		}
	}

	void operator= (Person &p)
	{
		// if not NULL: release
		if (m_pAge != NULL)
		{
			delete m_pAge;
			m_pAge = NULL;
		}
		// apply another memory and write the value from outside
		m_pAge = new int(*p.m_pAge);
	}

	int* m_pAge;
};

void test()
{
	Person p1(18);
	cout << "p1's Age: " << *p1.m_pAge << endl;  // 18
	Person p2(20);
	cout << "p2's Age: " << *p2.m_pAge << endl;  // 20
	
	p2 = p1; // overloaded `=` : deep copy
	cout << "After p2 = p1;\tp1's Age: " << *p1.m_pAge << endl; // 18
	cout << "After p2 = p1;\tp2's Age: " << *p2.m_pAge << endl; // 18

	*p2.m_pAge = 22;
	cout << "After *p2.m_pAge = 22;\tp2's Age: " << *p2.m_pAge << endl;
	// 22, right
	cout << "After *p2.m_pAge = 22;\tp1's Age: " << *p1.m_pAge << endl;
	// 18, right
}
```

输出
```
p1's Age: 18
p2's Age: 20
After p2 = p1;  p1's Age: 18
After p2 = p1;  p2's Age: 18
After *p2.m_pAge = 22;  p2's Age: 22
After *p2.m_pAge = 22;  p1's Age: 18
Press any key to continue . . .
```
***
### 连续赋值

现在浅拷贝的问题已经解决，但还存在一个细节问题是，这个重载的赋值不能做连续赋值。  

默认的赋值号是可以对内置数据格式做连续赋值的（链式）：
```cpp
int a = 10;
int b = 20;
int c = 30;

c = b = a;

cout << "a = " << a << endl;  // 10
cout << "b = " << b << endl;  // 10
cout << "c = " << c << endl;  // 10
```
而我们新定义的赋值号，返回类型为 void，所以为了可以实现连续赋值，需要进一步修改：
```cpp
Person& operator= (Person &p)
{
	// if not NULL: release
	if (m_pAge != NULL)
	{
		delete m_pAge;
		m_pAge = NULL;
	}
	// apply another memory and write the value from outside
	m_pAge = new int(*p.m_pAge);

	return *this;
}
```
> **注意**：  
这里不能反回值。返回值也会调用一次拷贝构造，然后再返回值再拷贝，所以无限拷贝死循环！  
>
>拷贝构造函数默认为浅拷贝，如果我们自己写一个深拷贝，待会儿析构又要重复释放堆区内容引发异常

***

下面是修改完成之后的完整 .cpp 脚本：

```cpp
#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
	Person(int age)
	{
		m_pAge = new int(age);
	}

	~Person()
	{
		if (m_pAge != NULL)
		{
			delete m_pAge;
			m_pAge = NULL;
		}
	}

	Person& operator= (Person &p)
	{
		if (m_pAge != NULL)
		{
			delete m_pAge;
			m_pAge = NULL;
		}

		m_pAge = new int(*p.m_pAge);
		return *this;
	}

	int* m_pAge;
};

// TEST ==============================================================
void test()  // ------------------------------------------------------
{
	Person p1(18);
	cout << "p1's Age: " << *p1.m_pAge << endl;  // 18
	Person p2(20);
	cout << "p2's Age: " << *p2.m_pAge << endl;  // 20
	
	p2 = p1; // overloaded `=` : deep copy
	cout << "After p2 = p1;\tp1's Age: " << *p1.m_pAge << endl; // 18
	cout << "After p2 = p1;\tp2's Age: " << *p2.m_pAge << endl; // 18

	*p2.m_pAge = 22;
	cout << "After *p2.m_pAge = 22;\tp2's Age: " << *p2.m_pAge << endl;
	// 22, right
	cout << "After *p2.m_pAge = 22;\tp1's Age: " << *p1.m_pAge << endl;
	// 18, right
}

void test02()  // ---------------------------------------------------
{
	Person p1(18);
	Person p2(20);
	Person p3(22);

	p3 = p2 = p1;

	cout << "p1 Age = " << *p1.m_pAge << ", saved at " << p1.m_pAge << endl;  // 18
	cout << "p2 Age = " << *p2.m_pAge << ", saved at " << p2.m_pAge << endl;  // 18
	cout << "p3 Age = " << *p3.m_pAge << ", saved at " << p3.m_pAge << endl;  // 18
}

// MAIN ==============================================================
int main()
{
	// test();
	test02();
	system("pause");
	return 0;
}
```

输出：
```
p1 Age = 18, saved at 008F67E8
p2 Age = 18, saved at 008F6818
p3 Age = 18, saved at 008FECB8
Press any key to continue . . .
```

## 5.5.5 关系运算符 `==`、`!=`、`>`、`<` 重载

> 作用：让两个自定义类型的对象进行对比操作
```cpp
class Person
{
public:
	string m_Name;
	int m_Age;
public:
	Person(string name, int age)
	{
		m_Name = name;
		m_Age = age;
	}

	bool operator== (Person &p)
	{
		if (m_Name == p.m_Name && m_Age == p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!= (Person &p)
	{
		if (m_Name != p.m_Name || m_Age != p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator> (Person &p)
	{
		if (m_Age > p.m_Age)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator< (Person &p)
	{
		if (m_Age > p.m_Age)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
};
```
> 注意： 
> ```cpp
> if (m_Name == p.m_Name && m_Age == p.m_Age)
> ```
> 等效于
> ```cpp
> if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
> ```
> this是默认的，没写系统也会加


测试代码
```cpp
void test()
{
	Person p1("Tom", 12);
	Person p2("Tom", 12);
	Person p3("Jerry", 12);
	Person p4("Dog", 15);

	// test ==
	if (p1 == p2)
	{
		cout << "p1 == p2" << endl;
	}
	else
	{
		cout << "p1 != p2" << endl;
	}
	
	// test !=
	if (p2 != p3)
	{
		cout << "p2 != p3" << endl;
	}
	else
	{
		cout << "p2 == p3" << endl;
	}

	// test >
	if (p4 > p3)
	{
		cout << "p4 > p3" << endl;
	}
}
```

## 5.5.6 函数调用运算符 `()` 重载
- 由于重载后使用的方式非常像函数调用，也称为 **仿函数**
- 仿函数没有固定写法，很灵活。在STL里会很常用

例1：实现打印功能的仿函数
```cpp
#include <iostream>
#include <string>
using namespace std;

// =============================================
class MyPrint
{
public:
	void operator()(string msg)
	{
		cout << msg << endl;
	}
};

// =============================================
void test()
{
	MyPrint myPrint;
	myPrint("hello world");
}

// =============================================
int main()
{
	test();
	system("pause");
	return 0;
}
```

例2：实现加法功能的仿函数
```cpp
// =============================================
class MyAdd
{
public:
	int operator()(int num1, int num2)
	{
		return num1 + num2;
	}
};

// =============================================
void test()
{
	MyAdd myAdd;
	int sum = myAdd(2, 3);
	cout << "the sum is: " << sum << endl;
}
```

匿名函数对象：省去实例化的步骤，直接使用类名调用仿函数
```cpp
void test()
{
	// MyAdd myAdd;
	// int sum = myAdd(2, 3);
	cout << "the sum is: " << MyAdd()(2, 3) << endl;
}
```
这样，语句执行完之后匿名对象会立刻被释放，节约内存空间