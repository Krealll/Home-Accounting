#include "algorithm.h"

typedef list<string>::iterator iter;
list<string>::iterator findS(list<string>& temp, iter it)   //����� � ����� �� ���������
{
	list<string>::iterator itt = temp.begin();
	for (; itt != temp.end(); ++itt)
		if (*itt == *it)   //���� ������ ����� �� ������� ��������� �����
			break;
	return itt;
}

void changeCurrObj(Tree<Currency>::iterator it)   //������� ��������� ������
{
	list<string> temp = chooseFields(*it);   //����� ����� ��� ���������
	changeCurrFields(it, temp);   //��������� �����
	system("CLS");
	cout << "���� ������� ��������" << endl;
	system("pause");
}


void changeCurrFields(typename Tree<Currency>::iterator it, list<string> tempList)   //������� ���������
																				     //����� ������
{
	system("CLS");
	cout << "��������� ���� �������" << endl;
	if (find(tempList.begin(), tempList.end(), "��� ������     ") != tempList.end())   //���� ���� ������� ��� 
	{
		string temp;
		cout << "������� �������� ����� ������" << endl;
		temp = inputCurr(cin, 3);   //���� ������ �������� ���� 
		(*it).setName(temp);   //��������� ����
	}
	if (find(tempList.begin(), tempList.end(), "����(1 ���.BYN)") != tempList.end())   //���� ��� ������ ����
	{
		double temp;
		cout << "������� ���� ����� ������" << endl;
		input(cin, temp);   //���� ������ �������� ���� 
		(*it).setRate(temp);   //��������� ����
	}
}

void findCurr(Tree<Currency>& tree)   //������� ��� ������ ������
{
	Currency obj;   //��������� ������ ��� ������
	stack<Currency> res;   //���� ����������� ������
	try
	{
		if (!tree.getRoot())
			throw Myexception("Can't find element in empty tree");
		comparator comp(chooseFields(obj));   //����� ����� ��� ������
		setObjCurr(comp.getCompFields(), obj);   //��������� ����� ��� ���������
		typename Tree<Currency>::iterator iter;
		iter = tree.begin();
		for (; iter != tree.end(); ++iter)   //�������� �� ������
		{
			if (comp(obj, *iter))   //����� ����� ����� �� ������
				res.push(*iter);   //������� � � ���� ����������
		}
		if (res.empty())
			throw Myexception("There are no such element");
	}
	catch (Myexception& mex)   //���������� ����������
	{
		throw mex;
	}
	catch (...)   //���������� ����������
	{
		cerr << "Unexpected behavior" << endl;
		return;
	}
	makeTable(res);   //����� ������� ��������� ������
}

void setObjCurr(list<string> tempList, Currency & obj)   //������� ��������� ����� �����
{
	system("CLS");
	cout << "��������� ���� �������" << endl;
	if (find(tempList.begin(), tempList.end(), "��� ������     ") != tempList.end())   //���� ������� ������
	{
		string temp;
		cout << "������� �������� ������� ������" << endl;
		temp = inputCurr(cin, 3);   //���� �������� ����
		obj.setName(temp);   //��������� ���� ��� ���������
	}
	if (find(tempList.begin(), tempList.end(), "����(1 ���.BYN)") != tempList.end())   //���� ������ ����
	{
		double temp;
		cout << "������� ���� ������� ������" << endl;
		input(cin, temp);   //���� �������� ����
		obj.setRate(temp);   //��������� ���� ��� ���������
	}
}

void setObj(list<string> tempList, Account & obj)   //������� ��������� ����� ��� ������ 
{
	system("CLS");
	cout << "��������� ���� �������" << endl;
	if (find(tempList.begin(), tempList.end(), "���������      ") != tempList.end())   //���� ������� ���������
	{
		string temp;
		cout << "������� ������� ���������" << endl;
		temp = inputStr(cin, 15);   //���� �������� ����
		dynamic_cast<MonetaryOperation&>(obj).setCategory(temp);   //��������� ���� ��� ���������
	}
	if (find(tempList.begin(), tempList.end(), "������         ") != tempList.end())   //���� ������� ������
	{
		string temp;
		cout << "������� �������� ������� ������" << endl;
		temp = inputCurr(cin, 3);   //���� �������� ����
		obj.setCrncName(temp);   //��������� ���� ��� ���������
	}
	if (find(tempList.begin(), tempList.end(), "�����          ") != tempList.end())   //���� ������� �����
	{
		double temp;
		cout << "������� ������� �����" << endl;
		input(cin, temp);   //���� �������� ����
		obj.setSum(temp);   //��������� ���� ��� ���������
	}
	if (find(tempList.begin(), tempList.end(), "���            ") != tempList.end())   //���� ������ ���
	{
		string temp;
		cout << "������� ������� ���" << endl;
		temp = inputType();   //���� �������� ����
		dynamic_cast<Deposit&>(obj).setType(temp);   //��������� ���� ��� ���������
	}
	if (find(tempList.begin(), tempList.end(), "�������        ") != tempList.end())   //���� ������ �������
	{
		int temp;
		cout << "������� ������� �������" << endl;
		inputNum(cin,temp,0,100);   //���� �������� ����
		dynamic_cast<Deposit&>(obj).setPercent(temp);   //��������� ���� ��� ���������
	}
}


double findRate(Currency curr, Tree<Currency>& tree)   //������� ��� ������ ����� ������
{
	double temp = 0.0;   //��������� ���������� ��� �������� �������� �����
	typename Tree <Currency>::iterator it;
	it = tree.begin();
	for (; it != tree.end(); ++it)   //������ � ������
		if (curr.getName() == (*it).getName())   //���� ������� ������ ��� ������
		{
			temp = (*it).getRate();   //���������� � ����
			break;
		}
	if (!temp)
		throw Myexception("������ ������. ��������� ������ ������");   //����� ����������
	return temp;
}

bool comparator::operator()(const Expenses & objr, const Expenses & objl)   //��������� ��������
{
	int counter{};   //���� ���� ��������� ����������� �������
	if (find(comparedFields.begin(), comparedFields.end(), "�����          ") != comparedFields.end())
		if (objr.getSum() == objl.getSum())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "������         ") != comparedFields.end())
		if (objr.getCrnc() == objl.getCrnc())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "���������      ") != comparedFields.end())
		if (objr.getCategory() == objl.getCategory())
			++counter;
	return counter == comparedFields.size();   //���� ���������� ��������� ����� ����� ��������, �� ������� �����
}

bool comparator::operator()(const Income & objr, const Income & objl)   //��������� �������
{
	int counter{};   //���� ���� ��������� ����������� �������
	if (find(comparedFields.begin(), comparedFields.end(), "�����          ") != comparedFields.end())
		if (objr.getSum() == objl.getSum())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "������         ") != comparedFields.end())
		if (objr.getCrnc() == objl.getCrnc())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "���������      ") != comparedFields.end())
		if (objr.getCategory() == objl.getCategory())
			++counter;
	return counter == comparedFields.size();   //���� ���������� ��������� ����� ����� ��������, �� ������� �����
}


bool comparator::operator()(const Deposit & objr, const Deposit & objl)   //��������� �������
{
	int counter{};   //���� ���� ��������� ����������� �������
	if (find(comparedFields.begin(), comparedFields.end(), "�����          ") != comparedFields.end())
		if (objr.getSum() == objl.getSum())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "������         ") != comparedFields.end())
		if (objr.getCrnc() == objl.getCrnc())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "�������        ") != comparedFields.end())
		if (objr.getPercent() == objl.getPercent())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "���            ") != comparedFields.end())
			if (objr.getType() == objl.getType())
				++counter;
	return counter == comparedFields.size();   //���� ���������� ��������� ����� ����� ��������, �� ������� �����
}

bool comparator::operator()(const Currency & objr, const Currency & objl)   //��������� �����
{
	int counter{};   //���� ���� ��������� ����������� �������
	if (find(comparedFields.begin(), comparedFields.end(), "��� ������     ") != comparedFields.end())
		if (objr.getName() == objl.getName())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "����(1 ���.BYN)") != comparedFields.end())
		if (objr.getRate() == objl.getRate())
			++counter;
	return counter == comparedFields.size();   //���� ���������� ��������� ����� ����� ��������, �� ������� �����
}
