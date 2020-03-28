#pragma once
#include "Account.h"
class Deposit :   //класс вкладов
	public Account
{
protected:
	int  perc;   //поле процента
	string type;   //поле типа
public:
	Deposit() :Account("","..\\Files\\deposit.txt"), perc(0), type("") {}
	Deposit(string _crnc, string _filePath="..\\Files\\deposit.txt",int _perc=0, string _type="", double _sum=0.0) :Account(_crnc, _filePath, _sum), perc(_perc), type(_type) {}

	double getPercent() const { return perc; }   //возращает процент
	string getType() const { return type; }   //вовращает тип

	void setType(string _type) { type = _type; }   //устанавливает тип
	void setPercent(long _perc) { perc = _perc; }   //устанавливает процент

	friend istream& operator >> (istream& is, Deposit& obj);   //оператор ввода вклада
	friend ostream& operator << (ostream& out, Deposit& obj);   //оператор вывода вклада

	void prep(string str);   //метод подготовки строки для загрузки из файла

	~Deposit() = default;   //деструктор

	bool operator==(const Deposit& obj)const;   //оператор равно сравнивает тип, процент и сумму
	bool operator!=(const Deposit& obj)const;   //оператор не равно
	bool operator>(const Deposit& obj)const;   //оператор больше(сравнение по проценту,типу и сумме)
	bool operator<(const Deposit& obj)const;   //оператор  меньше

	virtual string createHeader() const;   //метод создания заголовка
	virtual string makeStr() const;   //метод создания строки данных 
};
