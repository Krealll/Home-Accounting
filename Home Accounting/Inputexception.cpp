#include "Inputexception.h"

bool isDigit(char c)   //проверка на число
{
	return (c > '0' && c < '9') ? true : false;
}

bool isSpace(char c)   //проверка на пробел
{
	return (c==' ') ? true : false;
}

bool isRus(char c)   //проверка на кириллицу
{
	if (c > -65 && c < 0||c=='ё'||c=='Ё')
		return true;
	else 
		return false;
}

bool isEng(char c)   //проверка на латиницу
{
	return ((c > 'A' && c < 'Z')||(c>'a'&&c<'z')) ? true : false;
}

bool isUpper(char c)   //проверка на верхний регистр латиницы
{
	 if (c > 64 && c < 91)
		return true;
	else return false;
}

Inputexception::~Inputexception()   //деструктор
{
}

int Inputexception::getCode()   //метод возврата кода ошибки
{
	return exCode;
}

double setDouble(double d)   //функция округления до сотых
{
	double temp = round(d * 100);
	return temp / 100;
}
