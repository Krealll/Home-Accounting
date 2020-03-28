#pragma once
#include "MonetaryOperation.h"
class Expenses :   //����� ��������
	public MonetaryOperation
{
public:
	Expenses() :MonetaryOperation("",""){}
	Expenses(string _crnc,string _filePath="..\\Files\\expenses.txt",string _category="" , double _sum =0.0) : MonetaryOperation(_crnc,_filePath,_category, _sum) {}

	friend istream& operator >> (istream& is, Expenses& obj);   //�������� ����� �������
	friend ostream& operator << (ostream& out, Expenses& obj);   //�������� ������ �������

	void prep(string str);   //����� ���������� ������ ��� �������� �� �����

	~Expenses() = default;   //����������


	bool operator==(const Expenses& obj)const;   //�������� ����� ���������� ��������� � �����
	bool operator!=(const Expenses& obj)const;   //�������� �� �����
	bool operator>(const Expenses& obj)const;   //�������� ������(��������� �� ��������� � �����)
	bool operator<(const Expenses& obj)const;   //��������  ������

	virtual string createHeader() const;   //����� �������� ���������
	virtual string makeStr() const;   //����� �������� ������ ������ 
};

