#pragma once
#include "Myexception.h"
#include"Tree.h"


class Inputexception :   //класс исключений ввода
	public Myexception
{
protected:
	int exCode;   //поле кода ошибки
public:
	
	Inputexception(string str, int code) : Myexception(str), exCode(code) {};
	~Inputexception();
	int getCode();   //возвращает код ошибки

};

bool isDigit(char c);   //проверка на число
bool isSpace(char c);   //проверка на пробел
bool isRus(char c);   //проверка на кириллицу
bool isEng(char c);   //проверка на латиницу
bool isUpper(char c);   //проверка на латиницу верхнего регистра
double setDouble(double d);    //функция округления до сотых

template<typename T>
void input(std::istream& in, T& obj)   //шаблонная функция безопасного ввода 
{
	bool flag{ false };
	do
	{
		try 
		{
			if(flag)
			cout << "Введите информацию типа " << typeid(T).name() << ": " << endl;
			flag = true;
			in >> obj;
			if (typeid(T)==typeid(int) || typeid(T)==typeid(double)|| typeid(T) == typeid(long))
				if (!in.good() || in.peek() != '\n')   //если не установился флаг ошибки и поток не пуст
					throw Inputexception("Введен неправильный элемент",1);
		}
		catch (Inputexception& inpex)   //обработка исключения
		{
			flag = false;
			cin.clear();
			cin.ignore(32767, '\n');
			cerr << "Исключение:" << inpex.what() << "\n Код ошибки:" << inpex.getCode() << endl;
		}
		catch (...)   //абсолютный обработчик
		{
			flag = false;
			cout << "Неожиданное исключение";
			rewind(stdin);
			in.clear();
		}
	} while (!flag);
}

template <typename T>
inline void inputNum(istream& is,T& n, T j, T k)   //функция ввода числа с диапозоном
{
	bool flag{ true };
	do
	{
		try
		{
			if(!flag)
			cout << "Введите число в диапазоне: от " << j << " до " << k << ")" << endl;
			flag = true;
			is >> n;
			if (!is.good() || is.peek() != '\n')   //если не установился флаг ошибки и поток не пуст
				throw Inputexception("Введенная информация не соответствует типу", 2);
			if ((n < j) || (n > k))   //если элемент не входит в диапозон
				throw Inputexception("Введеная информация находится вне заданного диапазона", 3);
		}
		catch (Inputexception& inpex)   //обработка исключения
		{
			flag = false;
			is.clear();
			is.ignore(32767, '\n');
			cerr << "Исключение:" << inpex.what() << "\n Код ошибки:" << inpex.getCode() << endl;
		}
		catch (...)   //абсолютный обработчик
		{
			flag = false;
			cout << "Неожиданное исключение" << endl;
			rewind(stdin);
			is.clear();
		}
	} while (!flag);
}


template <typename T>
inline void inputNum(T& n)   //функция ввода числа
{
	bool flag{ true };
	do
	{
		try
		{
			if (!flag)
				cout << "Введите положительное числовое значение" << endl;
			flag = true;
			cin >> n;
			if (!cin.good() || cin.peek() != '\n')   //если не установился флаг ошибки и поток не пуст
				throw Inputexception("Введенная информация не соответствует типу", 2);
			if (n<0)   //если число меньше нуля
				throw Inputexception("Введеные данные не должны быть отрицательными", 4);
		}
		catch (Inputexception& inpex)   //обработка исключения
		{
			flag = false;
			cin.clear();
			cin.ignore(32767, '\n');
			cerr << "Исключение:" << inpex.what() << "\n Код ошибки:" << inpex.getCode() << endl;
		}
		catch (...)   //абсолютный обработчик
		{
			flag = false;
			cout << "Неожиданное исключение" << endl;
			rewind(stdin);
			cin.clear();
		}

	} while (!flag);
}

inline string inputStr(istream& is, unsigned end)   //функция ввода 
{
	string tmp;
	bool flag{ true };
	do
	{
		try
		{
			if(!flag)
			cout << "Введите строку меньше " << end << " символов, используя только русского алфавита и пробелы:" << endl;
			flag = true;
			char* buff = new char[80]{};
			rewind(stdin);
			is.getline(buff, 80);
			tmp = buff;
			for (unsigned i = 0; i < tmp.length(); i++)
				if (!(isRus(tmp[i])||isSpace(tmp[i])))   //если не русский символ либо пробел
					throw
					Inputexception("Введенная строка имеет лишние символы", 5);
			if (tmp.length() > end)   //если строка больше заданного размера
				throw
				Inputexception("Введенная строка превысила допустимый размер", 3);
			if(tmp.length() < 1)   //если строка пустая
				throw
				Inputexception("Введенная строка не должна быть пустой", 3);
		}
		catch (Inputexception& inpex)   //обработка исключения
		{
			flag = false;
			is.clear();
			rewind(stdin);
			cerr << "Исключение:" << inpex.what() << "\n Код ошибки:" << inpex.getCode() << endl;
		}
		catch (...)   //абсолютный обработчик
		{
			flag = false;
			cout << "Неожиданное исключение" << endl;
			rewind(stdin);
			cin.clear();
		}
	} while (!flag);
	return tmp;
}

inline string inputCurr(istream& is, unsigned end)   //функция ввода 
{
	string tmp;
	bool flag{ true };
	do
	{
		try
		{
			if(!flag)
			cout << "Введите строку размером " << end << " символов, используя только английские символы верхнего регистра:" << endl;
			flag = true;
			char* buff = new char[80]{};
			rewind(stdin);
			is.getline(buff, 80);
			tmp = buff;
			for (unsigned i = 0; i < tmp.length(); i++)
				if (!(isUpper(tmp[i])))   //если не символы верхнего регистра латиницы
					throw
					Inputexception("Введенная строка имеет лишние символы", 5);
			if (tmp.length() != end)   //если строка не является 3-хсимвольной(формат валюты)
				throw
				Inputexception("Введенная строка не соответствует формату валюты", 6);
		}
		catch (Inputexception& inpex)   //обработка исключения
		{
			flag = false;
			is.clear();
			rewind(stdin);
			cerr << "Исключение:" << inpex.what() << "\n Код ошибки:" << inpex.getCode() << endl;
		}
		catch (...)   //абсолютный обработчик
		{
			flag = false;
			cout << "Неожиданное исключение" << endl;
			rewind(stdin);
			cin.clear();
		}
	} while (!flag);
	return tmp;
}

inline string inputType()   //функция выбора типа вклада
{
	string str;
	std::cout << "Доступные типы вклада: 1 - Пополняемый| 2 - Не пополняемый" << endl;
	cout << "Выберите тип:" << endl;
	int n;   //временная переменная для выбора
	inputNum(cin,n, 1, 2);   //безопасный ввод 
	if (n == 1)
		str = "Пополняемый";
	else
		str = "Не пополняемый";
	return str;
}