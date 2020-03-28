#include "Currency.h"


bool Currency::operator==(const Currency & obj) const   //оператор равно сравнивает имя валюты
{
	return name == obj.name;
}

bool Currency::operator!=(const Currency & obj) const   //оператор не равно
{
	return !((*this) == obj);
}

bool Currency::operator>(const Currency & obj) const   //оператор больше(по имени валюты и курсу)
{
	if (*this == obj)
		return false;
	if (name > obj.name)
		return true;
	if (name == obj.name && rate > obj.rate)
		return true;
	return false;
}

bool Currency::operator<(const Currency & obj) const   //оператор  меньше
{
	if (*this == obj)
		return false;
	return !(*this > obj);
}

void Currency::prep(string str)   //метод подготовки строки для загрузки из файла
{
	string tmp;
	int i = 0;
	while (str[i] != '|')   //считывание до разделительного знака
		tmp += str[i++];
	this->name = tmp;
	tmp = "";
	i++;
	while (str[i] != '\0')   //считывание до конца строки
		tmp += str[i++];
	this->rate = atof(tmp.c_str());   //установка считанной подстроки в поле курса
}

string Currency::createHeader() const   //метод создания заголовка
{
	return "|Имя валюты     |Курс(1 отн.BYN)|";
}

string Currency::makeStr() const   //метод создания строки данных 
{
	string tmp('|' + name);
	for (unsigned i = 0; i < (15 - name.length()); i++)
		tmp += ' ';   //заполнение строки пробелами
	tmp += '|';
	tmp += to_string(rate);
	for (unsigned i = 0; i < (15 - (to_string(rate).length())); i++)
		tmp += ' ';   //заполнение строки пробелами
	tmp += '|';
	return tmp;
}

string Currency::createHeaderA() const   //создание заголовка для не валютных таблиц
{
	return "Валюта         |";
}

string Currency::makeStrA() const   //создание строки для не валютных таблиц
{
	string tmp(name);
	for (unsigned i = 0; i < (15 - name.length()); i++)
		tmp += ' ';   //заполнение строки пробелами
	tmp += '|';
	return tmp;
}

istream & operator>>(istream & is, Currency & obj)   //оператор ввода валюты
{
	cout << "Имя\n";
	obj.name = inputCurr(is, 3);
	cout << "Курс относительно 1 BYN\n";
	inputNum(obj.rate);
	return is;
}

ostream & operator<<(ostream & out, Currency & obj)   //оператор вывода валюты
{
	out << obj.name;
	out << '|';
	out <<obj.rate;
	return out;
}
