#include "Currency.h"


bool Currency::operator==(const Currency & obj) const   //�������� ����� ���������� ��� ������
{
	return name == obj.name;
}

bool Currency::operator!=(const Currency & obj) const   //�������� �� �����
{
	return !((*this) == obj);
}

bool Currency::operator>(const Currency & obj) const   //�������� ������(�� ����� ������ � �����)
{
	if (*this == obj)
		return false;
	if (name > obj.name)
		return true;
	if (name == obj.name && rate > obj.rate)
		return true;
	return false;
}

bool Currency::operator<(const Currency & obj) const   //��������  ������
{
	if (*this == obj)
		return false;
	return !(*this > obj);
}

void Currency::prep(string str)   //����� ���������� ������ ��� �������� �� �����
{
	string tmp;
	int i = 0;
	while (str[i] != '|')   //���������� �� ��������������� �����
		tmp += str[i++];
	this->name = tmp;
	tmp = "";
	i++;
	while (str[i] != '\0')   //���������� �� ����� ������
		tmp += str[i++];
	this->rate = atof(tmp.c_str());   //��������� ��������� ��������� � ���� �����
}

string Currency::createHeader() const   //����� �������� ���������
{
	return "|��� ������     |����(1 ���.BYN)|";
}

string Currency::makeStr() const   //����� �������� ������ ������ 
{
	string tmp('|' + name);
	for (unsigned i = 0; i < (15 - name.length()); i++)
		tmp += ' ';   //���������� ������ ���������
	tmp += '|';
	tmp += to_string(rate);
	for (unsigned i = 0; i < (15 - (to_string(rate).length())); i++)
		tmp += ' ';   //���������� ������ ���������
	tmp += '|';
	return tmp;
}

string Currency::createHeaderA() const   //�������� ��������� ��� �� �������� ������
{
	return "������         |";
}

string Currency::makeStrA() const   //�������� ������ ��� �� �������� ������
{
	string tmp(name);
	for (unsigned i = 0; i < (15 - name.length()); i++)
		tmp += ' ';   //���������� ������ ���������
	tmp += '|';
	return tmp;
}

istream & operator>>(istream & is, Currency & obj)   //�������� ����� ������
{
	cout << "���\n";
	obj.name = inputCurr(is, 3);
	cout << "���� ������������ 1 BYN\n";
	inputNum(obj.rate);
	return is;
}

ostream & operator<<(ostream & out, Currency & obj)   //�������� ������ ������
{
	out << obj.name;
	out << '|';
	out <<obj.rate;
	return out;
}
