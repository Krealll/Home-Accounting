#include "Account.h"


Account::~Account()   //����������
{
}

bool Account::operator==(const Account & obj) const   //�������� ����� ���������� �����
{
	return sum == obj.sum;
}

bool Account::operator!=(const Account & obj) const   //�������� �� �����
{
	return sum != obj.sum;
}

bool Account::operator>(const Account & obj) const   //�������� ������(�� �����)
{
	return sum > obj.sum;
}

bool Account::operator<(const Account & obj) const   //��������  ������
{
	return sum < obj.sum;
}

string Account::createHeader() const   //����� �������� ���������
{
	return "|�����          |" + currency.createHeaderA();
}

string Account::makeStr() const	   //����� �������� ������ ������ 
{
	int i(4);
	string tmp('|' + to_string(sum));
	while (i--)
		tmp.pop_back();
	for (unsigned i = 0; i < (15 - (to_string(sum).length()-4)); i++)
		tmp += ' ';   //���������� ������ ���������
	tmp += '|';
	tmp += currency.makeStrA();   //������ ������ ������ ��� ������ �����
	return tmp;
}

istream & operator>>(istream & is, Account & obj)   //�������� �����
{
	cout << "�����:\n";
	inputNum(obj.sum);
	obj.sum = setDouble(obj.sum);
	return is;
}

ostream & operator<<(ostream & out, Account & obj)   //�������� ������ �����
{
	out.precision(2);
	out<<fixed<< obj.sum;
	out << "|";
	out << obj.currency.getName();
	return out;
}
