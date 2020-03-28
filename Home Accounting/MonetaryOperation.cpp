#include "MonetaryOperation.h"



MonetaryOperation::~MonetaryOperation()   //����������
{
}

bool MonetaryOperation::operator==(const MonetaryOperation & obj) const   //�������� �����
{
	return dynamic_cast<const Account&>(*this) == dynamic_cast<const Account&>(obj)&&category == obj.category;
}

bool MonetaryOperation::operator!=(const MonetaryOperation & obj) const   //�������� �� �����
{
	return !(*this == obj);
}

bool MonetaryOperation::operator>(const MonetaryOperation & obj) const   //��������� ������ 
{
	if (*this == obj)
		return false;
	if (category > obj.category)   //���� ��������� ������
		return true;               //������� - ������
	if (category == obj.category)   //���� ��������� �����  - ��������� �� ����� ��������
		return (dynamic_cast<const Account&>(*this) > dynamic_cast<const Account&>(obj));
	return false; 
}

bool MonetaryOperation::operator<(const MonetaryOperation & obj) const   //�������� ������
{
	if (*this == obj)
		return false;
	return !(*this > obj);
}


string MonetaryOperation::createHeader() const   //����� �������� ���������
{
	return Account::createHeader() + "���������      |";
}

string MonetaryOperation::makeStr() const   //����� �������� ������ ��� �������
{
	string tmp("");
	tmp += Account::makeStr();
	tmp += category;
	for (unsigned i = 0; i < (15 - category.length()); i++)
		tmp += ' ';   //���������� ������ ���������
	tmp += '|';
	return tmp;
}

istream & operator>>(istream & is, MonetaryOperation & obj)   //��������� �����
{
	is >> dynamic_cast<Account&>(obj);   //���� ������������ �����
	cout << "���������\n";
	obj.category=inputStr(is, 25);   //���� ������ ���������
	return is;
}

ostream & operator<<(ostream & out, MonetaryOperation & obj)   //�������� ������
{
	out << dynamic_cast<Account&>(obj);   //����� ������������ �����
	out << '|';   //����� ��������������� �����
	out << obj.category;   //����� ���������
	return out;
}
