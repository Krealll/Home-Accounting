#pragma once
#include"Tree.h"
#include"Income.h"
#include"Expenses.h"
#include"Deposit.h"
#include "algorithm.h"
#include <stack>
#include"File.h"

template <typename T>   //шаблоный класс интерфейса
class Interface
{
private: 
	string path{};   //строка c путём к файлу
	string crnc{};   //строка выбранной валюты

public:
	Tree<T> data;   //шаблонное дерево данных
	int flag = 0;   //флаг для планирования

	bool start();   //метод работы с данными
	bool subMenu();   //полменю выбора планирования
	void currMenu();   //подменю выбора валюты
	void saveResult();   //метод сохранения резултата
	void load();   //метод загрузки данных из файла
	void undo(Tree<T>& tree, stack<T>& stItem, stack<int>& stCode);   //шаблонный метод отмены 
	                                                                  //последнего действия
	template<typename T>
	void change(Tree<T>& data,typename Tree<T>::iterator it)   //шаблонный метод 
															   //изменения данных
	{
		changeObj<T>(it);
	}
	template<>
	void change(Tree<Currency>& data,Tree<Currency>::iterator it)   //специализация метода
																    //изменения для валюты
	{
		changeCurrObj(it);
	}
	template<typename T>
	void search(Tree<T>& data)   //шаблонный метод поиска данных
	{
		findItem(data);
	}
	template<>
	void search(Tree<Currency>& data)   //специализация метода поиска для валюты
	{
		findCurr(data);
	}
	template <typename T>
	void show(Tree<T>& data)   //шаблонный метод вывода таблицы даных
	{
		cout << "Таблица " << Name(data.getRoot()->value);
		makeTable(data.begin(), data.end());
	}
	template <>
	void show(Tree<Income>& data)   //специализация метода вывода таблицы
								    //для доходов
	{
		cout << "Таблица ";
		if (flag)
			cout << "планируемых доходов" << endl;
		else
			cout << "поступивших доходов" << endl;
		makeTable(data.begin(), data.end());
	}
	template <>
		void show(Tree<Expenses>& data)   //специализация метода вывода таблицы
										  //для расходов
	{
			cout << "Таблица ";
			if (flag)
				cout << "планируемых расходов" << endl;
			else
				cout << "текущих расходов" << endl;
		makeTable(data.begin(), data.end());
	}

	template <typename T>
	string Name(T& obj)   //шаблонный метод имени типа
	{
		return "расходов\n";
	}
	template <>
	string Name(Income& obj)   //специализация метода имени для доходов
	{
		return "доходов\n";
	}
	template <>
	string Name(Currency& obj)   //специализация метода имени для валюты
	{
		return "валюты\n";
	}
	template <>
	string Name(Deposit& obj)   //специализация метода имени для вкладов
	{
		return "вкладов\n";
	}
};

template<typename T>
void Interface<T>::load()   //метод загрузки данных из фала
{
	T temp("");
	if (!flag)   //если не установлено планирование 
	path = temp.getPath();   //получение пути к файлу
	else if (typeid(T).name() == typeid(Income).name())   //иначе задаем путь
														  //к файлам планирования
			path = "..\\Files\\plIncome.txt";
		else
			path = "..\\Files\\plExpenses.txt";
	string tmp;   //временная строка для чтения
	File f(path);   //вызов конструктора с параметор
	f.openIn();   //открытие файла для записи
	try
	{
		while(f.readLine(tmp))   //читаем файл пока не достигли конца
		{
			temp.prep(tmp);   //задаём поля объекта
			data.insert(temp);   //вставляем елемент в дерево
		}
		if (typeid(T).name() == typeid(Currency).name() && (!data.getRoot()))   //если файл
																				//валют пуст
		{
			temp.prep("BYN|1");   //задаём значение валюты BYN
			data.insert(temp);   //вставляем елемент в дерево
		}
	}
	catch (Myexception& obj)   //обработка исключительной ситуации
	{
		cerr << "Исключение, связанное с данными в файле: " << obj.what() << endl;
		system("pause");
		return;
	}
	catch (...)   //неожиданный обработчик
	{
		cerr << "Неожиднное исключение\n";
		return;
	}
}

template<typename T>   //шаблонный метод отмены последнего действия
inline void Interface<T>::undo(Tree<T>& tree, stack<T>& stItem, stack<int>& stCode)
{
	if (stCode.top() == 1)   //если сверху стэка значение состояния 1 - произошло добавление
	{
		stCode.pop();   //удаляем верхний элемент стэка состояния
		T temp;
		temp = stItem.top();   //получаем элемент, который был вставлен из стэка элементов
		tree.pop(temp);   //удаляем данный элемент из дерева
		stItem.pop();   //удаляем верхний элемент стэка
	}
	else if (stCode.top() == 2)   //значение состояния 2 - произошло удаление
	{
		stCode.pop();   //удаляем верхний элемент стэка состояния
		tree.insert(stItem.top());   //вставляем в дерево удалённый элемент
		stItem.pop();   //удаляем верхний элемент стэка
	}
	else if (stCode.top() == 3)   //значение состояния 3 - произошло изменение
	{
		stCode.pop();   //удаляем верхний элемент стэка состояния
		tree.pop(stItem.top());   //удаляем новый измененный элемент из дерева
		stItem.pop();   //удаляем верхний элемент стэка
		tree.insert(stItem.top());    //вставляем старый элемент
		stItem.pop();   //удаляем верхний элемент стэка
	}
}

template<typename T>
bool Interface<T>::subMenu()    //шаблонное подменю выбора планирования
{
	system("CLS");
	int ans{};    //переменная для пользовательского ввода
	do
	{
		T obj;    //временный объект для работы
		cout << "Меню " << Name(obj);
		cout << "1: Планирование " << Name(obj);
		cout << "2: Учёт текущих " << Name(obj);
		cout << "3: Выход в главное меню\n";
		cout << "0: Выход\n";
		inputNum(cin,ans,0,4);    //безопасный ввод 
		system("CLS");
		switch (ans)
		{
		case 1:
		{
			this->flag = 1;    //установка флага планирования
			if (this->start())    //запуск метода работы
				return true;
			else
				return false;
		}
		case 2:
		{
			if (this->start())    //запуск метода работы
				return true;    //выход в главное меню
			else
				return false;    //выход из программы
		}
		case 3:
		{
			system("CLS");
			return true;    //выход в главное меню
		}
		case 0: {
			system("CLS");
			return false;    //выход из программы
		}
		default: {
			cout << "\nIncorrect answer, please, try again" << endl;
			system("pause");
			break;
		}
		}
	} while (ans);
	return true;
}

template<typename T>
inline void Interface<T>::currMenu()    //шаблонное меню выбора валюты
{
	try
	{
		int i;    //переменная для выбора валюты
		Interface<Currency> temp;    //временный интерфей для выбора
		temp.load();    //загрузка данных из файла валют
		if (!temp.data.empty())    //если файл не пустой
		{
			cout << "Таблица валюты" << endl;
			makeTable(temp.data.begin(), temp.data.end());    //вывод таблицы валют
		}
		else
			throw Myexception("Нет валют для выбора");    //вызов исключительной ситуации
		cout << "\nВыберите номер валюты для работы:";
		inputNum(cin,i, 1, temp.data.size());    //безопасный ввод 
		typename Tree<Currency>::iterator it;
		it = temp.data.begin();    //установка итератора на начало дерева валют
		for (; i > 1; i--)
			++it;    //проход по дереву до необходимого элемента
		this->crnc = (*it).getName();    //запоминаем выбранную валюту
		system("CLS");
	}
	catch (Myexception& obj)    //обработка исключения
	{
		cerr << "Исключение: " << obj.what() << endl;
		system("pause");
		return;
	}
	catch (...)    //неожиданный обработчик
	{
		cerr << "Неожиднное исключение\n";
		system("pause");
		return;
	}
}

template<typename T>
inline void Interface<T>::saveResult()    //метод сохранения дерева в файл
{
	File f(path);     //конструктор с параметром пути
	f.openOut();    //открытие файла для загрузки данных в файл
	
	if (data.getRoot())    //если дерево не пустое
	{
		typename Tree<T>::iterator it;
		it = data.preBegin();    //устанавливаем итератор на начало дерева 
							     //для прямого обхода
		while (it != data.end())    //пока не дойдём до конца дерева
		{
			f.putObj(*it);    //вставляем элемент в файл
			it.preOrder();    //увеличиваем итератор на 1(прямой обход)
		}
	}
}

template<typename T>
bool Interface<T>::start()    //шаблонный метод работы с данными
{
	stack<int> stCode;    //стэк состояний для отмены действий
	stack<T> stItem;    //стэк элементов для отмены действий
	this->load();    //загружаем данные из файла в дерево
	if (typeid(T).name() != typeid(Currency).name())    //если работаем не с валютой
	{
		currMenu();    //вызываем меню выбора валюты
	}
	T tmp(crnc);    //задаём значение валюты
	int ans{};    //переменная для пользовательского ввода
	do
	{
		if (typeid(T).name() != typeid(Currency).name())
		cout << "Выбранная валюта: "<< crnc << endl;
		cout << "Меню ";
		cout << Name(tmp);
		cout << "1: Добавть\n";
		cout << "2: Удалить один элемент\n";
		cout << "3: Показать \n";
		cout << "4: Удалить всё\n";
		cout << "5. Изменить\n";
		cout << "6. Отменить последнее действие\n";////////////////////
		cout << "7: Найти\n";
		cout << "8: Выход в главное меню\n";
		cout << "0: Выход\n";
		inputNum(cin,ans, 0, 8);    //безопасный ввод
		switch (ans)
		{
		case 1:
		{
			system("CLS");
			cout << "1:\nВведите элемент: " << endl;
			input(cin, tmp);    //ввод элемента для добавления
			try
			{
				data.insert(tmp);    //добавление элемента в дерево
				stCode.push(1);    //заносим значение с стэк состояний
				stItem.push(tmp);    //заносим в стэк элемент
			}
			catch (Myexception& obj)    //обработка исключения
			{
				cerr << "Исключение: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //абсолютный обработчик
			{
				cerr << "Неожиднное исключение\n";
			}
			break;
		}
		case 2:
		{
			int i;
			system("CLS");
			try
			{
				if (data.getRoot())    //если дерево не пустое - вывод таблицы данных
				{
					cout << "2:\nВведите номер элемента для удаления: " << endl;
					makeTable(data.begin(), data.end());    
				}
				else
					throw Myexception("Нет информации для удаления");    //вызов исключения
				inputNum(cin,i, 1, data.size());    //выбор по таблице элемента для удаления
				typename Tree<T>::iterator it;
				it = data.begin();    //установка итератора на начало дерева
				for (; i > 1; i--)
					++it;    //проход по дереву до нужного элемента
				stItem.push(*it);    //вставка элемента в стэк
				data.pop(*it);    //удаление элемента по значению
				stCode.push(2);    //вставка значения в стэк состояний
			}
			catch (Myexception& obj)    //обработка исключительной ситуации
			{
				cerr << "Исключение: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //абсолютный обработчик
			{
				cerr << "Неожиднное исключение\n";
				system("pause");
				break;
			}
			break;
		}
		case 3:
		{
			system("CLS");
			cout << "3:\n";
			try
			{
				if (data.getRoot())    //если дерево не пустое
				{
					show(data);    //вывод данных в виде таблицы
				}
				else 
					throw Myexception("Нет информации для отображения");    //иначе вызов исключения
			}
			catch (Myexception& obj)    //обработка исключительной ситуации
			{
				cerr << "Исключение: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //абсолютный обработчик
			{
				cerr << "Неожиднное исключение\n";
				system("pause");
				break;
			}
			break;
		}
		case 4:
		{
			try
			{
				system("CLS");
				if (data.getRoot())    //если дерево не пустое
				{
					int i;    //переменная для выбора
					cout << "Вы действительно хотите удалить данные?" << endl;
					cout << "1. Да" << endl;
					cout << "0. Нет" << endl;
					inputNum(cin,i, 0, 1);    //безопасный ввод
					if (!i)
					{
						system("CLS");
						break;
					}
					cout << "\nДанные были уничтожены\n";
					data.destroyTree(data.getRoot());    //удаление дерева
				}
				else
					throw Myexception("Нет информации для удаления");
			}
			catch (Myexception& obj)    //обработка исключительной ситуации
			{
				cerr << "Исключение: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //абсолютный обработчик
			{
				cerr << "Неожиднное исключение\n";
				system("pause");
				break;
			}
			break;
		}
		case 5:
		{
			system("CLS");
			try
			{
				cout << "5:" << endl;
				int j;    //переменная для выбора изменяемого объекта
				if (!data.empty())    //если дерево не пусто
				{
					cout << "Таблица " << Name(tmp) << endl;
					makeTable(data.begin(), data.end());    //вывести таблицу
				}
				else
					throw Myexception("Нет данных для выбора");
				cout << "\nВыберите номер , который хотите изменить:";
				inputNum(cin,j, 1, data.size());    //безопасный ввод
				typename Tree<T>::iterator it, beg;
				Tree<T> tempo;    //временное дерево
				it = data.begin();    //устанавливаем итератор на начало дерева данных
				for (; j > 1; j--)
					++it;    //находим необходимый элемент
				stCode.push(3);    //заносим в стэк состояние 3
				stItem.push(*it);    //заносим выбранный элемент в стэк

				tempo.insert(*it);    //вставляем элемент во временное дерево
				data.pop(*it);    //удаляем выбранный элемент из дерева данных
				beg = tempo.begin();    //устанавливаем итератор на сохранённый элемент

				change(tempo,beg);    //изменяем выбранные поля в сохранённом элементе

				stItem.push(*beg);    //вставляем измененный элемент в стэк элементов
				data.insert(*beg);    //вставляем измененный элемент в исходное дерево
				system("CLS");
			}
			catch (Myexception& obj)    //обработка исключительной ситуации
			{
				cerr << "Исключение: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //абсолютный обработчик
			{
				cerr << "Неожиднное исключение\n";
				system("pause");
				break;
			}
			break;
		}
		case 6:
		{
			system("CLS");
			try
			{
				if (stCode.empty())   //если стэк состояния пуст
					throw Myexception("Стэк отмены пуст");   //вызов исключения
				undo(data, stItem, stCode);   //иначе отмена последнего действия
			}
			catch (Myexception& obj)    //обработка исключительной ситуации
			{
				cerr << "Исключение: " << obj.what() << endl;
				system("pause");
				break;
			}
			catch (...)    //абсолютный обработчик
			{
				cerr << "Неожиднное исключение\n";
				system("pause");
				break;
			}
			break;
		}
		case 7: 
		{
			system("CLS");
			try
			{
				cout<<"7:"<<endl;
				search(data);   //метод поиска в дереве
			}
			catch (Myexception& mex)    //обработка исключительной ситуации
			{
				system("CLS");
				cerr << "Error:" << mex.what() << "\n" << endl;
				system("pause");
				break;
			}
			catch (...)    //абсолютный обработчик
			{
				cerr << "Unexpected";
				rewind(stdin);
				system("pause");
			}
			break;
		}
		case 8: {
			saveResult();    //сохранение данных дерева в файл
			system("CLS");
			return true;    //возврат в главное меню
		}
		case 0: {
			saveResult();    //сохранение данных дерева в файл
			system("CLS");
			return false;    //выход из программы
		}
		default:
		{
			cout << "\nНеправильный ответ, попробуйте снова" << endl;
			system("pause");
			break;
		}
		}
	} while (ans);
	return true;
}
