# Part 5 类和对象
- C++面向对象的三大特性：
  - 封装
  - 继承
  - 多态
- C++认为万事万物皆为对象，对象上有其属性（参数）和行为（函数），称为 “成员”
  - 属性：成员属性 成员变量
  - 行为：成员函数 成员方法

# 5.1 封装
## 1.1 封装的意义
- 将对象的属性和行为作为一个整体
- 将属性和行为加以权限控制

### **将对象的成员（属性和行为）作为一个整体**
示例：定义一个类并实例化一个对象
> 一般规定，类名称首字母大写；  
> 而实例化对象属于变量，首字母小写
```cpp
const double PI = 3.1415926;

class Circle  // 定义一个类
{
public: // 权限

    // 属性
    int m_r;

    // 行为
    double calcCircum()
    {
        return 2 * PI * m_r;
    }
};

int main()
{
    Circle cl;  // 通过类，实例化一个对象
    cl.m_r = 8;  // 给对象的属性赋值
    cout << "circum is: " << cl.calcCircum() << endl;  // 调用对象的行为
}
```
### **将属性和行为加以权限控制**
类在设计时，可以把属性和行为放在不同的权限下，加以管理
- public &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;公共：类内可以读写 $\sqrt{}$； 类外可以读写$\sqrt{}$
- protected &nbsp;保护：类内可以读写 $\sqrt{}$； 类外不可读写  $\times$； 子类可以访问 $\sqrt{}$
- private &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;私有：类内可以读写 $\sqrt{}$； 类外不可读写 $\times$； 子类不能访问 $\times$

```cpp
// 类内部 ========================
class Person
{
// 成员变量 -----------------------
public:
    string m_Name;

protected:
    string m_Car;

private:
    int m_BankPIN;

// 成员函数 -----------------------
public:
    // 公共-类内写
    void initPerson()
    {
        m_Name = "Someone";
        m_Car = "someCar";
        m_BankPIN = 000000;
    }

    void setPerson(string name, string car, int pin)
    {
        m_Name = name;
        m_Car = car;
        m_BankPIN = pin;
    }
    // 公共-类内读
    void prtAllInfo()  
    {
        cout << "Name: " << p1.m_Name << endl;
        cout << "Car: " << p1.m_Car << endl;
        cout << "BankPIN: " << p1.m_BankPIN << endl;
    }

private:
    // 私有-类内读
    void prtPrivate()
    {
        cout << "Car: " << p1.m_Car << endl;
        cout << "BankPIN: " << p1.m_BankPIN << endl;
    }
};

// 主函数， 类外部 =================
int main()
{
    Person p1;
    p1.initPerson(); // 类外访问公共成员函数

    // 类外访问成员属性 ------------------------------------
    // 类外写
    p1.m_Name = "Mike";     // PASS
    p1.m_Car = "Benz";      // ERROR
    p1.m_BankPIN = 111222;  // ERROR

    // 类外读
    cout << "Name: " << p1.m_Name << endl; // >> Name: Mike
        // PASS：公共属性
    cout << "Car: " << p1.m_Car << endl;
        // ERROR：保护属性
    cout << "BankPIN: " << p1.m_BankPIN << endl;
        // ERROR：私有属性

    // 类外访问成员函数 ------------------------------------
    p1.prtPrivate(); // ERROR 私有-类内读
    p1.prtAllInfo(); // PASS  公共-类内读
        // >>
        // Name: Mike       ——> Changed
        // Car: someCar     ——> Unchanged
        // BankPIN: 000000  ——> Unchanged
    p1.setPerson("Hans", "Porsche", 123456); // 公共-类内写
    p1.prtAllInfo(); // 公共-类内读
        // >>
        // Name: Hans       ——> Changed
        // Car: Porsche     ——> Changed
        // BankPIN: 123456  ——> Changed
}
```

## 1.2 struct 和 class 的区别
C++中struct和class唯一的区别在于：默认的访问权限不同
- struct &nbsp;默认权限为公共
- class &nbsp;&nbsp;默认权限为私有

```cpp
class C1
{
    int m_class;  // 默认权限是私有
};

struct S1
{
    int m_struct; // 默认权限是公共
};

int main()
{
    C1 c1;
    c1.m_class = 10; // ERROR

    S1 s1;
    s1.m_struct = 10; // PASS
}
```

## 1.3 成员属性设为私有
封装的精髓在于隔绝与外部的默认连接，从而保护内部数据。  

对于来自外部的读/写需求，需要通过公共成员函数访问类的内部，使得对内部的读、写变为一种有意识的行为。

作用：
- $+$ 可以自己控制读写操作，防止被bug误修改
- $+$ 对于写权限，我们可以检测数据的有效性

```cpp
// 定义类 =======================================
class Person
{
private:
    string m_Name;
    int m_Age;

public:
    // 读名字
    string getName()
    {
        return m_Name;
    }
    // 写名字
    void setName(string name)
    {
        m_Name = name;
    }

    // 读年龄
    int getAge()
    {
        return m_Age;
    }
    // 写年龄
    void setAge(int age)
    {
        // 判断数据有效性
        if(age < 0 ||  age > 150)
        {   
            cout << "unreasonable input" << endl;
            return;
        }
        m_Age = age;
    }
};

// 主函数 =======================================
int main()
{
    Person p1;

    // 直接访问对象属性 X 
    p1.m_Name = "MJ";                    // ERROR
    cout << "Name: " << p1.Name << endl; // ERROR
    p1.m_Age = 26;                       // ERROR
    cout << "Age: " << p1.m_Age << endl; // ERROR

    // 通过成员函数访问私有属性
    p1.setName("MJ");                         // PASS
    cout << "Name: " << p1.getName() << endl; // PASS
        // >> Name: MJ
    p1.setAge(26);                            // PASS
    cout << "Age: " << p1.getAge() << endl;   // PASS
        // >> Age: 26
}
```

### **set() 和 get() 函数：外部到类内的接口**

**set()函数**
- 返回类型：空
- 输入参数：类型和成员属性一致
  
**get()函数**
- 返回类型：和成员属性一致
- 输入参数：空

***

## *1.4 封装案例*
### 1.4.1 立方体类
- 设计立方体类
- 求出体积和表面积
- 分别用全局函数和成员函数判断两个立方体实例是否相等

类外全局函数：
- **需要两个立方体作为输入**：两个立方体实例之间的比较
  
类内成员函数：
- **只要一个立方体作为输入**：当前立方体实例与另一个来自外部的立方体作比较

```cpp
#include <iostream>
#include <string>

using namespace std;

class Cube
{
private:
	int m_L;
	int m_W;
	int m_H;

public:
	void set_LWH(int l, int w, int h)
	{
		m_L = l;
		m_W = w;
		m_H = h;
	}

	int get_L()
	{
		return m_L;
	}

	int get_W()
	{
		return m_W;
	}

	int get_H()
	{
		return m_H;
	}

	int calc_Volume()
	{
		return m_L * m_W * m_H;
	}

	int calc_Surface()
	{
		return 2 * (m_L*m_W + m_W * m_H + m_H * m_L);
	}

	// Member func to judge if equal to ANOTHER cube
	bool isSameExCube(Cube &c)
	{
		if (m_L == c.get_L() && m_W == c.get_W() && m_H == c.get_H())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

// Global func to judge if two cubes are equal
bool isCubeSame(Cube &c1, Cube &c2)
{
	if (c1.get_L() == c2.get_L() && c1.get_W() == c2.get_W() && c1.get_H() == c2.get_H())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void prtComparison(bool ret)
{
	if (ret == true)
	{
		cout << "Cubes are same" << endl;
	}
	else
	{
		cout << "Cubes are different." << endl;
	}
}

int main()
{
	Cube c1, c2;
	c1.set_LWH(10, 20, 30);
	c2.set_LWH(5, 10, 15);

	// use global func
	bool ret_glb = isCubeSame(c1, c2);
	prtComparison(ret_glb);

	// use member func
	bool ret_cls1 = c1.isSameExCube(c2);
	prtComparison(ret_cls1);

	bool ret_cls2 = c2.isSameExCube(c1);
	prtComparison(ret_cls1);
}
```

### 1.4.2 点和圆的关系
设计一个圆类和一个点类，判断点和圆的位置关系  
其中，圆类的圆心成员是点类 -> 在类中可以使用另一个类作为成员  
  
分文件编写:  
**point.h**
```cpp
#pragma once
#include <iostream>

using namespace std;

class Point
{
private:
	int m_x;
	int m_y;
public:
	void setXY(int x, int y);
	int getX();
	int getY();
};
```
**point.cpp**
```cpp
#include "point.h"

void Point::setXY(int x, int y)
{
    m_x = x;
    m_y = y;
}

int Point::getX()
{
    return m_x;
}

int Point::getY()
{
    return m_y;
}
```
**circle.h**
```cpp
#pragma once
#include <iostream>
using namespace std;

class Circle
{
private:
	Point m_Center;
	double m_r;
public:
	void setR(int r);
	double getR();
	void setCenter(Point center);
	Point getCenter();
};
```
**circle.cpp**
```cpp
#include "circle.h"

void Circle::setR(int r)
{
    m_r = r;
}

double Circle::getR()
{
    return m_r;
}

void Circle::setCenter(Point center)
{
    m_Center = center;
}

Point Circle::getCenter()
{
    return m_Center;
}
```
**main.cpp**
```cpp
#include <math.h>
#include <string>
#include "point.h"
#include "circle.h"

int isInCircle(Circle &c, Point &p)
{
	double dist_pow = pow((c.getCenter().getX() - p.getX()), 2)
		+ pow((c.getCenter().getY() - p.getY()), 2);

	if (dist_pow == pow(c.getR(), 2))
	{
		return 0;
	}
	else if (dist_pow > pow(c.getR(), 2))
	{
		return 1;
	}
	else if (dist_pow < pow(c.getR(), 2))
	{
		return -1;
	}
	else
	{
	}
}

void prtInCircle(int diff)
{
	switch (diff)
	{
	case 0:
		cout << "Point is on the circle" << endl;
		break;
	case 1:
		cout << "Point is out of the circle" << endl;
		break;
	case -1:
		cout << "Point is within the circle" << endl;
		break;
	default:
		break;
	}
}

int main()
{
	Point p;
	p.setXY(10, 10);

	Point center;
	center.setXY(10, 0);

	Circle cir;
	cir.setCenter(center);
	cir.setR(10);

	prtInCircle(isInCircle(cir, p));
}
```

***


## 3.1 成员变量和成员函数分开存储
## 3.2 this 指针的用途
## 3.3 空指针访问成员函数
## 3.4 const 修饰成员函数
# 4. 友元
# 5. 运算符重载
# 6. 继承
# 7. 多态