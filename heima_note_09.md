# 09. 模板

建立通用的程序结构，提高代码的复用性。这种编程风格叫做 **泛型编程**。

<br>

# 9.1 函数模板
建立一个通用函数，其返回值类型和形参类型可以先不确定，而用一个 **虚拟的类型** 来代表。  

语法：
```cpp
template<typename T>
// func declaration or definition
```
- `template` 声明创建模板
- `typename` 声明后面的名称是一种数据类型，可以用 class 代替
- `T` 通用的数据类型，通常为大写字母

例如，写一个交换数值的函数。不管传入的值是 int，float 还是 double， 甚至是其他自定义的类或结构体，实现功能的函数体都大同小异。这种情况就可以使用函数模板统一处理，而不必针对每一种数据类型写一个函数
```cpp
template<typename T>  // declare `T` is an universal data type
void swapTemplate (T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}
```
这样，一个适配所有数据类型的交换函数模板就写好了。其中，`typename` 关键字仅适用于函数模板；`class` 关键字对于类模板和函数模板都可用。

如何使用函数模板对具体的数据类型做操作呢？有两种方式：
### **1）自动类型推导**
```cpp
int a = 10;
int b = 20;
swapTemplate(a, b);
```
### **2）显式指定类型**
```cpp
int a = 10;
int b = 20;
swapTemplate<int>(a, b);  // indicate `T` here should be int
```
***
## 函数模板注意事项

- 自动类型推导，必须推导出一致的数据类型 T 才可以使用
- 模板必须确定出 T 的数据类型，才可以使用

### **错误1：** 使用自动类型推导，但输入数据的类型不一致
```cpp
// Template ---------------------------
template<class T>
void mySwap(T &a, T &b)
{
	T temp = a;
	a = b;
	b = temp;
}

// Test --------------------------------
void test01()
{
	float a = 12.1F;
	char b = 'b';
	mySwap(a, b);  // -> ERR
}
```
ERROR msg
```
E0304 no instance of function template "mySwap" matches the argument list
```
### **错误2：** 模板函数体当中没有给 T 匹配数据类型
```cpp
template<class T>
void funcTemplate(T &a, T &b)
{
	cout << "call the template func" << endl;
}

// Test --------------------------------
void test01()
{
	funcTemplate();  // implicit -> ERR
}

void test02()
{
	funcTemplate<int>();  // explicit -> OK
}
```
ERROR msg
```
E0304 no instance of function template "funcTemplate" matches the argument list
```

## 函数模板案例：
- 利用函数模板封装一个排序函数，可以对任意指定数据类型的数组做排序
- 排序规则从大到小，算法使用 **选择排序**
- 分别用 **char数组** 和 **int数组** 测试
# 9.2 类模板