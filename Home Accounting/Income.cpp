#include "Income.h"


void Income::prep(string str)   //метод подготовки строки для загрузки из файла
{
	string tmp;
	int i = 0;
	while (str[i] != '|')   //считывание до разделительного знака
		tmp += str[i++];
	this->sum = atof(tmp.c_str());   //преобразование считанной строки в double
	tmp = "";
	i++;
	while (str[i] != '|')   //считывание до разделительного знака
		tmp += str[i++];
	this->currency.setName(tmp);   //установка считанной подстроки в поле имени валюты
	tmp = "";
	i++;
	while (str[i] != '\0')
		tmp += str[i++];
	this->category = tmp;   //установка считанной подстроки в поле категории
}

bool Income::operator==(const Income & obj) const   //оператор равно сравнивает категории и сумму
{
	return static_cast<const MonetaryOperation&>(*this) == static_cast<const MonetaryOperation&>(obj);
}
bool Income::operator!=(const Income & obj) const   //оператор не равно
{
	return !(*this == obj);
}

bool Income::operator>(const Income & obj) const   //оператор больше(сравнение по категории и сумме)
{
	return (static_cast<const MonetaryOperation&>(*this) > static_cast<const MonetaryOperation&>(obj));
}

bool Income::operator<(const Income & obj) const   //оператор  меньше
{
	if (*this == obj)
		return false;
	return!(*this > obj);
}


string Income::createHeader() const   //метод создания заголовка
{
	return MonetaryOperation::createHeader();
}

string Income::makeStr() const   //метод создания строки данных 
{
	string tmp(MonetaryOperation::makeStr());    //вызов родительского метода
	return tmp;
}

istream & operator>>(istream & is, Income & obj)   //оператор ввода дохода
{
	is >> dynamic_cast<MonetaryOperation&>(obj);

	return is;
}

ostream & operator<<(ostream & out, Income & obj)   //оператор вывода 
{
	out << dynamic_cast<MonetaryOperation&>(obj);
	return out;
}
