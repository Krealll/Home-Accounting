#pragma once
#include <iostream>
#include <string>

using namespace std;

class Myexception   //базовый класс исключения
{
protected:
	string errorStr;   //строка ошибки
public:

	Myexception(string str) :errorStr(str) {};

	virtual ~Myexception();

	string& what();   //метод вывода строки ошибки

};
