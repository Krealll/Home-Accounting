#pragma once
#include "Myexception.h"
#include"Tree.h"


class Inputexception :   //����� ���������� �����
	public Myexception
{
protected:
	int exCode;   //���� ���� ������
public:
	
	Inputexception(string str, int code) : Myexception(str), exCode(code) {};
	~Inputexception();
	int getCode();   //���������� ��� ������

};

bool isDigit(char c);   //�������� �� �����
bool isSpace(char c);   //�������� �� ������
bool isRus(char c);   //�������� �� ���������
bool isEng(char c);   //�������� �� ��������
bool isUpper(char c);   //�������� �� �������� �������� ��������
double setDouble(double d);    //������� ���������� �� �����

template<typename T>
void input(std::istream& in, T& obj)   //��������� ������� ����������� ����� 
{
	bool flag{ false };
	do
	{
		try 
		{
			if(flag)
			cout << "������� ���������� ���� " << typeid(T).name() << ": " << endl;
			flag = true;
			in >> obj;
			if (typeid(T)==typeid(int) || typeid(T)==typeid(double)|| typeid(T) == typeid(long))
				if (!in.good() || in.peek() != '\n')   //���� �� ����������� ���� ������ � ����� �� ����
					throw Inputexception("������ ������������ �������",1);
		}
		catch (Inputexception& inpex)   //��������� ����������
		{
			flag = false;
			cin.clear();
			cin.ignore(32767, '\n');
			cerr << "����������:" << inpex.what() << "\n ��� ������:" << inpex.getCode() << endl;
		}
		catch (...)   //���������� ����������
		{
			flag = false;
			cout << "����������� ����������";
			rewind(stdin);
			in.clear();
		}
	} while (!flag);
}

template <typename T>
inline void inputNum(istream& is,T& n, T j, T k)   //������� ����� ����� � ����������
{
	bool flag{ true };
	do
	{
		try
		{
			if(!flag)
			cout << "������� ����� � ���������: �� " << j << " �� " << k << ")" << endl;
			flag = true;
			is >> n;
			if (!is.good() || is.peek() != '\n')   //���� �� ����������� ���� ������ � ����� �� ����
				throw Inputexception("��������� ���������� �� ������������� ����", 2);
			if ((n < j) || (n > k))   //���� ������� �� ������ � ��������
				throw Inputexception("�������� ���������� ��������� ��� ��������� ���������", 3);
		}
		catch (Inputexception& inpex)   //��������� ����������
		{
			flag = false;
			is.clear();
			is.ignore(32767, '\n');
			cerr << "����������:" << inpex.what() << "\n ��� ������:" << inpex.getCode() << endl;
		}
		catch (...)   //���������� ����������
		{
			flag = false;
			cout << "����������� ����������" << endl;
			rewind(stdin);
			is.clear();
		}
	} while (!flag);
}


template <typename T>
inline void inputNum(T& n)   //������� ����� �����
{
	bool flag{ true };
	do
	{
		try
		{
			if (!flag)
				cout << "������� ������������� �������� ��������" << endl;
			flag = true;
			cin >> n;
			if (!cin.good() || cin.peek() != '\n')   //���� �� ����������� ���� ������ � ����� �� ����
				throw Inputexception("��������� ���������� �� ������������� ����", 2);
			if (n<0)   //���� ����� ������ ����
				throw Inputexception("�������� ������ �� ������ ���� ��������������", 4);
		}
		catch (Inputexception& inpex)   //��������� ����������
		{
			flag = false;
			cin.clear();
			cin.ignore(32767, '\n');
			cerr << "����������:" << inpex.what() << "\n ��� ������:" << inpex.getCode() << endl;
		}
		catch (...)   //���������� ����������
		{
			flag = false;
			cout << "����������� ����������" << endl;
			rewind(stdin);
			cin.clear();
		}

	} while (!flag);
}

inline string inputStr(istream& is, unsigned end)   //������� ����� 
{
	string tmp;
	bool flag{ true };
	do
	{
		try
		{
			if(!flag)
			cout << "������� ������ ������ " << end << " ��������, ��������� ������ �������� �������� � �������:" << endl;
			flag = true;
			char* buff = new char[80]{};
			rewind(stdin);
			is.getline(buff, 80);
			tmp = buff;
			for (unsigned i = 0; i < tmp.length(); i++)
				if (!(isRus(tmp[i])||isSpace(tmp[i])))   //���� �� ������� ������ ���� ������
					throw
					Inputexception("��������� ������ ����� ������ �������", 5);
			if (tmp.length() > end)   //���� ������ ������ ��������� �������
				throw
				Inputexception("��������� ������ ��������� ���������� ������", 3);
			if(tmp.length() < 1)   //���� ������ ������
				throw
				Inputexception("��������� ������ �� ������ ���� ������", 3);
		}
		catch (Inputexception& inpex)   //��������� ����������
		{
			flag = false;
			is.clear();
			rewind(stdin);
			cerr << "����������:" << inpex.what() << "\n ��� ������:" << inpex.getCode() << endl;
		}
		catch (...)   //���������� ����������
		{
			flag = false;
			cout << "����������� ����������" << endl;
			rewind(stdin);
			cin.clear();
		}
	} while (!flag);
	return tmp;
}

inline string inputCurr(istream& is, unsigned end)   //������� ����� 
{
	string tmp;
	bool flag{ true };
	do
	{
		try
		{
			if(!flag)
			cout << "������� ������ �������� " << end << " ��������, ��������� ������ ���������� ������� �������� ��������:" << endl;
			flag = true;
			char* buff = new char[80]{};
			rewind(stdin);
			is.getline(buff, 80);
			tmp = buff;
			for (unsigned i = 0; i < tmp.length(); i++)
				if (!(isUpper(tmp[i])))   //���� �� ������� �������� �������� ��������
					throw
					Inputexception("��������� ������ ����� ������ �������", 5);
			if (tmp.length() != end)   //���� ������ �� �������� 3-�����������(������ ������)
				throw
				Inputexception("��������� ������ �� ������������� ������� ������", 6);
		}
		catch (Inputexception& inpex)   //��������� ����������
		{
			flag = false;
			is.clear();
			rewind(stdin);
			cerr << "����������:" << inpex.what() << "\n ��� ������:" << inpex.getCode() << endl;
		}
		catch (...)   //���������� ����������
		{
			flag = false;
			cout << "����������� ����������" << endl;
			rewind(stdin);
			cin.clear();
		}
	} while (!flag);
	return tmp;
}

inline string inputType()   //������� ������ ���� ������
{
	string str;
	std::cout << "��������� ���� ������: 1 - �����������| 2 - �� �����������" << endl;
	cout << "�������� ���:" << endl;
	int n;   //��������� ���������� ��� ������
	inputNum(cin,n, 1, 2);   //���������� ���� 
	if (n == 1)
		str = "�����������";
	else
		str = "�� �����������";
	return str;
}