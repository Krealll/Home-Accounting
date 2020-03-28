#pragma once
#include"Tree.h"
#include"Income.h"
#include"Expenses.h"
#include"Deposit.h"
#include "algorithm.h"
#include <stack>
#include"File.h"

template <typename T>   //�������� ����� ����������
class Interface
{
private: 
	string path{};   //������ c ���� � �����
	string crnc{};   //������ ��������� ������

public:
	Tree<T> data;   //��������� ������ ������
	int flag = 0;   //���� ��� ������������

	bool start();   //����� ������ � �������
	bool subMenu();   //������� ������ ������������
	void currMenu();   //������� ������ ������
	void saveResult();   //����� ���������� ���������
	void load();   //����� �������� ������ �� �����
	void undo(Tree<T>& tree, stack<T>& stItem, stack<int>& stCode);   //��������� ����� ������ 
	                                                                  //���������� ��������
	template<typename T>
	void change(Tree<T>& data,typename Tree<T>::iterator it)   //��������� ����� 
															   //��������� ������
	{
		changeObj<T>(it);
	}
	template<>
	void change(Tree<Currency>& data,Tree<Currency>::iterator it)   //������������� ������
																    //��������� ��� ������
	{
		changeCurrObj(it);
	}
	template<typename T>
	void search(Tree<T>& data)   //��������� ����� ������ ������
	{
		findItem(data);
	}
	template<>
	void search(Tree<Currency>& data)   //������������� ������ ������ ��� ������
	{
		findCurr(data);
	}
	template <typename T>
	void show(Tree<T>& data)   //��������� ����� ������ ������� �����
	{
		cout << "������� " << Name(data.getRoot()->value);
		makeTable(data.begin(), data.end());
	}
	template <>
	void show(Tree<Income>& data)   //������������� ������ ������ �������
								    //��� �������
	{
		cout << "������� ";
		if (flag)
			cout << "����������� �������" << endl;
		else
			cout << "����������� �������" << endl;
		makeTable(data.begin(), data.end());
	}
	template <>
		void show(Tree<Expenses>& data)   //������������� ������ ������ �������
										  //��� ��������
	{
			cout << "������� ";
			if (flag)
				cout << "����������� ��������" << endl;
			else
				cout << "������� ��������" << endl;
		makeTable(data.begin(), data.end());
	}

	template <typename T>
	string Name(T& obj)   //��������� ����� ����� ����
	{
		return "��������\n";
	}
	template <>
	string Name(Income& obj)   //������������� ������ ����� ��� �������
	{
		return "�������\n";
	}
	template <>
	string Name(Currency& obj)   //������������� ������ ����� ��� ������
	{
		return "������\n";
	}
	template <>
	string Name(Deposit& obj)   //������������� ������ ����� ��� �������
	{
		return "�������\n";
	}
};

template<typename T>
void Interface<T>::load()   //����� �������� ������ �� ����
{
	T temp("");
	if (!flag)   //���� �� ����������� ������������ 
	path = temp.getPath();   //��������� ���� � �����
	else if (typeid(T).name() == typeid(Income).name())   //����� ������ ����
														  //� ������ ������������
			path = "..\\Files\\plIncome.txt";
		else
			path = "..\\Files\\plExpenses.txt";
	string tmp;   //��������� ������ ��� ������
	File f(path);   //����� ������������ � ���������
	f.openIn();   //�������� ����� ��� ������
	try
	{
		while(f.readLine(tmp))   //������ ���� ���� �� �������� �����
		{
			temp.prep(tmp);   //����� ���� �������
			data.insert(temp);   //��������� ������� � ������
		}
		if (typeid(T).name() == typeid(Currency).name() && (!data.getRoot()))   //���� ����
																				//����� ����
		{
			temp.prep("BYN|1");   //����� �������� ������ BYN
			data.insert(temp);   //��������� ������� � ������
		}
	}
	catch (Myexception& obj)   //��������� �������������� ��������
	{
		cerr << "����������, ��������� � ������� � �����: " << obj.what() << endl;
		system("pause");
		return;
	}
	catch (...)   //����������� ����������
	{
		cerr << "���������� ����������\n";
		return;
	}
}

template<typename T>   //��������� ����� ������ ���������� ��������
inline void Interface<T>::undo(Tree<T>& tree, stack<T>& stItem, stack<int>& stCode)
{
	if (stCode.top() == 1)   //���� ������ ����� �������� ��������� 1 - ��������� ����������
	{
		stCode.pop();   //������� ������� ������� ����� ���������
		T temp;
		temp = stItem.top();   //�������� �������, ������� ��� �������� �� ����� ���������
		tree.pop(temp);   //������� ������ ������� �� ������
		stItem.pop();   //������� ������� ������� �����
	}
	else if (stCode.top() == 2)   //�������� ��������� 2 - ��������� ��������
	{
		stCode.pop();   //������� ������� ������� ����� ���������
		tree.insert(stItem.top());   //��������� � ������ �������� �������
		stItem.pop();   //������� ������� ������� �����
	}
	else if (stCode.top() == 3)   //�������� ��������� 3 - ��������� ���������
	{
		stCode.pop();   //������� ������� ������� ����� ���������
		tree.pop(stItem.top());   //������� ����� ���������� ������� �� ������
		stItem.pop();   //������� ������� ������� �����
		tree.insert(stItem.top());    //��������� ������ �������
		stItem.pop();   //������� ������� ������� �����
	}
}

template<typename T>
bool Interface<T>::subMenu()    //��������� ������� ������ ������������
{
	system("CLS");
	int ans{};    //���������� ��� ����������������� �����
	do
	{
		T obj;    //��������� ������ ��� ������
		cout << "���� " << Name(obj);
		cout << "1: ������������ " << Name(obj);
		cout << "2: ���� ������� " << Name(obj);
		cout << "3: ����� � ������� ����\n";
		cout << "0: �����\n";
		inputNum(cin,ans,0,4);    //���������� ���� 
		system("CLS");
		switch (ans)
		{
		case 1:
		{
			this->flag = 1;    //��������� ����� ������������
			if (this->start())    //������ ������ ������
				return true;
			else
				return false;
		}
		case 2:
		{
			if (this->start())    //������ ������ ������
				return true;    //����� � ������� ����
			else
				return false;    //����� �� ���������
		}
		case 3:
		{
			system("CLS");
			return true;    //����� � ������� ����
		}
		case 0: {
			system("CLS");
			return false;    //����� �� ���������
		}
		default: {
			cout << "\nIncorrect answer, please, try again" << endl;
			system("pause");
			break;
		}
		}
	} while (ans);
	return true;
}

template<typename T>
inline void Interface<T>::currMenu()    //��������� ���� ������ ������
{
	try
	{
		int i;    //���������� ��� ������ ������
		Interface<Currency> temp;    //��������� �������� ��� ������
		temp.load();    //�������� ������ �� ����� �����
		if (!temp.data.empty())    //���� ���� �� ������
		{
			cout << "������� ������" << endl;
			makeTable(temp.data.begin(), temp.data.end());    //����� ������� �����
		}
		else
			throw Myexception("��� ����� ��� ������");    //����� �������������� ��������
		cout << "\n�������� ����� ������ ��� ������:";
		inputNum(cin,i, 1, temp.data.size());    //���������� ���� 
		typename Tree<Currency>::iterator it;
		it = temp.data.begin();    //��������� ��������� �� ������ ������ �����
		for (; i > 1; i--)
			++it;    //������ �� ������ �� ������������ ��������
		this->crnc = (*it).getName();    //���������� ��������� ������
		system("CLS");
	}
	catch (Myexception& obj)    //��������� ����������
	{
		cerr << "����������: " << obj.what() << endl;
		system("pause");
		return;
	}
	catch (...)    //����������� ����������
	{
		cerr << "���������� ����������\n";
		system("pause");
		return;
	}
}

template<typename T>
inline void Interface<T>::saveResult()    //����� ���������� ������ � ����
{
	File f(path);     //����������� � ���������� ����
	f.openOut();    //�������� ����� ��� �������� ������ � ����
	
	if (data.getRoot())    //���� ������ �� ������
	{
		typename Tree<T>::iterator it;
		it = data.preBegin();    //������������� �������� �� ������ ������ 
							     //��� ������� ������
		while (it != data.end())    //���� �� ����� �� ����� ������
		{
			f.putObj(*it);    //��������� ������� � ����
			it.preOrder();    //����������� �������� �� 1(������ �����)
		}
	}
}

template<typename T>
bool Interface<T>::start()    //��������� ����� ������ � �������
{
	stack<int> stCode;    //���� ��������� ��� ������ ��������
	stack<T> stItem;    //���� ��������� ��� ������ ��������
	this->load();    //��������� ������ �� ����� � ������
	if (typeid(T).name() != typeid(Currency).name())    //���� �������� �� � �������
	{
		currMenu();    //�������� ���� ������ ������
	}
	T tmp(crnc);    //����� �������� ������
	int ans{};    //���������� ��� ����������������� �����
	do
	{
		if (typeid(T).name() != typeid(Currency).name())
		cout << "��������� ������: "<< crnc << endl;
		cout << "���� ";
		cout << Name(tmp);
		cout << "1: �������\n";
		cout << "2: ������� ���� �������\n";
		cout << "3: �������� \n";
		cout << "4: ������� ��\n";
		cout << "5. ��������\n";
		cout << "6. �������� ��������� ��������\n";////////////////////
		cout << "7: �����\n";
		cout << "8: ����� � ������� ����\n";
		cout << "0: �����\n";
		inputNum(cin,ans, 0, 8);    //���������� ����
		switch (ans)
		{
		case 1:
		{
			system("CLS");
			cout << "1:\n������� �������: " << endl;
			input(cin, tmp);    //���� �������� ��� ����������
			try
			{
				data.insert(tmp);    //���������� �������� � ������
				stCode.push(1);    //������� �������� � ���� ���������
				stItem.push(tmp);    //������� � ���� �������
			}
			catch (Myexception& obj)    //��������� ����������
			{
				cerr << "����������: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //���������� ����������
			{
				cerr << "���������� ����������\n";
			}
			break;
		}
		case 2:
		{
			int i;
			system("CLS");
			try
			{
				if (data.getRoot())    //���� ������ �� ������ - ����� ������� ������
				{
					cout << "2:\n������� ����� �������� ��� ��������: " << endl;
					makeTable(data.begin(), data.end());    
				}
				else
					throw Myexception("��� ���������� ��� ��������");    //����� ����������
				inputNum(cin,i, 1, data.size());    //����� �� ������� �������� ��� ��������
				typename Tree<T>::iterator it;
				it = data.begin();    //��������� ��������� �� ������ ������
				for (; i > 1; i--)
					++it;    //������ �� ������ �� ������� ��������
				stItem.push(*it);    //������� �������� � ����
				data.pop(*it);    //�������� �������� �� ��������
				stCode.push(2);    //������� �������� � ���� ���������
			}
			catch (Myexception& obj)    //��������� �������������� ��������
			{
				cerr << "����������: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //���������� ����������
			{
				cerr << "���������� ����������\n";
				system("pause");
				break;
			}
			break;
		}
		case 3:
		{
			system("CLS");
			cout << "3:\n";
			try
			{
				if (data.getRoot())    //���� ������ �� ������
				{
					show(data);    //����� ������ � ���� �������
				}
				else 
					throw Myexception("��� ���������� ��� �����������");    //����� ����� ����������
			}
			catch (Myexception& obj)    //��������� �������������� ��������
			{
				cerr << "����������: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //���������� ����������
			{
				cerr << "���������� ����������\n";
				system("pause");
				break;
			}
			break;
		}
		case 4:
		{
			try
			{
				system("CLS");
				if (data.getRoot())    //���� ������ �� ������
				{
					int i;    //���������� ��� ������
					cout << "�� ������������� ������ ������� ������?" << endl;
					cout << "1. ��" << endl;
					cout << "0. ���" << endl;
					inputNum(cin,i, 0, 1);    //���������� ����
					if (!i)
					{
						system("CLS");
						break;
					}
					cout << "\n������ ���� ����������\n";
					data.destroyTree(data.getRoot());    //�������� ������
				}
				else
					throw Myexception("��� ���������� ��� ��������");
			}
			catch (Myexception& obj)    //��������� �������������� ��������
			{
				cerr << "����������: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //���������� ����������
			{
				cerr << "���������� ����������\n";
				system("pause");
				break;
			}
			break;
		}
		case 5:
		{
			system("CLS");
			try
			{
				cout << "5:" << endl;
				int j;    //���������� ��� ������ ����������� �������
				if (!data.empty())    //���� ������ �� �����
				{
					cout << "������� " << Name(tmp) << endl;
					makeTable(data.begin(), data.end());    //������� �������
				}
				else
					throw Myexception("��� ������ ��� ������");
				cout << "\n�������� ����� , ������� ������ ��������:";
				inputNum(cin,j, 1, data.size());    //���������� ����
				typename Tree<T>::iterator it, beg;
				Tree<T> tempo;    //��������� ������
				it = data.begin();    //������������� �������� �� ������ ������ ������
				for (; j > 1; j--)
					++it;    //������� ����������� �������
				stCode.push(3);    //������� � ���� ��������� 3
				stItem.push(*it);    //������� ��������� ������� � ����

				tempo.insert(*it);    //��������� ������� �� ��������� ������
				data.pop(*it);    //������� ��������� ������� �� ������ ������
				beg = tempo.begin();    //������������� �������� �� ���������� �������

				change(tempo,beg);    //�������� ��������� ���� � ���������� ��������

				stItem.push(*beg);    //��������� ���������� ������� � ���� ���������
				data.insert(*beg);    //��������� ���������� ������� � �������� ������
				system("CLS");
			}
			catch (Myexception& obj)    //��������� �������������� ��������
			{
				cerr << "����������: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //���������� ����������
			{
				cerr << "���������� ����������\n";
				system("pause");
				break;
			}
			break;
		}
		case 6:
		{
			system("CLS");
			try
			{
				if (stCode.empty())   //���� ���� ��������� ����
					throw Myexception("���� ������ ����");   //����� ����������
				undo(data, stItem, stCode);   //����� ������ ���������� ��������
			}
			catch (Myexception& obj)    //��������� �������������� ��������
			{
				cerr << "����������: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //���������� ����������
			{
				cerr << "���������� ����������\n";
				system("pause");
				break;
			}
			break;
		}
		case 7: 
		{
			system("CLS");
			try
			{
				cout<<"7:"<<endl;
				search(data);   //����� ������ � ������
			}
			catch (Myexception& mex)    //��������� �������������� ��������
			{
				system("CLS");
				cerr << "Error:" << mex.what() << "\n" << endl;
				system("pause");
				break;
			}
			catch (...)    //���������� ����������
			{
				cerr << "Unexpected";
				rewind(stdin);
				system("pause");
			}
			break;
		}
		case 8: {
			saveResult();    //���������� ������ ������ � ����
			system("CLS");
			return true;    //������� � ������� ����
		}
		case 0: {
			saveResult();    //���������� ������ ������ � ����
			system("CLS");
			return false;    //����� �� ���������
		}
		default:
		{
			cout << "\n������������ �����, ���������� �����" << endl;
			system("pause");
			break;
		}
		}
	} while (ans);
	return true;
}
