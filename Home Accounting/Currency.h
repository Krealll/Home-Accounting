#pragma once
#include <iostream>
#include"Inputexception.h"
using namespace std;

class Currency   //класс валюты
{
protected:
	string filePath{ "..\\Files\\currency.txt" };   //поле путя файла
	string name;   //поле имени валюты
	double rate;   //поле курса валюты
public:
	Currency() = default;
	Currency(string _name,double _rate=0.0) :name(_name),rate(_rate) {}

	string getName() const { return name; }   //возвращает имя валюты
	string getPath() { return filePath; }   //возвращает путь к файлу
	double getRate() const { return rate; }   //возвращает курс

	void setName(string _name) { name = _name; }   //устанавливает имя
	void setRate(double _rate) { rate = _rate; }   //устанавливает курс

	bool operator==(const Currency& obj)const;   //оператор равно сравнивает имя валюты
	bool operator!=(const Currency& obj)const;   //оператор не равно
	bool operator>(const Currency& obj)const;   //оператор больше(по имени валюты и курсу)
	bool operator<(const Currency& obj)const;   //оператор  меньше


	friend istream& operator >>(istream& is, Currency& obj);   //оператор ввода валюты
	friend ostream& operator << (ostream& out, Currency& obj);   //оператор вывода валюты

	void prep(string str);   //метод подготовки строки для загрузки из файла

	 string createHeader() const;   //метод создания заголовка
	string makeStr() const;   //метод создания строки данных 
	string createHeaderA() const;   //создание заголовка для не валютных таблиц
	string makeStrA() const;   //создание строки для не валютных таблиц
	~Currency() = default;   //деструктор
};