#pragma warning(disable : 4996)  
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <time.h>

const std::string getDate()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

void clrScreen()
{
	system("pause");
	system("cls");      // 清空屏幕
}

/// Define struct
// Struct Address
struct Name
{
	std::string m_Name;
	std::string m_Familyname;
};

struct Address
{
	int m_Postcode;
	std::string m_City;
};


// Struct Contact
struct Person
{
	Name m_Name;
	char m_Gender;
	std::string m_Tel;
	Address m_Address;
	std::string m_AddDate;
	std::string m_ModDate;
};

// Struct Phonebook
#define MAX 1000

struct Phonebook
{
	struct Person personArr[MAX];  // 直接开辟了一个1000个栏位的数组，只是信息都是空的；程序结束后才会释放
	int m_Len;  // 末位标记：用这个变量记录最后一位有效信息的index
};

/// CSV write & read
/// TODO: 把通讯录变量存储到外部csv；每次启动时加载这个csv
/*
void setCSV(std::string csv_path, Phonebook phonebook)
{
	std::ofstream dataFile;
	dataFile.open("test.csv", std::ios::out | std::ios::trunc);
}

Phonebook getCSV(std::string csv_path)
{
}
*/

// set & get name
void setName(Name * pName)
{
	std::string name;
	std::cout << " Name:      \t";
	std::cin >> name;
	pName->m_Name = name;

	std::string fname;
	std::cout << " Familyname:\t";
	std::cin >> fname;
	pName->m_Familyname = fname;
}

const std::string getName(Name name)
{
	return  name.m_Familyname + ',' + name.m_Name;
}

// set & get address
void setAddress(Address * pAddress)
{
	int postcode;
	std::cout << " Postcode:\t";
	std::cin >> postcode;
	pAddress->m_Postcode = postcode;

	std::string city;
	std::cout << " City:    \t";
	std::cin >> city;
	pAddress->m_City = city;
}

const std::string getAddress(Address address)
{
	return std::to_string(address.m_Postcode) + " " + address.m_City + ".";
}

/// set & get Person
void setPerson(Person * pPerson)  // set函数必须用地址传值，否则无法更改实参内容
{
	std::cout << "Input contact's Name:" << std::endl;
	setName(&pPerson->m_Name);

	char gender;
	std::cout << "Gender ('m' for Mr.; 'w' for Ms.)" << std::endl;
	std::cin >> gender;
	pPerson->m_Gender = gender;

	std::string tel;
	std::cout << "Input contact's Tel. number:" << std::endl;
	std::cin >> tel;
	pPerson->m_Tel = tel;

	std::cout << "Set contact's Address:" << std::endl;
	setAddress(&pPerson->m_Address);
}

void prtPerson(Person * pPerson) // get函数可以使用值传递也可以用地址传递；地址传递更省内存，因为不会产生数据副本；值传递可以保护实参不被修改
{
	std::cout
		<< (pPerson->m_Gender == 'm' ? "Mr." : "Ms.") << "\t"
		<< getName(pPerson->m_Name) << "\t"
		<< pPerson->m_Tel << "\t"
		<< getAddress(pPerson->m_Address) << "\t\t| "
		<< pPerson->m_AddDate << "\t| "
		<< pPerson->m_ModDate << std::endl;
}

/// Func1: Add contact
/// No more than 1000; 
/// Info: Name, Tel, Address, Add date, Last modifi date
void addPerson(Phonebook * pPhonebook)
{
	// 判断通讯录是否已满
	if (pPhonebook->m_Len == MAX)
	{
		std::cout << "Phonebook already full, cannot add new contact." << std::endl;
	}
	else
	{
		// 添加联系人：往开辟好的数组里写信息
		setPerson(&pPhonebook->personArr[pPhonebook->m_Len]);

		pPhonebook->personArr[pPhonebook->m_Len].m_AddDate = getDate();
		pPhonebook->personArr[pPhonebook->m_Len].m_ModDate = "---";

		std::cout << "Successfully added " << getName(pPhonebook->personArr[pPhonebook->m_Len].m_Name) << std::endl;
		pPhonebook->m_Len++;
	}
	clrScreen(); // 清空屏幕
}

/// Func2: Show contacts
/// check if phonebook is blank; 
/// If yes, print msg.
/// If no, show info:
/// Info: Name, Tel, Address, Add date, Last modifi date
void showPersons(Phonebook * pPhonebook)
{
	if (pPhonebook->m_Len == 0)
	{
		std::cout << "Phonebook is blank. No contacts saved." << std::endl;
	}
	else
	{
		std::cout << "Anrede\tName\t\tTel.\t\tAdd.\t\t\t| add date\t\t| last modified on " << std::endl;
		for (int i = 0; i < pPhonebook->m_Len; i++)
		{
			prtPerson(&pPhonebook->personArr[i]);
		}
	}
	clrScreen(); // 清空屏幕
}

/// Func3: Delete contacts
/// check if the person with the given name exists; 
/// If yes, return the index.
/// If no, return -1
int isExistPerson(Phonebook * pPhonebook, std::string name)
{
	for (int i = 0; i < pPhonebook->m_Len; i++)
	{
		if (getName(pPhonebook->personArr[i].m_Name) == name)
		{
			return i;
		}
	}
	return -1;
}
//TODO: 增加模糊搜寻功能

void deletePerson(Phonebook * pPhonebook)
{
	std::string nameDel;
	std::cout << "Please input the name of contact to be deleted:" << std::endl;
	std::cin >> nameDel;
	int ret = isExistPerson(pPhonebook, nameDel);
	if (ret == -1)
	{
		std::cout << nameDel << "does not exist." << std::endl;
	}
	else
	{	
		char flagDel;
		std::cout << "Found " << nameDel << ", sure to delete? [y]Yes; [n]No" << std::endl;
		std::cin >> flagDel;
		if (flagDel == 'y')
		{
			///Delete:
			///把待删元素后面的所有元素前移一位覆盖
			///最后更新数组长度
			for (int j = ret; j < pPhonebook->m_Len; j++)
			{
				pPhonebook->personArr[j] = pPhonebook->personArr[j + 1];
			}
			// 此时personArr末两位元素相同
			pPhonebook->m_Len --;  // 最后一位并没有被删除，只是我们把末位标识前移，末位就被忽略掉了
			// sizeof(pPhonebook->personArr) / sizeof(pPhonebook->personArr[0]) 一直是1000
			std::cout << nameDel << "deleted !" << std::endl;
		}

		//array并不能做到“删除”元素。从声明开始它就是定长度的，这里也就是MAX=1000
		//用vector可以实现删除一个元素，其余元素自动顶位并且释放空间，向量长度也会相应减一。这种做法更妥当一些。
		// https://stackoverflow.com/questions/4023011/delete-element-from-c-array

		else
		{
			std::cout << "Delete canceled." << std::endl;
		}
	}
	clrScreen();
}

/// Func4: Find contact
/// check if the person with the given name exists; 
/// If yes, print the info.
/// If no, print err msg
void findPerson(Phonebook * pPhonebook)
{
	std::string nameFind;
	std::cout << "Please input the name of contact you want to find:" << std::endl;
	std::cin >> nameFind;
	int ret = isExistPerson(pPhonebook, nameFind);
	if (ret == -1)
	{
		std::cout << nameFind << "does not exist." << std::endl;
	}
	else
	{
		std::cout << "Found. Printed below:" << std::endl;
		std::cout << "Anrede\tName\t\tTel.\t\tAdd.\t\t\t| add date\t\t| last modified on " << std::endl;
		prtPerson(&pPhonebook->personArr[ret]);
	}
	/// TODO: add feature: 输入部分姓名返回满足条件的联系人；不区分大小写
	clrScreen();
}

/// Func5: Modify contact
/// check if the person with the given name exists; 
/// If yes, modify the contact.
/// If no, print err msg
void modPerson(Phonebook * pPhonebook)
{
	std::string nameMod;
	std::cout << "Please input the name of contact you want to modify:" << std::endl;
	std::cin >> nameMod;
	int ret = isExistPerson(pPhonebook, nameMod);
	if (ret == -1)
	{
		std::cout << nameMod << "does not exist." << std::endl;
	}
	else
	{
		// 修改联系人
		setPerson(&pPhonebook->personArr[ret]);

		pPhonebook->personArr[ret].m_ModDate = getDate();

		std::cout << "Successfully modified " << nameMod
			      << " as " << getName(pPhonebook->personArr[ret].m_Name) << std::endl;
	}
	/// TODO: add feature: 输入部分姓名返回满足条件的联系人；不区分大小写
	clrScreen();
}

/// Func6: Clear all contacts
/// 直接把有效位的标记置0
/// 数据依然存在，但不可访问
void clearPersons(Phonebook * pPhonebook)
{
	pPhonebook->m_Len = 0;
	std::cout << "Phonebook cleared" << std::endl;
	clrScreen();
}
// https://stackoverflow.com/questions/33335668/how-to-free-an-array-in-c-c

/// Menu
void showMenu(Phonebook phonebook)
{
	std::cout << "===================================================================" << std::endl
		<< "\t * Press [1] \t Add a new contact" << std::endl
		<< "\t * Press [2] \t Show all contacts" << std::endl
		<< "\t * Press [3] \t Delete contact via name" << std::endl
		<< "\t * Press [4] \t Find contact via name" << std::endl
		<< "\t * Press [5] \t Modify contact via name" << std::endl
		<< "\t * Press [6] \t DELETE ALL" << std::endl
		<< "\t * Press [q] \t Quit" << std::endl
		<< "===================================================================" << std::endl
		<< "                       [ " << getDate() << " ]                    " << std::endl
		<< "-------------------< Please select one function >------------------" << std::endl
		<< "current saved contacts:  " << phonebook.m_Len << std::endl;
}

int main()
{	
	// Initialize a Phonebook
	Phonebook phonebook;
	phonebook.m_Len = 0;  // !!! 不初始化长度会导致没有读取权限

	int inSelect = 0;

	while (true)
	{
		showMenu(phonebook);

		std::cin >> inSelect;

		switch (inSelect)
		{
		case 1:  // Add a new contact
			addPerson(&phonebook);  // 地址传递，修改实参
			break;
		case 2:  // Show all contacts
			showPersons(&phonebook);
			break;
		case 3:  // Delete contact via name
			deletePerson(&phonebook);
			break;
		case 4:  // Find contact via name
			findPerson(&phonebook);
			break;
		case 5:  // Modify contact via name
			modPerson(&phonebook);
			break;
		case 6:  // DELETE ALL
			clearPersons(&phonebook);
			break;
		case 0:  // Quit
			std::cout << "Quit. Update unsaved." << std::endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}