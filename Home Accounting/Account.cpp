#include "Account.h"


Account::~Account()   //деструктор
{
}

bool Account::operator==(const Account & obj) const   //оператор равно сравнивает сумму
{
	return sum == obj.sum;
}

bool Account::operator!=(const Account & obj) const   //оператор не равно
{
	return sum != obj.sum;
}

bool Account::operator>(const Account & obj) const   //оператор больше(по сумме)
{
	return sum > obj.sum;
}

bool Account::operator<(const Account & obj) const   //оператор  меньше
{
	return sum < obj.sum;
}

string Account::createHeader() const   //метод создания заголовка
{
	return "|Сумма          |" + currency.createHeaderA();
}

string Account::makeStr() const	   //метод создания строки данных 
{
	int i(4);
	string tmp('|' + to_string(sum));
	while (i--)
		tmp.pop_back();
	for (unsigned i = 0; i < (15 - (to_string(sum).length()-4)); i++)
		tmp += ' ';   //заполнение строки пробелами
	tmp += '|';
	tmp += currency.makeStrA();   //метода класса валюты для вывода имени
	return tmp;
}

istream & operator>>(istream & is, Account & obj)   //оператор ввода
{
	cout << "Сумма:\n";
	inputNum(obj.sum);
	obj.sum = setDouble(obj.sum);
	return is;
}

ostream & operator<<(ostream & out, Account & obj)   //оператор вывода счёта
{
	out.precision(2);
	out<<fixed<< obj.sum;
	out << "|";
	out << obj.currency.getName();
	return out;
}
