#pragma once
#include<iostream>
#include <list>
#include <stack>
#include"Deposit.h"
#include "Expenses.h"
#include "Income.h"
#include"Currency.h"
#include "Tree.h"
#include "Inputexception.h"
#include "table.h"
#include "File.h"

using namespace std;

class comparator   //класс компаратора для сравнения объектов
{
private:
	list<string> comparedFields;   //лист содержащий сравниваемые поля
public:
	list<string> getCompFields() { return comparedFields; }   //возвращает лист

	comparator(list<string> obj) :comparedFields(obj) {}

	bool operator()(const Expenses& objr, const Expenses& objl);   //сравнение расходов
	bool operator()(const Income& objr, const Income& objl);   //сравнение доходов
	bool operator()(const Deposit& objr, const Deposit& objl);   //сравнение вкладов
	bool operator()(const Currency& objr, const Currency& objl);   //сравнение валют
};

typedef list<string>::iterator iter;
list<string>::iterator findS(list<string>& temp, iter it);   //поиск в листе по итератору

void setObjCurr(list<string> tempList, Currency & obj);   //функция установки полей для поиска валют
void setObj(list<string> tempList, Account & obj);   //функция установки полей для поиска 
void findCurr(Tree<Currency>& tree);   //функция для поиска валюты
double findRate(Currency curr, Tree<Currency>& tree);   //функция для поиска курса валюты

void changeCurrFields(typename Tree<Currency>::iterator it, list<string> tempList);   //функция для 
                                                                                      //изменения полей валюты
void changeCurrObj(Tree<Currency>::iterator it);   //функция изменения валюты

template<typename T>
inline void getFields(list<string>& temp, T & obj)   //шаблонная функция для получения полей
{
	list<string> ::iterator it = temp.begin();   //устанавливаем итератор на начало дерева
	string header = obj.createHeader();   //создаём строку заголовка
	int position = 0;
	int prevPos = 1;
	while (1)
	{
		if ((position = header.find('|', prevPos)) == string::npos)   //если не достигли конца строки
			break;													  //либо стоп символа
		temp.push_back(header.substr(prevPos, position - prevPos));   //заносим в лист подстроку до стоп символа
		prevPos = position + 1;
	}
}

template<typename T>
inline double findSum(Tree<T>& tree)   //шаблонная функция подсчёта суммы в дереве
{
	Currency temp;   //временный объект для выбора
	Tree<Currency> currTree;   //временное дерево для выбора
	string tmp;
	File f("..\\Files\\currency.txt");
	f.openIn();   //открываем файл валюты
	while (f.readLine(tmp))   //пока не достигли конца файла считываем 
	{
		temp.prep(tmp);   //подготовка строки для внесения в дерево
		currTree.insert(temp);   //вставка элемента в дерево
	}
	double sum=0.0,tempo=1.0;   //переменные для суммы и для курса
	typename Tree<T>::iterator it;
	it = tree.begin();
	for (; it != tree.end(); ++it)   //проход по дереву поиска
	try
	{
		if (typeid(T).name() == typeid(Deposit).name())   //если щем в дереве вкладов
			tempo = dynamic_cast<Deposit&>(*it).getPercent()/100;   //изменяем переменную для курса
		sum += (tempo*(*it).getSum()*findRate((*it).getCrnc(), currTree));   //подсчитываем сумму 
																			 //с учётом курса
																		     //либо процента
	}
	catch (...)   //абсолютный обработчик
	{
		throw;   //перенаправление потока ошибки
	}
	return sum;
}

template<typename T>
inline T findMost(Tree<T>& tree)   //шаблонная функция поиска максимального элемента
{
	Currency temp;   //временный объект для выбора
	Tree<Currency> currTree;   //временное дерево для выбора
	string str;
	File f("..\\Files\\currency.txt");
	f.openIn();   //открываем файл валюты
	while (f.readLine(str))   //пока не достигли конца файла считываем 
	{
		temp.prep(str);   //подготовка строки для внесения в дерево
		currTree.insert(temp);   //вставка элемента в дерево
	}
	T tmp;   //переменная для хранения значения максимального
	double t = 0.0, max=0.0;
	typename Tree<T>::iterator it;
	it = tree.begin();
	for (; it != tree.end(); ++it)   //проход по дереву
	{
		t = (*it).getSum()*findRate((*it).getCrnc(), currTree);   //устанавливаем значение
																    //с учётом курса
		if (t > max)   //если больше максимального
		{
			tmp = *it;   //запоминаем текущий элемент
			max = t;   //запоминаем значение
		}
	}
	return tmp;
}

template<typename T>
list<string> chooseFields(T & obj)   //шаблонная функция выбора полей
{
	list<string> temp{};   //временный лист полей
	getFields(temp, obj);   //получаем поля объекта
	list<string> fields{};   //возвращаемый лист полей
	int t(1);   //переменная для выбора
	while (t)
	{
		int count(1);
		list<string>::iterator it = temp.begin();   //начало листа
		system("CLS");
		cout << "Выберите параметры:\n";
		cout << "1.Убрать все выбранные параметры" << endl;
		for (; it != temp.end(); ++it)   //проход по листу
		{
			cout << ++count << ". " << *it << endl;   //выводим значения полей
		}
		cout << "0. Стоп" << endl;
		rewind(stdin);
		inputNum(cin,t, 0, count);   //безопасный ввод 
		if (t == 0)   //если t = 0
		{			  // выход из меню выбора
			if (fields.size() == 0)     //если поля не были выбраны
			{
				t = 1;
				cout << "Вы не выбрали ни одного параметра. Повторите попытку.\n";
				system("pause");
				continue;
			}
			break;
		}
		if (t == 1)
		{
			fields.clear();   //очищение листа выбранных полей
			continue;
		}
		it = temp.begin();
		for (int i = t - 2; i > 0; i--, ++it);   //проход по лису
		if (findS(fields,it) == fields.end())   //если такого поля нет
		{
			fields.push_back(*it);   //вносим поле в лист
		}
		else
		{
			cout << "Вы уже выбрали такой параметр.\n";
			system("pause");
		}
		
		if (fields.size() == temp.size())   //если все поля были выбраны
			break;   //прекращение выбора
	};
	return fields;
}

template <typename T>
void changeObj(typename Tree<T>::iterator it)   //шаблонная функция изменения объекта 
{
	list<string> temp=chooseFields(*it);   //выбираем поля для изменения
	changeFields(it, temp);   //меняем выбранные поля
	system("CLS");
	cout << "Поля успешно изменены" << endl;
}

template <typename T>
void changeFields(T it, list<string> tempList)   //шаблонная функция изменения полей 
{
	cout << "Параметры были выбраны" << endl;
	if (find(tempList.begin(), tempList.end(), "Категория      ") != tempList.end())  //если выбрана категория
	{
		string temp;
		cout << "Введите новую категорию" << endl;
		temp = inputStr(cin, 15);   //ввод нового значения поля
		dynamic_cast<MonetaryOperation&>(*it).setCategory(temp);   //изменение поля
	}
	if (find(tempList.begin(), tempList.end(), "Валюта         ") != tempList.end())  //если выбрана валюта
	{
		string temp;
		cout << "Введите новую валюту" << endl;
		temp = inputCurr(cin, 3);   //ввод нового значения поля 
		(*it).setCrncName(temp);   //изменение поля
	}
	if (find(tempList.begin(), tempList.end(), "Сумма          ") != tempList.end())  //если выбрана сумма
	{
		double temp;
		if (typeid(*it).name() == typeid(Deposit).name())   //если работаем с вкладом
		{
			if (dynamic_cast<Deposit&>(*it).getType() == "Пополняемый")   //пополняемы вклад может только 
			{															  //увеличить свою сумма
				cout << "Введите, на сколько вы хотите пополнить балланс" << endl;
				inputNum(temp);
				(*it).setSum(temp + ((*it).getSum()));
			}
			else
			{
				cout << "Изменить балланс не пополняемого вклада невозможно" << endl;   //Не пополняемый 
																						//вклад нельзя изменить
				system("pause");
			}
		}
		else
		{
			cout << "Введите новую сумму" << endl;
			input(cin, temp);   //ввод нового значения поля 
			(*it).setSum(temp);   //изменение поля
		}
	}
	if (find(tempList.begin(), tempList.end(), "Тип            ") != tempList.end())  //если выбран тип
	{
		string temp;
		cout << "Выберите новый тип" << endl;
		temp = inputType();   //ввод нового значения поля 
		dynamic_cast<Deposit&>(*it).setType(temp);   //изменение поля
	}
	if (find(tempList.begin(), tempList.end(), "Процент        ") != tempList.end())  //если выбран процент
	{
		int temp;
		cout << "Введите новый процент" << endl;
		inputNum(cin,temp,0,100);   //ввод нового значения поля 
		dynamic_cast<Deposit&>(*it).setPercent(temp);   //изменение поля
	}
}

template <typename T>
void findItem(Tree<T>& tree)   //шаблонная функция поиска объекта в дереве
{
	T obj;
	stack<T> res;   //стэк для хранения результата
	try
	{
		if (!tree.getRoot())   //если дерево пустое
			throw Myexception("Невозможно найти в пустом дереве");   //вызов исключения
		comparator comp(chooseFields(obj));   //выбор полей для поиска элемента
		setObj(comp.getCompFields(), obj);   //ввод полей для поиска
		typename Tree<T>::iterator iter;
		iter = tree.begin();
		for (; iter != tree.end(); ++iter)   //проход по дереву
		{
			if (comp(obj, *iter))   //сравнивание по выбранным полям 
				res.push(*iter);   //если совпали, то вносим в стэк
		}
		if (res.empty())   //если не нашли элемент
			throw Myexception("Такого элемента нет");   //вызов исключения
	}
	catch (Myexception& mex)   //обработчик исключения
	{
		throw mex;
	}
	catch (...)   //абсолютный обработчик
	{
		cerr << "Неожиданное исключение" << endl;
		return;
	}
	makeTable(res);   //вывод таблицы найденных совпадений
}

template <typename T>
inline void makeTable(stack<T>& st)   //шаблонная функция создания таблицы из стэка
{
	table _table(static_cast<Account&>(st.top()).createHeader());   //инициализируем таблицу заголовком 
	while (!st.empty())   //пока стэк не пуст
	{
		_table.addStr(static_cast<Account&>(st.top()).makeStr());   //добавление строки
		st.pop();   //удаление верхнего элемента стэка
	}
	cout << _table;   //в итоге выводится полученная таблица
}

template <>
inline void makeTable(stack<Currency>& st)   //специализация функции создания таблицы из стэка валют
{
	table _table(st.top().createHeader());   //инициализируем таблицу заголовком 
	while (!st.empty())   //пока стэк не пуст
	{
		_table.addStr(st.top().makeStr());   //добавление строки
		st.pop();   //удаление верхнего элемента стэка
	}
	cout << _table;   //в итоге выводится полученная таблица
}

template<typename it,typename T>
inline it findIter(it begin, it end,T temp)   //шаблонная функция поиска 
{											  //по трем итераторам
	for (; begin != end; ++begin)
		if (*begin == temp)
			break;
	return begin;
}

template<typename it>
inline void makeTable(it begin, it end)   //шаблонная функция создания таблицы
{
	table _table(static_cast<Account&>(*(begin)).createHeader());   //инициализируем таблицу заголовком
	it i = begin;
	for (; i != end; i++)
		_table.addStr(static_cast<Account&>(*i).makeStr());   //добавление строки
	cout << _table;   //вывод полученной таблицы
}
template<>
inline void makeTable(Tree<Currency>::iterator begin, Tree<Currency>::iterator end)   //специализация функции создания
																			      //таблицы из стэка валют
{
	table _table((*begin).createHeader());   //инициализируем таблицу заголовком
	Tree<Currency>::iterator i = begin;
	for (; i != end; i++)
		_table.addStr((*i).makeStr());   //добавление строки
	cout << _table;   //вывод полученной таблицы
}