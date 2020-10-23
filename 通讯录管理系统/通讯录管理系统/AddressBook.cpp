#include "AddressBook.h"

struct AddrMumber
{
	string name = "��";
	string sex = "��";
	int age = 0;
	int phoneNumber = 0;
} AddrBook[MAX_SIZE];



//ͨѶ¼����
void surface()
{
	cout << "1.������ϵ��" << endl;
	cout << "2.���������ϵ��" << endl;
	cout << "3.�����ϵ��" << endl;
	cout << "4.ɾ����ϵ��" << endl;
	cout << "5.�����ϵ��" << endl;
	cout << "6.�˳�" << endl;
	cout << "���������ֽ��в���" << endl;
}
//�����û���������ݲ�������Ӧ����
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
//������ϵ��
void searchMumber()
{
	cout << "��������Ҫ���ҵ��˵����֣�";
	string inName;
	cin >> inName;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (AddrBook[i].name == inName)
		{
			cout << inName << "�ĵ绰����Ϊ" << AddrBook[i].phoneNumber << endl;
			break;
		}
		else if (AddrBook[i].name == "��")
		{
			cout << "��δ����" << inName << "�ĵ绰����" << endl;
			break;
		}
	}
	cout << "��������ص����˵�" << endl;
	system("pause");
}
//���������ϵ��
void printAllMumbers()
{
	int i = 0;
	for (i = 0; i < MAX_SIZE; i++)
	{
		if (AddrBook[0].name == "��")
		{
			cout << "����δ������ϵ�ˣ�" << endl;
			break;
		}
		if (AddrBook[i].name != "��")
		{
			cout << "������" << AddrBook[i].name << "\t" << "�绰���룺" << AddrBook[i].phoneNumber << endl;
		}
		else
		{
			break;
		}
	}
	if (i)
		cout << "������" << endl;
	cout << "��������ص����˵�" << endl;
	system("pause");
}
//�����ϵ��
void addMumber()
{
	int x = 1; //�����ж��û��Ƿ������ӵı���
	string newName;
	int newPhoneNumber;
	while (x)
	{
		cout << "��������Ҫ��ӵ��˵����֣�";
		cin >> newName;
		cout << "��������Ҫ��ӵ��˵ĵ绰���룺";
		cin >> newPhoneNumber;
		for (int i = 0; i < MAX_SIZE; i++)
		{
			if (AddrBook[i].name == "��")
			{
				AddrBook[i].name = newName;
				AddrBook[i].phoneNumber = newPhoneNumber;
				cout << "��ӳɹ���" << endl;
				break;
			}
			else if (i == MAX_SIZE - 1)
			{
				cout << "�������洢���ƣ����ʧ�ܣ�" << endl;
			}
		}
		cout << "����1������ӣ�����0�ص������棺";
		cin >> x;
	}
}
//ɾ����ϵ��
void delMumber()
{
	cout << "��������Ҫɾ�����˵����֣�";
	string inName;
	cin >> inName;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (AddrBook[i].name == inName)
		{
			int x = 0; //�����ж��Ƿ�ɾ���ɹ�
			for (int j = 0; j < MAX_SIZE - 1; j++)
			{
				if (AddrBook[j + 1].name == "��")
				{
					AddrBook[i] = AddrBook[j];
					AddrBook[j].name = "��";
					AddrBook[j].phoneNumber = 0;
					cout << "ɾ���ɹ���" << endl;
					x = 1;
					break;
				}
			}
			if (x)
				break;
		}
		else if (AddrBook[i + 1].name == "��")
		{
			cout << "�㻹û�д������ϵ�˵ĵ绰����";
			break;
		}
	}
	cout << "��������ص����˵�" << endl;
	system("pause");
}
//�����ϵ��
void cleanMumbers()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		if (AddrBook[i].name != "��")
		{
			AddrBook[i].name = "��";
			AddrBook[i].phoneNumber = 0;
		}
		else
		{
			break;
		}
	}
	cout << "����ɹ�����������ص����˵�" << endl;
	system("pause");
}
//�˳�ͨѶ¼
void exitAddr()
{
	exit(0);
}