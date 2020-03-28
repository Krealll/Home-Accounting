#pragma once
#include "Income.h"
#include"Expenses.h"
#include "Deposit.h"
#include "Interface.h"
#include"Currency.h"

class MainMenu   //класс главного меню
{
private:
	Account budget;   //агрегация обьекта бюджет класса счёт
public:
	MainMenu();  
	void launch();   //метод запуска главного меню

	void chooseCurrency(Currency& curr);   //метод запуска меню валюты

	void budgetAnalysis();   //метод анализа бюджета семьи
	void depositAnalysis();   //метод анализа прибыли депозитов
	void inputBudget();   //ввод семейного бюджета

	template<typename T>
	void analysis(Interface<T>& I)   //шаблонный метод анализа данных
	{
		T most;   //временый объект для поиска
		I.load();   //загружаем в обьект интерфейса данные из файла
		cout << "\n";
		if (I.data.getRoot())   //если файл не пуст 
			I.show(I.data);   //показ таблицы данных
		else
		{
			cout << "\n Нет данных для анализа в таблице " << I.Name(most) << endl;
			return;
		};
		double bdg = budget.getSum();   //запомиаем значение бюджета
		double temp = findSum(I.data);   //находим из дерева данных сумму 
		most = findMost(I.data);   //находим наибольший объект по полю Суммы
		cout.precision(2);
		cout << fixed;
		cout << "Суммарно :" << temp << " " << ((budget.getCrnc()).getName()) << endl;
		cout << "Самая значительная категория - " << most.getCategory() << ": "  << most.getSum() << " " << ((most.getCrnc()).getName()) << endl;
		bdg += temp;
		budget.setSum(bdg);
		cout << "С учётом  остаток бюджета: " << budget.getSum() << " " << ((budget.getCrnc()).getName()) << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||\n\n";
	}
	template<>
	void analysis(Interface<Income>& I)   //специализация для метода анализа доходов
	{
		Income most;   //временный объект для поиска
		I.load();   //загружаем данные дохдов из файла
		cout << "\n";
		if (I.data.getRoot())
			I.show(I.data);   //если файл не пуст - показываем таблицу
		else
		{
			cout << "\n Нет данных для анализа в таблице " << I.Name(most) << endl;
			return;
		};
		double bdg = budget.getSum();   //запоминаем значение бюджета 
		double temp = findSum(I.data);   //находим суммарный доход
		most = findMost(I.data);   //поиск наиболее доходного объекта
		cout.precision(2);
		cout << fixed;
		cout << "Суммарный доход:" <<  temp<< " " << ((budget.getCrnc()).getName())<<endl;
		cout << "Самая доходная категория - " << most.getCategory() <<": " << most.getSum() << " " << ((most.getCrnc()).getName()) << endl;
		bdg += temp;
		budget.setSum(bdg);
		cout << "С учётом доходов остаток бюджета: " << budget.getSum()<<" "<<((budget.getCrnc()).getName()) << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||\n\n";
	}
	template<>
	void analysis(Interface<Expenses>& I)   //специализация для метода анализа доходов
	{
		Expenses most;   //временный объект расходов для поиска
		I.load();   //загрузка данных расходов из файла
		cout << "\n";
		if (I.data.getRoot())
			I.show(I.data);   //если файл не пуст - вывод таблицы расходов
		else
		{
			cout << "\n Нет данных для анализа в таблице " << I.Name(most) << endl;
			return;
		};
		double bdg = budget.getSum();   //запоминаем значение  бюджета
		double temp = findSum(I.data);   //находим суммарный расход
		most = findMost(I.data);   //поиск наиболее затратного объекта
		cout.precision(2);
		cout << fixed;
		cout << "Суммарный расход:" << temp << " " << ((budget.getCrnc()).getName())<< endl;
		bdg -= temp;
		if (bdg < 0)   //если значение бюджета 
		{
			cout << "Вы превысили  бюджет. Снизьте затраты, либо увеличьте доход." << endl;
		}
		cout << "Самая затратная категория:" << most.getCategory() << ": " << most.getSum() << " " << ((most.getCrnc()).getName()) << endl;
		cout << "Следует снизить затраты на данную категорию" << endl;
		budget.setSum(bdg);
		cout << "С учётом расходов остаток бюджета: " << budget.getSum() << " " << ((budget.getCrnc()).getName()) << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||\n\n";

	}

};

