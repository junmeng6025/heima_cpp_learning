# Part1 数组/函数/指针/结构体
# 5. 数组
数组是一个集合，里面存放了若干相同类型的数据元素
- 每个元素都是相同的数据类型
- 数组由连续内存位置组成

## 5.1  一维数组 （向量）

$$
\left[
\begin{matrix}
    val1 \\
	val2 \\
    val3 \\
\end{matrix}
\right]
$$
```
arr[1]
>>> val2

arr
>>> &arr[0]
```
> 一维数组默认为列向量
### 定义方式
- `数据类型 数组名 [数组长度];`
- `数据类型 数组名 [数组长度] = {val1，val2, val3, ...};`
- `数据类型 数组名 [] = {val1，val2, val3, ...};`
    
    **定义数组时，数组长度必须被初始化**
    ```cpp
    int arr[] = { 10, 20, 30, 40, 50 };
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout << arr[i] << endl;
	}
	cout << "memory occupied:\t" << sizeof(arr) << endl;
	cout << "num of elements:\t" << sizeof(arr) / sizeof(int) << endl;
	cout << "saved at address\t" << arr << endl;
    cout << "the first element:\t" << *arr << endl;
    ```
### 数组变量名：
- 访问数组占用的长度
  ```cpp
  sizeof(arr)  //数组占用内存大小
  sizeof(arr)/sizeof(int) //数组元素个数
  ```
- 访问数组在内存中的首地址
  ```cpp
  arr  //首元素地址
  *arr  //首元素，相当于 arr[0]
  
  arr = &arr[0]  //地址
  *arr = arr[0]  //值
  ```
数组名对应的内容就是数组首地址。一旦定义之后就不可以被赋值，只能读取不能改写。也就是说，**数组名是一个常量**，不是一个左值。

### array vs. vector
```cpp
// array
int arr[] = { 10, 20, 30, 40, 50 };
for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
{
    cout << arr[i] << endl;
}

//vector
#include <vector>

vector<int> vec = { 10, 20, 30, 40, 50 };
for (auto it = vec.begin(); it != vec.end(); it++)
{
    cout << *it << endl;
}
```
### 常见功能代码
1. 寻找最大值
    ```cpp
    int arr[] = {300, 350, 200, 400, 250};
	int max = 0;
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
    ```
2. 元素逆置
    ```cpp
    int arr_inv[] = {1, 2, 3, 4, 5};
	int tmp = 0;
	int sz = sizeof(arr_inv) / sizeof(int);
	int start = 0;
	int end = sz-1;
	while(start < end)
	{
		tmp = arr_inv[start];
		arr_inv[start] = arr_inv[end];
		arr_inv[end] = tmp;
		start++;
		end--;
	}
    ```
3. 冒泡排序（eg. 升序）  
   思路：逐轮排序，每一轮都把当前队列里最大的元素顶到最后
    - 比较相邻的元素。如果第一个比第二个大，那就交换位置
    - 对接下来每一对相邻元素执行这个操作。
    - 执行完毕后，第一个最大值被确定
    - 重复如上步骤，每次比较次数减1，直到不需要比较
    ```cpp
    int arr_bubble[] = { 4, 2, 8, 0, 5, 7, 1, 3, 9 };
	int temp = 0;
	int size = sizeof(arr_bubble) / sizeof(int);

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr_bubble[j] > arr_bubble[j + 1])
			{
				temp = arr_bubble[j];
				arr_bubble[j] = arr_bubble[j + 1];
				arr_bubble[j + 1] = temp;
			}
            else
            {continue;}
		}
	}
    ```

## 5.2 二维数组 (矩阵)
$$
\left[
\begin{matrix}
    val1 & val2 \\
    val3 & val4 \\
\end{matrix}
\right]
$$
```
mat[0][1]
>>> val2
```
### 定义方式
- `数据类型 数组名 [行数] [列数];`
- `数据类型 数组名 [行数] [列数] = {{val1, val2}, {val3, val4}};`
- `数据类型 数组名 [行数] [列数] = {val1，val2, val3, val4};`
- `数据类型 数组名 [] [列数] = {val1，val2, val3, val4};`

	> 注意： 多维数组定义时只可省略最高维数目，计算机可以自行推算
	> 对于二维数组（矩阵），只写行数无法准确寻址，因为所有的数据都可以在同一行

	> 一维向量默认为列向量；二维数组相当于一个以行向量为元素的列向量
	```cpp
	int mat [2][2] = 
	{
		{val1, val2},
		{val3, val4}
	};
	```

### 数组变量名
- sizeof() 返回数组占用的内存空间
- 获取数组首地址

### 访问矩阵元素
```cpp
// 数组首地址
mat					
// 数组第一行首地址
mat[0]				
&mat[0][0]
// 数组第二行首地址
mat[1] 				
&mat[1][0]
// 数组第一行第一列元素值
mat[0][0]			
```
<br>

***

# 6. 函数
- 将一段经常使用的代码封装起来，方便重复使用
- 在较大的程序中将功能分割，每个模块实现特定的功能
  
## 函数定义
- 返回值类型
- 函数名
- 参数列表
- 函数体语句
- return表达式，要与返回值类型一致
	
	```cpp
	int count_sum(int num1, int num2)
	{	
		int sum = num1 + num2;
		return sum;
	}
	```

	> 有些函数只执行操作，不返回结果，那么返回类型为空，void，函数体结尾也不需要有return语句。

## main 函数
系统默认的程序入口

## 函数的调用
- 实参：函数执行时传入的参数，有具体的值
- 形参：函数定义时用来抽象表达的参数，没有具体的值
- 值传递之后，形参进入函数体参与运算，实参的值不变。这个过程，形参相当于实参的“副本”

## 函数常见类型
- **无参无返**
- **有参无返**：类当中的 set函数
  ```cpp
  void set_attr (int val)
  {
	cls.attr = val;
  }
  ```
- **无参有返**：类当中的 get函数
  ```cpp
  int get_attr ()
  {
	return cls.attr;
  }
  ```
- **有参有返**

## 函数声明
- declaration 声明：提前告知编译器函数存在
- definition&ensp;&ensp;定义：函数的具体代码内容

## 函数分文件编写
步骤：
- 创建 `.h` 头文件 &ensp;&ensp;——> 写函数的声明
- 创建 `.cpp` 源文件 ——> 写函数的定义
- 建立链接：在 `.cpp` 文件里包含相应的头文件，表示二者是关联的
  
  ```cpp
  #include "headerfile.h"
  ```
  > 用到的标准库 可以包含在头文件，也可以在源文件

- 最后在主函数只需要包含这个头文件，相关的函数定义、依赖包都可以关联进来

<br>  

***

# 7. 指针 
通过指针间接访问内存
- 内存编号从0开始，一般用十六进制数字表示
- 可以利用一个指针保存其他变量的地址

指针占用的内存空间在32位系统（x86）是4字节，在64位系统（x64）是8字节

### 指针定义
`数据类型 * 指针名称；`
```cpp
int a = 10;
int * pa;	// 声明一个指针，其指向int型数据
pa = &a;	// 给指针赋值，赋int变量a的地址
```
### 指针使用
```cpp
pa		// 获取a的地址
*pa  	// 通过pa访问a
```

### 空指针 nullptr
指针变量指向内存中编号为0的空间
  - 用于初始化指针变量
  - 空指针指不可访问。0~255内存编号是系统占用的，不允许用户访问

### 野指针
指针变量指向非法空间。要避免
```cpp
int * p = (int *)0x1100;
```
直接给指针变量赋十六进制的地址编号。因为地址并非申请所得，所以对其没有读写权限

空指针和野指针都不是用户申请的，因此不要访问。

## 7.1 const修饰指针
- const修饰指针 ——> 常量指针
- const修饰常量 ——> 指针常量
- const既修饰指针又修饰常量

### 1）const修饰指针 ——> 常量指针

> $\sqrt{}$ 修改指针指向的内存空间   
> X &ensp;修改指针指向的值   

```cpp
int a = 10;
int b = 10;

const int * pa = &a;  // 指针指向的是const

*p = 20;  // ERROR
p = &b;   // OK
```

### 2）const修饰常量 ——> 指针常量
> X &ensp;修改指针指向的内存空间  
> $\sqrt{}$ 修改指针指向的值

```cpp
int * const pa = &a;  // 指针是const

*p = 20;  // OK
p = &b;   // ERROR
```

### 3）const既修饰指针又修饰常量
> X &ensp;修改指针指向的内存空间  
> X &ensp;修改指针指向的值

```cpp
const int * const pa = &a;  // 指针是const，指针指向的也是const

*p = 20;  // OK
p = &b;   // ERROR
```

## 7.2 指针和数组
利用指针访问数组中的元素

```cpp
int arr[] = {1, 2, 3, 4, 5, 6};
int * p = arr; 

*p   // arr[0]
p++  // p后移一个内存空间。即p的值+4，向后移动四个字节
     // 如果是double型，则一个内存空间是8字节
*p   // arr[1]
```

## 7.3 **指针和函数**
指针作为函数形参，可以修改实参的值
### 值传递
```cpp
void swap(int num1, int num2)
{
	cout << "input num1 = " << num1 << endl; // 10
	cout << "input num2 = " << num2 << endl; // 20

	int temp = num1;
	num1 = num2;
	num2 = temp;

	cout << "swaped num1 = " << num1 << endl; // 20
	cout << "swaped num2 = " << num2 << endl; // 10
}

int main()
{
	int a = 10;
	int b = 20;

	cout << "before swap, a = " << a << endl; // 10
	cout << "before swap, b = " << b << endl; // 20

	swap(a, b);

	cout << "after swap, a = " << a << endl; // 10
	cout << "after swap, b = " << b << endl; // 20

	return 0;
}
```
### 地址传递
```cpp
void swap_p(int * pnum1, int * pnum2)
{
	cout << "input num1 = " << *pnum1 << endl; // 10
	cout << "input num2 = " << *pnum2 << endl; // 20

	int temp = *pnum1;
	*pnum1 = *pnum2;
	*pnum2 = temp;

	cout << "swaped num1 = " << *pnum1 << endl; // 20
	cout << "swaped num2 = " << *pnum2 << endl; // 10
}

int main()
{
	int a = 10;
	int b = 20;

	cout << "before swap, a = " << a << endl; // 10
	cout << "before swap, b = " << b << endl; // 20

	swap(&a, &b);

	cout << "after swap, a = " << a << endl; // 20
	cout << "after swap, b = " << b << endl; // 10

	return 0;
}
```
> 值传递的过程，形参相当于实参的 **副本**。函数体对形参进行的操作不会影响到实参  
> 地址传递的过程，形参相当于实参的 **链接**。函数体对形参的操作就是对实参的操作

## 7.4 指针，数组，函数
把冒泡排序封装为一个函数，对传入的整型数组做升序排序

```cpp
// bubble.h
void bubbleSort(int * arr, int len);
```

```cpp
// bubble.cpp
#include "bubble.h"

void bubbleSort(int * arr, int len)
{
	for(int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
```

```cpp
// main.cpp
#include "bubble.h"
#include <iostream>

using namespace std;
void print_arr(int * arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

int main()
{
	int arr[] = { 4, 3, 6, 9, 1, 2, 10, 8, 7, 5 };
	int sz_arr = sizeof(arr) / sizeof(arr[0]);

	cout << "array before sorting:" << endl;
	print_arr(arr, sz_arr);

	bubbleSort(arr, sz_arr);

	cout << "array after sorting:" << endl;
	print_arr(arr, sz_arr);
}
```

<br>  

***

# 8. 结构体
用户自定义的数据类型，允许用户存储不同类型的数据。类似 Python 里的字典

## 8.1 定义一个结构体
`struct 结构体名 {成员变量1; 成员变量2; ...};`  
  
定义一个 “学生” 结构体
  
```cpp
struct Student
{
	std::string name;
	int age;
	float score;
}；
```
## 8.2 创建结构体形式的变量
`结构体名 结构体变量名；`  
`结构体变量.成员变量 = xxx；`  
  
通过 “学生” 结构体实例化一个变量，记录一个学生的信息
  
```cpp
// 方法1：先声明变量，再赋值
struct Student s1;
s1.name = "MLL";
s1.age = 26;
s1.score = 1.5;

// 方法2：声明时直接赋值
struct Student s2 = {"MJ", 25, 2.7};

// 方法3：定义结构体时顺便声明一个该类型的变量
struct Student
{
	std::string name;
	int age;
	float score;
}s3；
s3.name = "MLL";
s3.age = 26;
s3.score = 1.5;
```
> 创建结构体变量时可以省略关键字 struct，但定义结构体时必须有 struct 关键字

```cpp
// 方法1：先声明变量，再赋值
Student s1;
s1.name = "MLL";
s1.age = 26;
s1.score = 1.5;
```

## 8.3 结构体数组
`结构体名 结构体数组名[] = {结构体1， 结构体2， ...}`

以结构体变量为元素的数组。例如用包含 “学生” 结构体的数组统计全班同学的信息

```cpp
Student arrStudents[] =
{
	{"L Ma", 26, 1.5},
	{"J Meng", 25, 2.7},
	{"Y Zhang", 25, 1.5}
}
```

## 8.4 结构体指针
通过指向结构体变量的指针访问结构体的成员变量  
- 通过结构体指针访问成员：使用操作符 `->`
- 通过结构体名访问成员：使用操作符 `.` 

```cpp
Student s1 = {"MJ", 25, 2.7};
s1.age = 27;     // 通过结构体变量名修改“年龄”成员

Student * pS1 = &s1;
pS1 -> age = 27; // 通过结构体指针修改“年龄”成员
```

## 8.5 结构体嵌套结构体
“老师” 的信息里有他带教的 “学生”
```cpp
// 定义 “学生” 结构体 （要先定义子结构体）
struct Student
{
	std::string name;
	int age;
	float score;
}；

// 定义 “老师” 结构体
struct Teacher
{
	std::string name;
	int age;
	std::string course;
	Student students[3];  // 嵌套的结构体 (数组长度必须初始化)
}；

// 实例化一位老师
Teacher t1;
t1.name = "Mathias";
t1.age = 30;
t1.course = "Intro Deep Learning";
t1.students = 
{
	{"MJ", 25, "2.7"},
	{"MLL", 26, "1.7"},
	{"KK", 24, "1.3"}
};
// 或者直接赋值 （可读性差）
Teacher t1 =
{
	"Mathias"，
	30，
	"Intro Deep Learning"， 
	{
		{"MJ", 25, "2.7"},
		{"MLL", 26, "1.7"},
		{"KK", 24, "1.3"}
	}
}；
```

## 8.6 结构体作为函数参数
写一个打印结构体成员变量的函数
### a）值传递
+ $+$ 形参副本不影响实参
+ $-$ 造成额外内存使用
```cpp
void prtStudent(struct Student s)
{
	cout << "\tName: " << s.name
	     << "\tAge:  " << s.age
		 << "\tScore:" << s.score
		 << endl;
}
...
Student s = {"MJ", 25, 2.7};
prtStudent(s)
```
### b）地址传递
+ $-$ 容易产生意外的修改
+ $+$ 不造成额外内存使用
```cpp
void prtStudent(struct Student * ptS)
{
	cout << "\tName: " << ptS -> name
	     << "\tAge:  " << ptS -> age
		 << "\tScore:" << ptS -> score
		 << endl;
}
...
Student s = {"MJ", 25, 2.7};
prtStudent(&s)
```

## 8.7 const 在结构体中的使用
作用：在地址传值时，防止潜在的误修改
```cpp
void prtStudent(const struct Student * ptS)
{
	cout << "\tName: " << ptS -> name
	     << "\tAge:  " << ptS -> age
		 << "\tScore:" << ptS -> score
		 << endl;
}
...
Student s = {"MJ", 25, 2.7};
prtStudent(&s)
```

## 8.8 结构体案例
### 1. 毕业设计
创建嵌套的结构体
<details>  

```cpp
// 定义学生结构体
struct Student
{
	string sID;
	int sScore;
};

// 定义老师结构体
struct Teacher
{
	string tID;
	char tTopic;
	Student tStudents[5];
};
```
```cpp
// 编写函数，给结构体数组赋值
void setMemberValue(struct Teacher tArray[], int len)
{
	for (int i = 0; i < len; i++)
	{
		tArray[i].tID = "Teacher_";
		tArray[i].tID += to_string(i);
		tArray[i].tTopic = (char)i+97; // ASCII
		for (int j = 0; j < 5; j++)
		{
			tArray[i].tStudents[j].sID = "Student_T";
			tArray[i].tStudents[j].sID += to_string(i);
			tArray[i].tStudents[j].sID += "-";
			tArray[i].tStudents[j].sID += to_string(j);

			int random = rand() % 41;  // 0~40随机数
			tArray[i].tStudents[j].sScore = 60 + random;
		}
	}
}
```
```cpp
// 编写函数，打印结构体内容
void prtScore(struct Teacher tArray[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << "TeacherID: " << tArray[i].tID 
			 << "\tTopic: " << tArray[i].tTopic
			 << endl;
		for (int j = 0; j < 5; j++)
		{
			cout << "\tStudentID: " << tArray[i].tStudents[j].sID 
				 << "\tScore: " << tArray[i].tStudents[j].sScore
				 << endl;
		}
		cout << "========================================" << endl;
	}
}
```
```cpp
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

...

// 主函数
int main()
{	
	// 由系统时钟初始化随机数种子
	srand((unsigned int)time(NULL));

	// define a Teacher array
	Teacher arrTeachers[3];
	int len_arrTeachers = sizeof(arrTeachers) / sizeof(Teacher);

	setMemberValue(arrTeachers, len_arrTeachers);
	prtScore(arrTeachers, len_arrTeachers);

	return 0;
}
```
输出：
```
TeacherID: Teacher_0    Topic: a
        StudentID: Student_T0-0 Score: 94
        StudentID: Student_T0-1 Score: 64
        StudentID: Student_T0-2 Score: 78
        StudentID: Student_T0-3 Score: 85
        StudentID: Student_T0-4 Score: 62
========================================
TeacherID: Teacher_1    Topic: b
        StudentID: Student_T1-0 Score: 100
        StudentID: Student_T1-1 Score: 81
        StudentID: Student_T1-2 Score: 94
        StudentID: Student_T1-3 Score: 64
        StudentID: Student_T1-4 Score: 82
========================================
TeacherID: Teacher_2    Topic: c
        StudentID: Student_T2-0 Score: 66
        StudentID: Student_T2-1 Score: 73
        StudentID: Student_T2-2 Score: 74
        StudentID: Student_T2-3 Score: 72
        StudentID: Student_T2-4 Score: 62
========================================
```

</details>  

### 2. 英雄
对结构体数组按照某个 attribute 的值做冒泡排序
<details>

```cpp
#include <iostream>
#include <string>

using namespace std;

struct Hero
{
	string name;
	int age;
	char sex;
};

void prtHero(struct Hero arrH[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << "Name: " << arrH[i].name
			<< "\tAge: " << arrH[i].age
			<< "\tSex: " << arrH[i].sex
			<< endl;
	}
}

void bubblesort(struct Hero arrH[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1 - i; j++)
		{
			if (arrH[j].age > arrH[j + 1].age)
			{
				struct Hero tempHero = arrH[j];
				arrH[j] = arrH[j + 1];
				arrH[j + 1] = tempHero;
			}
		}
	}
}


int main()
{
	struct Hero arrHero[5] =
	{
		{"Liu", 23, 'M'},
		{"Guan", 22, 'M'},
		{"Zhang", 20, 'M'},
		{"Zhao", 21, 'M'},
		{"Diao", 19, 'F'}
	};

	cout << "before sorting " << endl;
	prtHero(arrHero, 5);
	bubblesort(arrHero, 5);
	cout << "after sorting " << endl;
	prtHero(arrHero, 5);

	return 0;
}
```
输出
```
before sorting
Name: Liu       Age: 23 Sex: M
Name: Guan      Age: 22 Sex: M
Name: Zhang     Age: 20 Sex: M
Name: Zhao      Age: 21 Sex: M
Name: Diao      Age: 19 Sex: F
after sorting
Name: Diao      Age: 19 Sex: F
Name: Zhang     Age: 20 Sex: M
Name: Zhao      Age: 21 Sex: M
Name: Guan      Age: 22 Sex: M
Name: Liu       Age: 23 Sex: M
```
</details>

