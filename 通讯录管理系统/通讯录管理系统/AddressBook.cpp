#include "AddressBook.h"

struct AddrMumber
{
	string name = "无";
	string sex = "无";
	int age = 0;
	int phoneNumber = 0;
} AddrBook[MAX_SIZE];



//通讯录界面
void surface()
{
	cout << "1.查找联系人" << endl;
	cout << "2.输出所有联系人" << endl;
	cout << "3.添加联系人" << endl;
	cout << "4.删除联系人" << endl;
	cout << "5.清空联系人" << endl;
	cout << "6.退出" << endl;
	cout << "请输入数字进行操作" << endl;
}
//读入用户输入的数据并进行相应操作
void inNumber()
{
	int inNumber = 7;
	while (inNumber)
	{
		cin >> inNumber;
		switch (inNumber)
		{
		case 1:
			searchMumber();
			break;
		case 2:
			printAllMumbers();
			break;
		case 3:
			addMumber();
			break;
		case 4:
			delMumber();
			break;
		case 5:
			cleanMumbers();
			break;
		case 6:
			exitAddr();
			break;
		}
		system("CLS");
		surface();
	}
}
//查找联系人
void searchMumber()
{
	cout << "请输入你要查找的人的名字：";
	string inName;
	cin >> inName;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (AddrBook[i].name == inName)
		{
			cout << inName << "的电话号码为" << AddrBook[i].phoneNumber << endl;
			break;
		}
		else if (AddrBook[i].name == "无")
		{
			cout << "您未存入" << inName << "的电话号码" << endl;
			break;
		}
	}
	cout << "按任意键回到主菜单" << endl;
	system("pause");
}
//输出所有联系人
void printAllMumbers()
{
	int i = 0;
	for (i = 0; i < MAX_SIZE; i++)
	{
		if (AddrBook[0].name == "无")
		{
			cout << "您还未存入联系人！" << endl;
			break;
		}
		if (AddrBook[i].name != "无")
		{
			cout << "姓名：" << AddrBook[i].name << "\t" << "电话号码：" << AddrBook[i].phoneNumber << endl;
		}
		else
		{
			break;
		}
	}
	if (i)
		cout << "输出完毕" << endl;
	cout << "按任意键回到主菜单" << endl;
	system("pause");
}
//添加联系人
void addMumber()
{
	int x = 1; //用来判断用户是否继续添加的变量
	string newName;
	int newPhoneNumber;
	while (x)
	{
		cout << "请输入你要添加的人的名字：";
		cin >> newName;
		cout << "请输入你要添加的人的电话号码：";
		cin >> newPhoneNumber;
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (AddrBook[i].name == "无")
			{
				AddrBook[i].name = newName;
				AddrBook[i].phoneNumber = newPhoneNumber;
				cout << "添加成功！" << endl;
				break;
			}
			else if (i == MAX_SIZE - 1)
			{
				cout << "超过最大存储限制，添加失败！" << endl;
			}
		}
		cout << "输入1继续添加，输入0回到主界面：";
		cin >> x;
	}
}
//删除联系人
void delMumber()
{
	cout << "请输入你要删除的人的名字：";
	string inName;
	cin >> inName;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (AddrBook[i].name == inName)
		{
			int x = 0; //用来判断是否删除成功
			for (int j = 0; j < MAX_SIZE - 1; j++)
			{
				if (AddrBook[j + 1].name == "无")
				{
					AddrBook[i] = AddrBook[j];
					AddrBook[j].name = "无";
					AddrBook[j].phoneNumber = 0;
					cout << "删除成功！" << endl;
					x = 1;
					break;
				}
			}
			if (x)
				break;
		}
		else if (AddrBook[i + 1].name == "无")
		{
			cout << "你还没有存入该联系人的电话号码";
			break;
		}
	}
	cout << "按任意键回到主菜单" << endl;
	system("pause");
}
//清空联系人
void cleanMumbers()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (AddrBook[i].name != "无")
		{
			AddrBook[i].name = "无";
			AddrBook[i].phoneNumber = 0;
		}
		else
		{
			break;
		}
	}
	cout << "清除成功！按任意键回到主菜单" << endl;
	system("pause");
}
//退出通讯录
void exitAddr()
{
	exit(0);
}