#pragma once
#include "MonetaryOperation.h"

class Income :   //����� �������
	public MonetaryOperation
{
public:
	Income() :MonetaryOperation("") {}
	Income(string crnc,string _filePath="..\\Files\\income.txt", string _category = "", double _sum = 0.0) : MonetaryOperation(crnc,_filePath, _category, _sum) {}

	friend istream& operator >> (istream& is, Income& obj);   //�������� ����� ������
	friend ostream& operator << (ostream& out, Income& obj);   //�������� ������ ������

	void prep(string str);   //����� ���������� ������ ��� �������� �� �����

	~Income() = default;   //����������

	bool operator==(const Income& obj)const;   //�������� ����� ���������� ��������� � �����
	bool operator!=(const Income& obj)const;   //�������� �� �����
	bool operator>(const Income& obj)const;   //�������� ������(��������� �� ��������� � �����)
	bool operator<(const Income& obj)const;   //��������  ������
	   
	virtual string createHeader() const;   //����� �������� ���������
	virtual string makeStr() const;   //����� �������� ������ ������ 
};
