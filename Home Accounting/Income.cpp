#include "Income.h"


void Income::prep(string str)   //����� ���������� ������ ��� �������� �� �����
{
	string tmp;
	int i = 0;
	while (str[i] != '|')   //���������� �� ��������������� �����
		tmp += str[i++];
	this->sum = atof(tmp.c_str());   //�������������� ��������� ������ � double
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

bool Income::operator==(const Income & obj) const   //�������� ����� ���������� ��������� � �����
{
	return static_cast<const MonetaryOperation&>(*this) == static_cast<const MonetaryOperation&>(obj);
}
bool Income::operator!=(const Income & obj) const   //�������� �� �����
{
	return !(*this == obj);
}

bool Income::operator>(const Income & obj) const   //�������� ������(��������� �� ��������� � �����)
{
	return (static_cast<const MonetaryOperation&>(*this) > static_cast<const MonetaryOperation&>(obj));
}

bool Income::operator<(const Income & obj) const   //��������  ������
{
	if (*this == obj)
		return false;
	return!(*this > obj);
}


string Income::createHeader() const   //����� �������� ���������
{
	return MonetaryOperation::createHeader();
}

string Income::makeStr() const   //����� �������� ������ ������ 
{
	string tmp(MonetaryOperation::makeStr());    //����� ������������� ������
	return tmp;
}

istream & operator>>(istream & is, Income & obj)   //�������� ����� ������
{
	is >> dynamic_cast<MonetaryOperation&>(obj);

	return is;
}

ostream & operator<<(ostream & out, Income & obj)   //�������� ������ 
{
	out << dynamic_cast<MonetaryOperation&>(obj);
	return out;
}
