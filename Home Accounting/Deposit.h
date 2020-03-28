#pragma once
#include "Account.h"
class Deposit :   //����� �������
	public Account
{
protected:
	int  perc;   //���� ��������
	string type;   //���� ����
public:
	Deposit() :Account("","..\\Files\\deposit.txt"), perc(0), type("") {}
	Deposit(string _crnc, string _filePath="..\\Files\\deposit.txt",int _perc=0, string _type="", double _sum=0.0) :Account(_crnc, _filePath, _sum), perc(_perc), type(_type) {}

	double getPercent() const { return perc; }   //��������� �������
	string getType() const { return type; }   //��������� ���

	void setType(string _type) { type = _type; }   //������������� ���
	void setPercent(long _perc) { perc = _perc; }   //������������� �������

	friend istream& operator >> (istream& is, Deposit& obj);   //�������� ����� ������
	friend ostream& operator << (ostream& out, Deposit& obj);   //�������� ������ ������

	void prep(string str);   //����� ���������� ������ ��� �������� �� �����

	~Deposit() = default;   //����������

	bool operator==(const Deposit& obj)const;   //�������� ����� ���������� ���, ������� � �����
	bool operator!=(const Deposit& obj)const;   //�������� �� �����
	bool operator>(const Deposit& obj)const;   //�������� ������(��������� �� ��������,���� � �����)
	bool operator<(const Deposit& obj)const;   //��������  ������

	virtual string createHeader() const;   //����� �������� ���������
	virtual string makeStr() const;   //����� �������� ������ ������ 
};
