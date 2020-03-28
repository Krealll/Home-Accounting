#include "Expenses.h"


void Expenses::prep(string str)   //����� ���������� ������ ��� �������� �� �����
{
	string tmp;
	int i = 0;
	while (str[i] != '|')   //���������� �� ��������������� �����
		tmp += str[i++];
	this->sum = atof(tmp.c_str());   //��������� ��������� ��������� � ���� �����
	tmp = "";
	i++;
	while (str[i] != '|')   //���������� �� ��������������� �����
		tmp += str[i++];
	this->currency.setName(tmp);   //��������� ��������� ��������� � ���� ����� ������
	tmp = "";
	i++;
	while (str[i] != '\0')  
		tmp += str[i++];
	this->category = tmp;   //��������� ��������� ��������� � ���� ���������
}

bool Expenses::operator==(const Expenses & obj) const   //�������� ����� ���������� ��������� � �����
{
	return static_cast<const MonetaryOperation&>(*this) == static_cast<const MonetaryOperation&>(obj);
}
bool Expenses::operator!=(const Expenses & obj) const   //�������� �� �����
{
	return !(*this == obj);
}

bool Expenses::operator>(const Expenses & obj) const   //�������� ������(��������� �� ��������� � �����)
{
	return (static_cast<const MonetaryOperation&>(*this) > static_cast<const MonetaryOperation&>(obj));
}

bool Expenses::operator<(const Expenses & obj) const   //��������  ������
{
	if (*this == obj)
		return false;
	return!(*this > obj);
}

string Expenses::createHeader() const   //����� �������� ���������
{
	return MonetaryOperation::createHeader();
}

string Expenses::makeStr() const   //����� �������� ������ ������ 
{
	string tmp(MonetaryOperation::makeStr());   //����� ������������� ������
	return tmp;
}

istream & operator>>(istream & is, Expenses & obj)   //�������� �����
{
	is >> dynamic_cast<MonetaryOperation&>(obj);
	return is;
}

ostream & operator<<(ostream & out, Expenses & obj)   //�������� ������ �������
{
	out << dynamic_cast<MonetaryOperation&>(obj);
	return out;
}
