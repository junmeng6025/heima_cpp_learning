# 5.3 C++对象模型和 this 指针

## 5.3.1 成员变量和成员函数分开存储
在C++中，类内的成员变量和成员函数分开存储。 

静态的成员函数和变量、非静态成员函数都不属于对象，**只有非静态成员变量才归属具体的实例化对象**。  

```cpp
// blank class
class Person0
{

};
// class with 1 unstatic attribute
class Person1
{
	int m_A;
};
// class with 1 unstatic and 1 static attribute
class Person2
{
	int m_A;
	static int m_B;
};
int Person2::m_B = 0;

// class with 1 unstatic and 1 static attribute, 1 unstatic function
class Person3
{
	int m_A;
	static int m_B;
	void func() {}
};

// class with 1 unstatic and 1 static attribute, 1 unstatic and 1 static function
class Person4
{
	int m_A;
	static int m_B;
	void func() {}
	static void func_s() {}
};

void test()
{
	Person0 p0;
	cout << "size of p0: blank >> " << sizeof(p0) << endl;  //1

	Person1 p1;
	cout << "size of p1: 1 int >> " << sizeof(p1) << endl;  //4

	Person2 p2;
	cout << "size of p2: 1 int, 1 static int >> " << sizeof(p2) << endl; //4

	Person3 p3;
	cout << "size of p3: p2 + 1 func >> " << sizeof(p3) << endl; //4

	Person4 p4;
	cout << "size of p4: p3 + 1 static func >> " << sizeof(p4) << endl; //4
}
```
- 一个空的对象会占用 1 字节的内存，用以区分存储位置；
- 包含一个非静态 int 型成员变量的对象就占用一个 int 所需的内存，4字节。
- 包含一个非静态 int 和一个静态 int 的对象也占用4字节内存，因为静态成员变量不归属于该对象。
- 类似地，包含其他独立成员时：静态的成员函数或变量、非静态的成员函数，都不会进入对象的空间

## 5.3.2 this指针
C++中成员变量和成员函数分开存储。  

每个非静态成员函数只会生成一份函数实例，同一类实例化出来的多个对象会复用同一块代码。那么这一块代码是如何区分正在被哪个对象调用的呢？  

C++提供了特殊的对象指针：`this` 指针，**指向被调用成员函数所属的对象**。
- this指针隐含在每一个非静态成员函数内，指向当前的对象
- this指针不需要定义，可以直接使用

this指针用途：
- 解决名称冲突：当形参和成员变量同名时，可用this指针区分
- 返回对象本身：在类的非静态成员函数中返回对象本身，可使用：return *this;

1）解决名称冲突
```cpp
class Person
{
public:
    int age

    Person(int age)
    {
        this->age = age;
    }
};
```
相当于：
```cpp
class Person
{
public:
    int m_age

    Person(int age)
    {
        m_age = age;
    }
};
```
2）返回对象本身
```cpp
class Person
{
public:
    int m_age;

    Person(int age)
    {
        m_age = age;
    }

    Person& AddAge(Person &p)  // return type same as input
    {
        this->m_age += p.m_age;
        return *this;
    }
};

void test()
{
    Person p1(10);
    Person p2(10);

    p2.AddAge(p1).AddAge(p1).AddAge(p1);  // chain rule
    cout << "p2 age = " << p2.m_age << endl;  // 40
}

```
注意：如果返回的不是 `Person&` 而是 `Person`，
```cpp
class Person
{
public:
    int m_age;

    Person(int age)
    {
        m_age = age;
    }

    Person AddAge(Person &p)  // return type without &
    {
        this->m_age += p.m_age;
        return *this;  // return a copy p2'
    }
};

void test()
{
    Person p1(10);
    Person p2(10);

    p2.AddAge(p1).AddAge(p1).AddAge(p1);  // p2', p2'', p2'''
    cout << "p2 age = " << p2.m_age << endl;  // 20
}

```
只加了一次。这是因为p2的 m_age 加完之后，返回的其实是p2的一份拷贝。p2的成员m_age确实被改写了，但是传出并参与下一次AddAge()的是返回的副本，而非p2本身了。

## 5.3.3 空指针访问成员函数
C++空指针可以调用成员函数，但要注意有没有用到 `this` 指针。如果用到了 this 指针，需要检查一下代码的稳健性。

```cpp
class Person
{
	int m_Age;
public:
	void showClassName()
	{
		cout << "this is Person class" << endl;
	}

	void showAge()
	{
		// improve the robustness ---------------
		if (this == NULL)
		{
			return;
		}
		// --------------------------------------
		cout << "person age: " << m_Age << endl;
	}
};

void test()
{
	Person* p = NULL;
	p->showClassName(); // no use of member attr
	p->showAge();       // uses member attr: 
                        // -> can cause error, when p is nullptr
}
```
事实上，当成员函数调用了成员变量，成员函数内部会隐式地使用 this 指针
```cpp
void showAge()
{
    cout << "person age: " << m_Age << endl;
    cout << "person age: " << this->m_Age << endl;
}
```

## 5.3.4 const修饰成员函数

### **常函数：**
- 成员函数**后**加 const 构成常函数
- 常函数内**不可修改成员属性**
- 成员属性声明时加上关键字 mutable 可以被常函数修改

### **常对象：**
- 声明对象**前**加 const 构成常对象
- 常对象**只能调用常函数**

像前面提到的，成员函数内会隐式地使用 this 指针。this 指针是一个**指针常量**，其指向是固定不可修改的；

### 1）常函数
```cpp
class Person
{
public:
	int m_A;
	mutable int m_B;
	// Person * const this            --> default `this` pointer, func without `const`
	// const Person * const this      --> func also with `const`,
	void modAttrB() const  
    // `const` here equiv CONST in `CONST Person * const this`
	{
		// this->m_A = 100; 
		/* ERR: 
			const Person * const this
			expression must be a modifiable Ivalue
		*/

		this->m_B = 100;  // equiv `m_B = 100;`
	}

    void modAttrA()
    {
        m_A = 200;
    }

};

void test()
{
	Person p;
    // Mod mutable attr via const func ------
	p.modAttrB();
	cout << "person m_B = " << p.m_B << endl;
    // Mod normal attr via normal func ------
    p.modAttrA();
    cout << "person m_A = " << p.m_A << endl;
}
```
没有 const 修饰的成员函数：默认的this指针只是个指针常量，即指向不可更改，但指向的内容可以改写；  

有 const 修饰的成员函数：this 变成指向常量的指针常量，即指针的指向和所指向的内容都不可更改。

### 1）常对象
```cpp
void test02()
{   
    const Person p;
    // MOD ATTRBUTE -------------------------
    p.m_B = 10;  // m_B mutable
    cout << "person m_B = " << p.m_B << endl;
    // p.m_A = 100; // ERR

    // CALL FUNC ----------------------------
    p.modAttrB();
    cout << "person m_B = " << p.m_B << endl;
    //p.modAttrA(); // ERR
}
```

常对象只能调用常函数在逻辑上是行得通的：
> 因为常函数只能修改mutable的成员变量，常对象也是；  
> 
> 修改普通变量的语句在非 const 函数里是合法的，既然常对象不可以修改普通变量，自然也不可以调用能修改普通变量的普通函数