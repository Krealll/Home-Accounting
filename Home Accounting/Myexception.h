#pragma once
#include <iostream>
#include <string>

using namespace std;

class Myexception   //������� ����� ����������
{
protected:
	string errorStr;   //������ ������
public:

	Myexception(string str) :errorStr(str) {};

	virtual ~Myexception();

	string& what();   //����� ������ ������ ������

};
