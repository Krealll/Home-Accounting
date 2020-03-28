#pragma once
#include<iostream>
#include <list>
#include <stack>
#include"Deposit.h"
#include "Expenses.h"
#include "Income.h"
#include"Currency.h"
#include "Tree.h"
#include "Inputexception.h"
#include "table.h"
#include "File.h"

using namespace std;

class comparator   //����� ����������� ��� ��������� ��������
{
private:
	list<string> comparedFields;   //���� ���������� ������������ ����
public:
	list<string> getCompFields() { return comparedFields; }   //���������� ����

	comparator(list<string> obj) :comparedFields(obj) {}

	bool operator()(const Expenses& objr, const Expenses& objl);   //��������� ��������
	bool operator()(const Income& objr, const Income& objl);   //��������� �������
	bool operator()(const Deposit& objr, const Deposit& objl);   //��������� �������
	bool operator()(const Currency& objr, const Currency& objl);   //��������� �����
};

typedef list<string>::iterator iter;
list<string>::iterator findS(list<string>& temp, iter it);   //����� � ����� �� ���������

void setObjCurr(list<string> tempList, Currency & obj);   //������� ��������� ����� ��� ������ �����
void setObj(list<string> tempList, Account & obj);   //������� ��������� ����� ��� ������ 
void findCurr(Tree<Currency>& tree);   //������� ��� ������ ������
double findRate(Currency curr, Tree<Currency>& tree);   //������� ��� ������ ����� ������

void changeCurrFields(typename Tree<Currency>::iterator it, list<string> tempList);   //������� ��� 
                                                                                      //��������� ����� ������
void changeCurrObj(Tree<Currency>::iterator it);   //������� ��������� ������

template<typename T>
inline void getFields(list<string>& temp, T & obj)   //��������� ������� ��� ��������� �����
{
	list<string> ::iterator it = temp.begin();   //������������� �������� �� ������ ������
	string header = obj.createHeader();   //������ ������ ���������
	int position = 0;
	int prevPos = 1;
	while (1)
	{
		if ((position = header.find('|', prevPos)) == string::npos)   //���� �� �������� ����� ������
			break;													  //���� ���� �������
		temp.push_back(header.substr(prevPos, position - prevPos));   //������� � ���� ��������� �� ���� �������
		prevPos = position + 1;
	}
}

template<typename T>
inline double findSum(Tree<T>& tree)   //��������� ������� �������� ����� � ������
{
	Currency temp;   //��������� ������ ��� ������
	Tree<Currency> currTree;   //��������� ������ ��� ������
	string tmp;
	File f("..\\Files\\currency.txt");
	f.openIn();   //��������� ���� ������
	while (f.readLine(tmp))   //���� �� �������� ����� ����� ��������� 
	{
		temp.prep(tmp);   //���������� ������ ��� �������� � ������
		currTree.insert(temp);   //������� �������� � ������
	}
	double sum=0.0,tempo=1.0;   //���������� ��� ����� � ��� �����
	typename Tree<T>::iterator it;
	it = tree.begin();
	for (; it != tree.end(); ++it)   //������ �� ������ ������
	try
	{
		if (typeid(T).name() == typeid(Deposit).name())   //���� ��� � ������ �������
			tempo = dynamic_cast<Deposit&>(*it).getPercent()/100;   //�������� ���������� ��� �����
		sum += (tempo*(*it).getSum()*findRate((*it).getCrnc(), currTree));   //������������ ����� 
																			 //� ������ �����
																		     //���� ��������
	}
	catch (...)   //���������� ����������
	{
		throw;   //��������������� ������ ������
	}
	return sum;
}

template<typename T>
inline T findMost(Tree<T>& tree)   //��������� ������� ������ ������������� ��������
{
	Currency temp;   //��������� ������ ��� ������
	Tree<Currency> currTree;   //��������� ������ ��� ������
	string str;
	File f("..\\Files\\currency.txt");
	f.openIn();   //��������� ���� ������
	while (f.readLine(str))   //���� �� �������� ����� ����� ��������� 
	{
		temp.prep(str);   //���������� ������ ��� �������� � ������
		currTree.insert(temp);   //������� �������� � ������
	}
	T tmp;   //���������� ��� �������� �������� �������������
	double t = 0.0, max=0.0;
	typename Tree<T>::iterator it;
	it = tree.begin();
	for (; it != tree.end(); ++it)   //������ �� ������
	{
		t = (*it).getSum()*findRate((*it).getCrnc(), currTree);   //������������� ��������
																    //� ������ �����
		if (t > max)   //���� ������ �������������
		{
			tmp = *it;   //���������� ������� �������
			max = t;   //���������� ��������
		}
	}
	return tmp;
}

template<typename T>
list<string> chooseFields(T & obj)   //��������� ������� ������ �����
{
	list<string> temp{};   //��������� ���� �����
	getFields(temp, obj);   //�������� ���� �������
	list<string> fields{};   //������������ ���� �����
	int t(1);   //���������� ��� ������
	while (t)
	{
		int count(1);
		list<string>::iterator it = temp.begin();   //������ �����
		system("CLS");
		cout << "�������� ���������:\n";
		cout << "1.������ ��� ��������� ���������" << endl;
		for (; it != temp.end(); ++it)   //������ �� �����
		{
			cout << ++count << ". " << *it << endl;   //������� �������� �����
		}
		cout << "0. ����" << endl;
		rewind(stdin);
		inputNum(cin,t, 0, count);   //���������� ���� 
		if (t == 0)   //���� t = 0
		{			  // ����� �� ���� ������
			if (fields.size() == 0)     //���� ���� �� ���� �������
			{
				t = 1;
				cout << "�� �� ������� �� ������ ���������. ��������� �������.\n";
				system("pause");
				continue;
			}
			break;
		}
		if (t == 1)
		{
			fields.clear();   //�������� ����� ��������� �����
			continue;
		}
		it = temp.begin();
		for (int i = t - 2; i > 0; i--, ++it);   //������ �� ����
		if (findS(fields,it) == fields.end())   //���� ������ ���� ���
		{
			fields.push_back(*it);   //������ ���� � ����
		}
		else
		{
			cout << "�� ��� ������� ����� ��������.\n";
			system("pause");
		}
		
		if (fields.size() == temp.size())   //���� ��� ���� ���� �������
			break;   //����������� ������
	};
	return fields;
}

template <typename T>
void changeObj(typename Tree<T>::iterator it)   //��������� ������� ��������� ������� 
{
	list<string> temp=chooseFields(*it);   //�������� ���� ��� ���������
	changeFields(it, temp);   //������ ��������� ����
	system("CLS");
	cout << "���� ������� ��������" << endl;
}

template <typename T>
void changeFields(T it, list<string> tempList)   //��������� ������� ��������� ����� 
{
	cout << "��������� ���� �������" << endl;
	if (find(tempList.begin(), tempList.end(), "���������      ") != tempList.end())  //���� ������� ���������
	{
		string temp;
		cout << "������� ����� ���������" << endl;
		temp = inputStr(cin, 15);   //���� ������ �������� ����
		dynamic_cast<MonetaryOperation&>(*it).setCategory(temp);   //��������� ����
	}
	if (find(tempList.begin(), tempList.end(), "������         ") != tempList.end())  //���� ������� ������
	{
		string temp;
		cout << "������� ����� ������" << endl;
		temp = inputCurr(cin, 3);   //���� ������ �������� ���� 
		(*it).setCrncName(temp);   //��������� ����
	}
	if (find(tempList.begin(), tempList.end(), "�����          ") != tempList.end())  //���� ������� �����
	{
		double temp;
		if (typeid(*it).name() == typeid(Deposit).name())   //���� �������� � �������
		{
			if (dynamic_cast<Deposit&>(*it).getType() == "�����������")   //���������� ����� ����� ������ 
			{															  //��������� ���� �����
				cout << "�������, �� ������� �� ������ ��������� �������" << endl;
				inputNum(temp);
				(*it).setSum(temp + ((*it).getSum()));
			}
			else
			{
				cout << "�������� ������� �� ������������ ������ ����������" << endl;   //�� ����������� 
																						//����� ������ ��������
				system("pause");
			}
		}
		else
		{
			cout << "������� ����� �����" << endl;
			input(cin, temp);   //���� ������ �������� ���� 
			(*it).setSum(temp);   //��������� ����
		}
	}
	if (find(tempList.begin(), tempList.end(), "���            ") != tempList.end())  //���� ������ ���
	{
		string temp;
		cout << "�������� ����� ���" << endl;
		temp = inputType();   //���� ������ �������� ���� 
		dynamic_cast<Deposit&>(*it).setType(temp);   //��������� ����
	}
	if (find(tempList.begin(), tempList.end(), "�������        ") != tempList.end())  //���� ������ �������
	{
		int temp;
		cout << "������� ����� �������" << endl;
		inputNum(cin,temp,0,100);   //���� ������ �������� ���� 
		dynamic_cast<Deposit&>(*it).setPercent(temp);   //��������� ����
	}
}

template <typename T>
void findItem(Tree<T>& tree)   //��������� ������� ������ ������� � ������
{
	T obj;
	stack<T> res;   //���� ��� �������� ����������
	try
	{
		if (!tree.getRoot())   //���� ������ ������
			throw Myexception("���������� ����� � ������ ������");   //����� ����������
		comparator comp(chooseFields(obj));   //����� ����� ��� ������ ��������
		setObj(comp.getCompFields(), obj);   //���� ����� ��� ������
		typename Tree<T>::iterator iter;
		iter = tree.begin();
		for (; iter != tree.end(); ++iter)   //������ �� ������
		{
			if (comp(obj, *iter))   //����������� �� ��������� ����� 
				res.push(*iter);   //���� �������, �� ������ � ����
		}
		if (res.empty())   //���� �� ����� �������
			throw Myexception("������ �������� ���");   //����� ����������
	}
	catch (Myexception& mex)   //���������� ����������
	{
		throw mex;
	}
	catch (...)   //���������� ����������
	{
		cerr << "����������� ����������" << endl;
		return;
	}
	makeTable(res);   //����� ������� ��������� ����������
}

template <typename T>
inline void makeTable(stack<T>& st)   //��������� ������� �������� ������� �� �����
{
	table _table(static_cast<Account&>(st.top()).createHeader());   //�������������� ������� ���������� 
	while (!st.empty())   //���� ���� �� ����
	{
		_table.addStr(static_cast<Account&>(st.top()).makeStr());   //���������� ������
		st.pop();   //�������� �������� �������� �����
	}
	cout << _table;   //� ����� ��������� ���������� �������
}

template <>
inline void makeTable(stack<Currency>& st)   //������������� ������� �������� ������� �� ����� �����
{
	table _table(st.top().createHeader());   //�������������� ������� ���������� 
	while (!st.empty())   //���� ���� �� ����
	{
		_table.addStr(st.top().makeStr());   //���������� ������
		st.pop();   //�������� �������� �������� �����
	}
	cout << _table;   //� ����� ��������� ���������� �������
}

template<typename it,typename T>
inline it findIter(it begin, it end,T temp)   //��������� ������� ������ 
{											  //�� ���� ����������
	for (; begin != end; ++begin)
		if (*begin == temp)
			break;
	return begin;
}

template<typename it>
inline void makeTable(it begin, it end)   //��������� ������� �������� �������
{
	table _table(static_cast<Account&>(*(begin)).createHeader());   //�������������� ������� ����������
	it i = begin;
	for (; i != end; i++)
		_table.addStr(static_cast<Account&>(*i).makeStr());   //���������� ������
	cout << _table;   //����� ���������� �������
}
template<>
inline void makeTable(Tree<Currency>::iterator begin, Tree<Currency>::iterator end)   //������������� ������� ��������
																			      //������� �� ����� �����
{
	table _table((*begin).createHeader());   //�������������� ������� ����������
	Tree<Currency>::iterator i = begin;
	for (; i != end; i++)
		_table.addStr((*i).makeStr());   //���������� ������
	cout << _table;   //����� ���������� �������
}