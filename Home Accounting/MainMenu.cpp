#include "MainMenu.h"


MainMenu::MainMenu()   //конструкор по умолчанию
{
	Account();
}

void MainMenu::launch()   //метод запуска главного меню
{
	cout << "Добро пожаловать в программу по учёту домашней бухгалтерии!" << endl;
	int ans;   //Переменная для пользовательского ввода
	do 
	{
		cout << "Главное Меню:\n";
		cout << "1: Работа с расходами\n";
		cout << "2: Работа с доходами\n";
		cout << "3: Задать бюджет семьи\n";
		cout << "4: Анализ бюджета\n";
		cout << "5: Работа со вкладами\n";
		cout << "6: Анализ вкладов\n";
		cout << "7: Настройка валют\n";
		cout << "0: Выйти из программы\n";

		inputNum(cin,ans, 0, 7);   //Безопасный ввод числа в диапозоне
		switch (ans)
		{
		case 1:
		{
		Interface<Expenses> I;   //интерфейс расходов
		if (!I.subMenu())   //запуск подменю планирования
			return;
		break;
		}
		case 2:
		{	
			Interface<Income> I;   //интерфейс доходов
			if (!I.subMenu())   //запуск подменю планирования
				return;
			break;
		}
		case 3:
		{
			inputBudget();   //Ввод семейного бюджета 
			system("CLS");
			break;
		}
		case 4:
		{
			try
			{
				budgetAnalysis();   //запуск метода анализа бюджета
			}
			catch (Myexception& obj)
			{
				cerr << "Исключение: " << obj.what() << endl;   //обработка исключительной ситуации
				system("pause");
				break;
			}
			catch (...)
			{
				cerr << "Неожиднное исключение\n";   //обработка исключительной ситуации
			}
			system("pause");
			system("CLS");
			break;
			
		}
		case 5:
		{
			system("CLS");
			Interface<Deposit> I;   //интерфейс вкладов
			if (!I.start())   //запуск меню вкладов
				return;
			break;
		}
		case 6:
		{
			system("CLS");
			try
			{
				depositAnalysis();   //запуск метода анализа вкладов
			}
			catch (Myexception& obj)
			{
				cerr << "Исключение: " << obj.what() << endl;   //обработка исключительной ситуации
				system("pause");
				break;
			}
			catch (...)
			{
				cerr << "Неожиднное исключение\n";   //обработка исключительной ситуации
				system("pause");
			}
			system("CLS");
			break;
		}
		case 7:
		{
			system("CLS");
		Interface<Currency> I;   //интерфейс валюты
			if (!I.start())   //запуск меню валюты
				return;
			break;
		}
		case 0:
		{
			exit(0);   //выход из программы
			break;
		}
		default:
			cout << "Неправильный ввод" << endl;
			system("pause");
			break;
		}
	} while (1);
}

void MainMenu::chooseCurrency(Currency& curr)   //меню выбора валюты
{
	int i;   //переменная для выбора валюты
	Interface<Currency> temp;   //интерфейс валюты для её выбора
	temp.load();   //загрузка данных из файла валют
	if (!temp.data.empty())   //если файл был не пустой
	{
		cout << "Таблица валюты" << endl;
		makeTable(temp.data.begin(), temp.data.end());   //запуск метода вывода таблицы
	}
	else
		throw Myexception("Нет валют для выбора");   //вызов исключительной ситуации
	cout << "\nВыберите валюту бюджета:";
	inputNum(cin,i, 1, temp.data.size());   //Безопасный ввод переменной в диапозоне
	typename Tree<Currency>::iterator it;   //итератор для прохода по дереву валют
	it = temp.data.begin();   //устанавливаем итератор на начало дерева
	for (; i > 1; i--)
		++it;
	curr = *it;   //устанавливаем выбранную валюту
}

void MainMenu::budgetAnalysis()   //метод анализа бюджета
{
	if (!budget.getSum())   //если семейный бюджет не задан
	{
		cout << "Сперва задайте семейный бюджет:" << endl;
		system("pause");
		system("CLS");
		inputBudget();   //ввод семейного бюджета
	}
	double temp = budget.getSum();   //запись значения бюджета во временную переменную
	cout << "Производится анализ данных из файлов:" << endl;
	Interface<Income> I1;   //интерфейс доходов
	Interface<Expenses> I2;   //интерфейс расходов
	analysis(I1);   //метод анализа данных
	analysis(I2);   

	I1.flag = 1;   //установка флага в интерфейсе для планирования
	I2.flag = 1;
	I1.data.destroyTree(I1.data.getRoot());   //очищаем загруженные данные
	I2.data.destroyTree(I2.data.getRoot());

	analysis(I1);   //метод анализа данных
	analysis(I2);
	budget.setSum(temp);   //возвращаем изначальное значение бюджета для дальнейшей работы
}

void MainMenu::depositAnalysis()   //метод анализа вкладов
{
	if (!budget.getSum())   //если бюджет не задан
	{
		cout << "Сперва задайте семейный бюджет:" << endl;
		system("pause");
		system("CLS");
		inputBudget();   //ввод бюджета
	}
	Interface<Deposit> I;   //интерфейс вкладов
	I.load();   //загрузка данных из файла со вкладами
	cout << "\n";
	if (I.data.getRoot())
	{
		double sum = findSum(I.data);   //метод нахождения дохода по вкладам
		I.show(I.data);   //метод вывода данных 
		cout << "После окончания сроков вкладов, чистая выручка составит:" << sum << " " << ((budget.getCrnc()).getName()) << endl;
		cout << "С учётом данной выручки балланс бюджета: " << budget.getSum() + sum << endl;
	}
	else
	{
		cout << "\n Нет данных для анализа в таблице вкладов"<< endl;
		return;
	};
	system("pause");
}

void MainMenu::inputBudget()   //метод безопасного ввода семейного бюджета
{
	cout << "Введите допустимый бюджет в BYN" << endl;
	input(cin,budget);   //функция безопасного ввода
	Currency curr("BYN", 1.0);   //задаём валюту семейного бюджета
	this->budget.setCrnc(curr);
}

