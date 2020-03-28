#pragma once
#include <iostream>
#include"Inputexception.h"
#include "Currency.h"

using namespace std;

class Account   // ����� �����
{
protected:
	double sum;   //���� �����
	Currency currency;   //��������� ������� currnecy ������ Currency
	string filePath;   //���� ���� �����
public:
	Account() :sum(0.0),currency(""),filePath("") {}
	Account(string _crnc, string _filePath="",double _sum=0.0):filePath(_filePath),currency(_crnc),sum(_sum) {}

	double getSum() const { return sum; }   //���������� �����
	Currency getCrnc() const { return currency; }   //���������� ������
	string getPath() const { return filePath; }   //���������� ���� � �����

	void setCrnc(Currency _crnc) { currency =_crnc; }   //������������� ������
	void setCrncName(string _name) { currency.setName(_name); }   //������������� ��� ������
	void setSum(double _sum) { sum = _sum; }   //������������� �����

	friend istream& operator >>(istream& is, Account& obj);   //�������� ����� �����
	friend ostream& operator << (ostream& out, Account& obj);   //�������� ������ �����

	virtual ~Account();   //����������

	bool operator==(const Account& obj)const;   //�������� ����� ���������� �����
	bool operator!=(const Account& obj)const;   //�������� �� �����
	bool operator>(const Account& obj)const;   //�������� ������(�� �����)
	bool operator<(const Account& obj)const;   //��������  ������

	virtual string createHeader() const;   //����� �������� ���������
	virtual string makeStr() const;   //����� �������� ������ ������ 
};

