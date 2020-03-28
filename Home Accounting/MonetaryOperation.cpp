#include "MonetaryOperation.h"



MonetaryOperation::~MonetaryOperation()   //деструктор
{
}

bool MonetaryOperation::operator==(const MonetaryOperation & obj) const   //оператор равно
{
	return dynamic_cast<const Account&>(*this) == dynamic_cast<const Account&>(obj)&&category == obj.category;
}

bool MonetaryOperation::operator!=(const MonetaryOperation & obj) const   //оператор не равно
{
	return !(*this == obj);
}

bool MonetaryOperation::operator>(const MonetaryOperation & obj) const   //опрератор больше 
{
	if (*this == obj)
		return false;
	if (category > obj.category)   //если категория больше
		return true;               //возврат - правда
	if (category == obj.category)   //если категории равны  - сравнение по полям родителя
		return (dynamic_cast<const Account&>(*this) > dynamic_cast<const Account&>(obj));
	return false; 
}

bool MonetaryOperation::operator<(const MonetaryOperation & obj) const   //оператор меньше
{
	if (*this == obj)
		return false;
	return !(*this > obj);
}


string MonetaryOperation::createHeader() const   //метод создания заголовка
{
	return Account::createHeader() + "Категория      |";
}

string MonetaryOperation::makeStr() const   //метод создания строки для таблицы
{
	string tmp("");
	tmp += Account::makeStr();
	tmp += category;
	for (unsigned i = 0; i < (15 - category.length()); i++)
		tmp += ' ';   //заполнение строки пробелами
	tmp += '|';
	return tmp;
}

istream & operator>>(istream & is, MonetaryOperation & obj)   //опрератор ввода
{
	is >> dynamic_cast<Account&>(obj);   //ввод родительских полей
	cout << "Категория\n";
	obj.category=inputStr(is, 25);   //ввод строки категории
	return is;
}

ostream & operator<<(ostream & out, MonetaryOperation & obj)   //оператор вывода
{
	out << dynamic_cast<Account&>(obj);   //вывод родительских полей
	out << '|';   //вывод разделительного знака
	out << obj.category;   //вывод категории
	return out;
}
