#pragma once
#include <iostream>
#include"Inputexception.h"
using namespace std;

class Currency   //����� ������
{
protected:
	string filePath{ "..\\Files\\currency.txt" };   //���� ���� �����
	string name;   //���� ����� ������
	double rate;   //���� ����� ������
public:
	Currency() = default;
	Currency(string _name,double _rate=0.0) :name(_name),rate(_rate) {}

	string getName() const { return name; }   //���������� ��� ������
	string getPath() { return filePath; }   //���������� ���� � �����
	double getRate() const { return rate; }   //���������� ����

	void setName(string _name) { name = _name; }   //������������� ���
	void setRate(double _rate) { rate = _rate; }   //������������� ����

	bool operator==(const Currency& obj)const;   //�������� ����� ���������� ��� ������
	bool operator!=(const Currency& obj)const;   //�������� �� �����
	bool operator>(const Currency& obj)const;   //�������� ������(�� ����� ������ � �����)
	bool operator<(const Currency& obj)const;   //��������  ������


	friend istream& operator >>(istream& is, Currency& obj);   //�������� ����� ������
	friend ostream& operator << (ostream& out, Currency& obj);   //�������� ������ ������

	void prep(string str);   //����� ���������� ������ ��� �������� �� �����

	 string createHeader() const;   //����� �������� ���������
	string makeStr() const;   //����� �������� ������ ������ 
	string createHeaderA() const;   //�������� ��������� ��� �� �������� ������
	string makeStrA() const;   //�������� ������ ��� �� �������� ������
	~Currency() = default;   //����������
};