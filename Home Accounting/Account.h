#pragma once
#include <iostream>
#include"Inputexception.h"
#include "Currency.h"

using namespace std;

class Account   // класс счёта
{
protected:
	double sum;   //поле суммы
	Currency currency;   //агрегация обьекта currnecy класса Currency
	string filePath;   //поле типа файла
public:
	Account() :sum(0.0),currency(""),filePath("") {}
	Account(string _crnc, string _filePath="",double _sum=0.0):filePath(_filePath),currency(_crnc),sum(_sum) {}

	double getSum() const { return sum; }   //возвращает сумму
	Currency getCrnc() const { return currency; }   //возвращает валюту
	string getPath() const { return filePath; }   //возвращает путь к файлу

	void setCrnc(Currency _crnc) { currency =_crnc; }   //устанавливает валюту
	void setCrncName(string _name) { currency.setName(_name); }   //устанавливает имя валюты
	void setSum(double _sum) { sum = _sum; }   //устанавливает сумму

	friend istream& operator >>(istream& is, Account& obj);   //оператор ввода счёта
	friend ostream& operator << (ostream& out, Account& obj);   //оператор вывода счёта

	virtual ~Account();   //деструктор

	bool operator==(const Account& obj)const;   //оператор равно сравнивает сумму
	bool operator!=(const Account& obj)const;   //оператор не равно
	bool operator>(const Account& obj)const;   //оператор больше(по сумме)
	bool operator<(const Account& obj)const;   //оператор  меньше

	virtual string createHeader() const;   //метод создания заголовка
	virtual string makeStr() const;   //метод создания строки данных 
};

