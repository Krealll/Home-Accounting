#pragma once
#include "MonetaryOperation.h"

class Income :   //класс доходов
	public MonetaryOperation
{
public:
	Income() :MonetaryOperation("") {}
	Income(string crnc,string _filePath="..\\Files\\income.txt", string _category = "", double _sum = 0.0) : MonetaryOperation(crnc,_filePath, _category, _sum) {}

	friend istream& operator >> (istream& is, Income& obj);   //оператор ввода дохода
	friend ostream& operator << (ostream& out, Income& obj);   //оператор вывода дохода

	void prep(string str);   //метод подготовки строки для загрузки из файла

	~Income() = default;   //деструктор

	bool operator==(const Income& obj)const;   //оператор равно сравнивает категории и сумму
	bool operator!=(const Income& obj)const;   //оператор не равно
	bool operator>(const Income& obj)const;   //оператор больше(сравнение по категории и сумме)
	bool operator<(const Income& obj)const;   //оператор  меньше
	   
	virtual string createHeader() const;   //метод создания заголовка
	virtual string makeStr() const;   //метод создания строки данных 
};
