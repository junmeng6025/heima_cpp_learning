# 5.4 友元
以日常生活举例，你的家里有客厅（public），有卧室（private）。  

像客厅这种公共空间，所有到访的客人都可以进去；但卧室属于私密空间，一般只有我们自己可以进去。不过有时候我们也允许好闺蜜、好基友进我们的卧室坐坐  

在C++程序里，有些类内的私有属性也想开放给类外一些特殊的函数或类进行访问，它们就是 **友元**。  

> **友元**：让类内的私有属性可以被指定的外部函数或其他类访问

关键字：`friend`  

友元有三种实现方法
- 全局函数作为友元
- 类作为友元
- 成员函数作为友元

## 5.4.1 全局函数作为友元
在类内声明友元函数：  
```cpp
friend void goodFriend(Building *building);
```
eg.
```cpp
// Class definition =====================================================
class Building
{
friend void goodFriend(Building *building);  // Declare friend function
public:
	Building()
	{
		m_LivingRoom = "Living room";
		m_BedRoom = "Bedroom";
	}

public:
	string m_LivingRoom;

private:
	string m_BedRoom;
};

// Global functions =====================================================
void guest(Building *building) // func guest ----------------------------
{
	cout << "Func guest() is visiting: " << building->m_LivingRoom << endl;
	// cout << "Func guest() is visiting: " << building->m_BedRoom << endl;
    /* ERR:
       member Building::m_BedRoom is inaccessible
    */
    // because guest() is not `friend` of the class Building
}

void goodFriend(Building *building) // func friend ---------------------
{
	cout << "Func goodFriend() is visiting: " << building->m_LivingRoom << endl;
	cout << "Func goodFriend() is visiting: " << building->m_BedRoom << endl;
}

// Test function ========================================================
void test()
{
	Building myHome;
	guest(& myHome);
	goodFriend(& myHome);
}

```
输出
```
Func guest() is visiting: Living room
Func goodFriend() is visiting: Living room
Func goodFriend() is visiting: Bedroom
```

## 5.4.2 友元类
在类内声明友元类：  
```cpp
friend friend class GoodFriend;
```
eg.
```cpp
// Class definition =====================================================
class Building // class Building ----------------------------------------
{
friend class GoodFriend;  // Declare friend class
public:
	Building()
	{
		m_LivingRoom = "Living room";
		m_BedRoom = "Bedroom";
	}

public:
	string m_LivingRoom;

private:
	string m_BedRoom;
};

class GoodFriend // class Friend ---------------------------------------
{
public:
	Building * m_pBuilding;

public:
	GoodFriend();
	void visit();
};
// Define member function outside of the class
GoodFriend::GoodFriend()
{
	m_pBuilding = new Building;
}
void GoodFriend::visit()
{
	cout << "Class GoodFriend is visiting: " << m_pBuilding->m_LivingRoom << endl;
	cout << "Class GoodFriend is visiting: " << m_pBuilding->m_BedRoom << endl;
}

class Guest // class Guest ----------------------------------------------
{
public:
	Building * m_pBuilding;

public:
	Guest();
	void visit();
	
};

Guest::Guest()
{ 
    m_pBuilding = new Building; 
}
void Guest::visit()
{ 
    cout << "Class Guest is visiting: " << m_pBuilding->m_LivingRoom << endl; 
    // cout << "Class Guest is visiting: " << m_pBuilding->m_BedRoom << endl;
    /*ERR
        member Building::m_BedRoom is inaccessible
    */
}

// Test function ========================================================
void test()
{
	Guest myGuest;
    myGuest.visit();
    GoodFriend myFirend;
    myFirend.visit();

}
```
输出
```
Class Guest is visiting: Living room
Class GoodFriend is visiting: Living room
Class GoodFriend is visiting: Bedroom
```

## 5.4.3 成员函数作为友元
在类内声明友元成员函数：  
```cpp
friend void Visitor::visit_prv();
```
eg.

```cpp
// Class definition =====================================================
class Building;
class Visitor // class Visitor Declaration ------------------------------
{
public:
	Building * m_pBuilding;

public:
	Visitor();
	void visit_prv();
	void visit_pub();
};

class Building // class Building Declaration ----------------------------
{
friend void Visitor::visit_prv();  // Declare friend member func
public:
	Building();

public:
	string m_LivingRoom;

private:
	string m_BedRoom;
};

// Class Building define ------------------------------------------------
Building::Building()
{
	m_LivingRoom = "Living room";
	m_BedRoom = "Bedroom";
}

// Class Visitor define -------------------------------------------------
Visitor::Visitor()
{
	m_pBuilding = new Building;
}

void Visitor::visit_prv()
{
	cout << "Class Visitor is visiting: " << m_pBuilding->m_LivingRoom << endl;
	cout << "Class Visitor is visiting: " << m_pBuilding->m_BedRoom << endl;
}

void Visitor::visit_pub()
{
	cout << "Class Visitor is visiting: " << m_pBuilding->m_LivingRoom << endl;
}

// Test function ========================================================
void test()
{
	Visitor myVisitor;
    cout << "public visit: " << endl;
	myVisitor.visit_pub();
    cout << "private visit: " << endl;
	myVisitor.visit_prv();
}
```
输出
```
public visit:
Class Visitor is visiting: Living room
private visit:
Class Visitor is visiting: Living room
Class Visitor is visiting: Bedroom
```
> **注意**
> - Visitor 类要定义在 Building 前
> - visit() 要在类外面定义，在 Building 类之后

如果成员函数都写为类内定义：
- 如果 Building 类先定义， Visitor 类前置声明
  ```
  E0265 - member "Building::m_BedRoom" is inaccessible
  C2027 - use of undefined type 'Visitor'
  C2248 - 'Building::m_BedRoom': cannot access private member declared in class 'Building'
  ```
- 如果 Visitor 类先定义， Building 类前置声明
  ```
  E0265 - member "Building::m_BedRoom" is inaccessible
  C2027 - use of undefined type 'Building'
  ```

