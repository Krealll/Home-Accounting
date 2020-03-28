#include "Deposit.h"


void Deposit::prep(string str)   //метод подготовки строки дл€ загрузки из файла
{
	string tmp;
	int i = 0;
	while (str[i] != '|')   //считывание до разделительного знака
		tmp += str[i++];
	this->sum = atof(tmp.c_str());   //установка считанной подстроки в поле суммы
	tmp = "";
	i++;
	while (str[i] != '|')   //считывание до разделительного знака
		tmp += str[i++];
	this->currency.setName(tmp);   //установка считанной подстроки в поле имени валюты
	tmp = "";
	i++;
	while (str[i] != '|')   //считывание до разделительного знака
		tmp += str[i++];
	this->perc = atol(tmp.c_str());   //установка считанной подстроки в поле процента
	i++;
	tmp = "";
	while (str[i] != '\0')
		tmp += str[i++];
	this->type = tmp;   //установка считанной подстроки в поле типа
}

bool Deposit::operator==(const Deposit & obj) const   //оператор равно сравнивает тип, процент и сумму
{
	return dynamic_cast<const Account&>(*this) == dynamic_cast<const Account&>(obj) &&
		perc == obj.perc&&type == obj.type;
}

bool Deposit::operator!=(const Deposit & obj) const   //оператор не равно
{
	return !(*this == obj);
}

bool Deposit::operator>(const Deposit & obj) const   //оператор больше
													//(сравнение по проценту,типу и сумме)
{
	if (*this == obj)
		return false;
	if (perc > obj.perc)
		return true;
	if (perc == obj.perc &&type > obj.type)
		return true;
	else if (type == obj.type)
		return (dynamic_cast<const Account&>(*this) > dynamic_cast<const Account&>(obj));
	return false;
}

bool Deposit::operator<(const Deposit & obj) const   //оператор  меньше
{
	if (*this == obj)
		return false;
	return !(*this > obj);
}

string Deposit::createHeader() const   //метод создани€ заголовка
{
	return Account::createHeader() + "ѕроцент        |“ип            |";
}

string Deposit::makeStr() const   //метод создани€ строки данных 
{

	string tmp("");
	tmp += Account::makeStr();   //вызов родительского метода  
	tmp += to_string(perc);
	for (unsigned i = 0; i < (15 - to_string(perc).length()); i++)
		tmp += ' ';   //заполнение строки пробелами
	tmp += '|';
	tmp += type;
	for (unsigned i = 0; i < (15 - type.length()); i++)
		tmp += ' ';   //заполнение строки пробелами
	tmp += '|';
	return tmp;
}

istream & operator>>(istream & is, Deposit & obj)   //оператор ввода
{
	is >> dynamic_cast<Account&>(obj);
	cout << "ѕроцент\n";
	inputNum(is,obj.perc,0,100);
	obj.type=inputType();
	return is;
}

ostream & operator<<(ostream & out, Deposit & obj)   //оператор вывода вклада 
{
	out << dynamic_cast<Account&>(obj);
	out << '|';
	out << obj.perc;
	out << '|';
	out << obj.type;
	return out;
}
