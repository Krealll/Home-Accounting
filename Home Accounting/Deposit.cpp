#include "Deposit.h"


void Deposit::prep(string str)   //����� ���������� ������ ��� �������� �� �����
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
	while (str[i] != '|')   //���������� �� ��������������� �����
		tmp += str[i++];
	this->perc = atol(tmp.c_str());   //��������� ��������� ��������� � ���� ��������
	i++;
	tmp = "";
	while (str[i] != '\0')
		tmp += str[i++];
	this->type = tmp;   //��������� ��������� ��������� � ���� ����
}

bool Deposit::operator==(const Deposit & obj) const   //�������� ����� ���������� ���, ������� � �����
{
	return dynamic_cast<const Account&>(*this) == dynamic_cast<const Account&>(obj) &&
		perc == obj.perc&&type == obj.type;
}

bool Deposit::operator!=(const Deposit & obj) const   //�������� �� �����
{
	return !(*this == obj);
}

bool Deposit::operator>(const Deposit & obj) const   //�������� ������
													//(��������� �� ��������,���� � �����)
{
	if (*this == obj)
		return false;
	if (perc > obj.perc)
		return true;
	if (perc == obj.perc &&type > obj.type)
		return true;
	else if (type == obj.type)
		return (dynamic_cast<const Account&>(*this) > dynamic_cast<const Account&>(obj));
	return false;
}

bool Deposit::operator<(const Deposit & obj) const   //��������  ������
{
	if (*this == obj)
		return false;
	return !(*this > obj);
}

string Deposit::createHeader() const   //����� �������� ���������
{
	return Account::createHeader() + "�������        |���            |";
}

string Deposit::makeStr() const   //����� �������� ������ ������ 
{

	string tmp("");
	tmp += Account::makeStr();   //����� ������������� ������  
	tmp += to_string(perc);
	for (unsigned i = 0; i < (15 - to_string(perc).length()); i++)
		tmp += ' ';   //���������� ������ ���������
	tmp += '|';
	tmp += type;
	for (unsigned i = 0; i < (15 - type.length()); i++)
		tmp += ' ';   //���������� ������ ���������
	tmp += '|';
	return tmp;
}

istream & operator>>(istream & is, Deposit & obj)   //�������� �����
{
	is >> dynamic_cast<Account&>(obj);
	cout << "�������\n";
	inputNum(is,obj.perc,0,100);
	obj.type=inputType();
	return is;
}

ostream & operator<<(ostream & out, Deposit & obj)   //�������� ������ ������ 
{
	out << dynamic_cast<Account&>(obj);
	out << '|';
	out << obj.perc;
	out << '|';
	out << obj.type;
	return out;
}
