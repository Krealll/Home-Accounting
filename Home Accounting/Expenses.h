#pragma once
#include "MonetaryOperation.h"
class Expenses :   //класс расходов
	public MonetaryOperation
{
public:
	Expenses() :MonetaryOperation("",""){}
	Expenses(string _crnc,string _filePath="..\\Files\\expenses.txt",string _category="" , double _sum =0.0) : MonetaryOperation(_crnc,_filePath,_category, _sum) {}

	friend istream& operator >> (istream& is, Expenses& obj);   //оператор ввода расхода
	friend ostream& operator << (ostream& out, Expenses& obj);   //оператор вывода расхода

	void prep(string str);   //метод подготовки строки для загрузки из файла

	~Expenses() = default;   //деструктор


	bool operator==(const Expenses& obj)const;   //оператор равно сравнивает категории и сумму
	bool operator!=(const Expenses& obj)const;   //оператор не равно
	bool operator>(const Expenses& obj)const;   //оператор больше(сравнение по категории и сумме)
	bool operator<(const Expenses& obj)const;   //оператор  меньше

	virtual string createHeader() const;   //метод создания заголовка
	virtual string makeStr() const;   //метод создания строки данных 
};

