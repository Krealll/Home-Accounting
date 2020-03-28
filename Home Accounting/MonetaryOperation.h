#pragma once
#include "Account.h"

class MonetaryOperation :   //����� �������� ��������
	public Account
{
protected:
	string category;   //������ ���������
public:
	MonetaryOperation() :Account("",""), category("") {}
	MonetaryOperation(string _crnc="", string _filePath = "", string _category="", double _sum=0.0) :Account(_crnc,_filePath,_sum), category(_category) {}

	string getCategory() const{ return category; }   //������� ���������

	void setCategory(string _category) { category = _category; }   //��������� ���������

	friend istream& operator >> (istream& is, MonetaryOperation& obj);   //���� �������� ��������
	friend ostream& operator << (ostream& out, MonetaryOperation& obj);   //����� �������� ��������
	~MonetaryOperation();

	bool operator==(const MonetaryOperation& obj)const;   //�������� ����� ���������� ��������� � �����
	bool operator!=(const MonetaryOperation& obj)const;   //�������� �� �����
	bool operator> (const MonetaryOperation& obj)const;   //��������� ������ �� ��������� 
													      // � �� �����
	bool operator<(const MonetaryOperation& obj)const;    //�������� ������

	virtual string createHeader() const;   //����� �������� ��������� 
	virtual string makeStr() const;   //����� ������ ������ ��� �������
};

