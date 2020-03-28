#pragma once
#include "Account.h"

class MonetaryOperation :   //класс денежных операций
	public Account
{
protected:
	string category;   //строка категории
public:
	MonetaryOperation() :Account("",""), category("") {}
	MonetaryOperation(string _crnc="", string _filePath = "", string _category="", double _sum=0.0) :Account(_crnc,_filePath,_sum), category(_category) {}

	string getCategory() const{ return category; }   //возврат категории

	void setCategory(string _category) { category = _category; }   //установка категории

	friend istream& operator >> (istream& is, MonetaryOperation& obj);   //ввод денежной опреации
	friend ostream& operator << (ostream& out, MonetaryOperation& obj);   //вывод денежной опреации
	~MonetaryOperation();

	bool operator==(const MonetaryOperation& obj)const;   //опреатор равно сравнивает категории и сумму
	bool operator!=(const MonetaryOperation& obj)const;   //оператор не равно
	bool operator> (const MonetaryOperation& obj)const;   //опрератор больше по категории 
													      // и по сумме
	bool operator<(const MonetaryOperation& obj)const;    //опреатор меньше

	virtual string createHeader() const;   //метод создания заголовка 
	virtual string makeStr() const;   //метод вывода данных для таблицы
};

