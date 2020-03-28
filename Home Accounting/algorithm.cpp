#include "algorithm.h"

typedef list<string>::iterator iter;
list<string>::iterator findS(list<string>& temp, iter it)   //поиск в листе по итератору
{
	list<string>::iterator itt = temp.begin();
	for (; itt != temp.end(); ++itt)
		if (*itt == *it)   //если найден такой же элемент прерываем поиск
			break;
	return itt;
}

void changeCurrObj(Tree<Currency>::iterator it)   //функция изменения валюты
{
	list<string> temp = chooseFields(*it);   //выбор полей для изменения
	changeCurrFields(it, temp);   //изменеине полей
	system("CLS");
	cout << "Поля успешно изменены" << endl;
	system("pause");
}


void changeCurrFields(typename Tree<Currency>::iterator it, list<string> tempList)   //функция изменения
																				     //полей валюты
{
	system("CLS");
	cout << "Параметры были выбраны" << endl;
	if (find(tempList.begin(), tempList.end(), "Имя валюты     ") != tempList.end())   //если было выбрано имя 
	{
		string temp;
		cout << "Введите название новой валюты" << endl;
		temp = inputCurr(cin, 3);   //ввод нового значения поля 
		(*it).setName(temp);   //изменение поля
	}
	if (find(tempList.begin(), tempList.end(), "Курс(1 отн.BYN)") != tempList.end())   //если был выбран курс
	{
		double temp;
		cout << "Введите курс новой валюты" << endl;
		input(cin, temp);   //ввод нового значения поля 
		(*it).setRate(temp);   //изменение поля
	}
}

void findCurr(Tree<Currency>& tree)   //функция для поиска валюты
{
	Currency obj;   //временный объект для поиска
	stack<Currency> res;   //стэк результатов поиска
	try
	{
		if (!tree.getRoot())
			throw Myexception("Can't find element in empty tree");
		comparator comp(chooseFields(obj));   //выбор полей для поиска
		setObjCurr(comp.getCompFields(), obj);   //установка полей для сравнения
		typename Tree<Currency>::iterator iter;
		iter = tree.begin();
		for (; iter != tree.end(); ++iter)   //проходим по дереву
		{
			if (comp(obj, *iter))   //когда нашли такую же валюту
				res.push(*iter);   //заносим её в стэк результата
		}
		if (res.empty())
			throw Myexception("There are no such element");
	}
	catch (Myexception& mex)   //обработчик исключения
	{
		throw mex;
	}
	catch (...)   //абсолютный обработчик
	{
		cerr << "Unexpected behavior" << endl;
		return;
	}
	makeTable(res);   //вывод таблицы найденной валюты
}

void setObjCurr(list<string> tempList, Currency & obj)   //функция изменения полей валют
{
	system("CLS");
	cout << "Параметры были выбраны" << endl;
	if (find(tempList.begin(), tempList.end(), "Имя валюты     ") != tempList.end())   //если выбрана валюта
	{
		string temp;
		cout << "Введите название искомой валюты" << endl;
		temp = inputCurr(cin, 3);   //ввод искомого поля
		obj.setName(temp);   //установка поля для сравнения
	}
	if (find(tempList.begin(), tempList.end(), "Курс(1 отн.BYN)") != tempList.end())   //если выбран курс
	{
		double temp;
		cout << "Введите курс искомой валюты" << endl;
		input(cin, temp);   //ввод искомого поля
		obj.setRate(temp);   //установка поля для сравнения
	}
}

void setObj(list<string> tempList, Account & obj)   //функция установки полей для поиска 
{
	system("CLS");
	cout << "Параметры были выбраны" << endl;
	if (find(tempList.begin(), tempList.end(), "Категория      ") != tempList.end())   //если выбрана категория
	{
		string temp;
		cout << "Введите искомую категорию" << endl;
		temp = inputStr(cin, 15);   //ввод искомого поля
		dynamic_cast<MonetaryOperation&>(obj).setCategory(temp);   //установка поля для сравнения
	}
	if (find(tempList.begin(), tempList.end(), "Валюта         ") != tempList.end())   //если выбрана валюта
	{
		string temp;
		cout << "Введите название искомой валюты" << endl;
		temp = inputCurr(cin, 3);   //ввод искомого поля
		obj.setCrncName(temp);   //установка поля для сравнения
	}
	if (find(tempList.begin(), tempList.end(), "Сумма          ") != tempList.end())   //если выбрана сумма
	{
		double temp;
		cout << "Введите искомую сумму" << endl;
		input(cin, temp);   //ввод искомого поля
		obj.setSum(temp);   //установка поля для сравнения
	}
	if (find(tempList.begin(), tempList.end(), "Тип            ") != tempList.end())   //если выбран тип
	{
		string temp;
		cout << "Введите искомый тип" << endl;
		temp = inputType();   //ввод искомого поля
		dynamic_cast<Deposit&>(obj).setType(temp);   //установка поля для сравнения
	}
	if (find(tempList.begin(), tempList.end(), "Процент        ") != tempList.end())   //если выбран процент
	{
		int temp;
		cout << "Введите искомый процент" << endl;
		inputNum(cin,temp,0,100);   //ввод искомого поля
		dynamic_cast<Deposit&>(obj).setPercent(temp);   //установка поля для сравнения
	}
}


double findRate(Currency curr, Tree<Currency>& tree)   //функция для поиска курса валюты
{
	double temp = 0.0;   //временная переменная для хранения значения курса
	typename Tree <Currency>::iterator it;
	it = tree.begin();
	for (; it != tree.end(); ++it)   //проход о дереву
		if (curr.getName() == (*it).getName())   //если нашлось нужное имя валюты
		{
			temp = (*it).getRate();   //запоминаем её курс
			break;
		}
	if (!temp)
		throw Myexception("Ошибка валюты. Дополните список валюты");   //вызов исключения
	return temp;
}

bool comparator::operator()(const Expenses & objr, const Expenses & objl)   //сравнение расходов
{
	int counter{};   //если поля совпадают увеличиваем счётчик
	if (find(comparedFields.begin(), comparedFields.end(), "Сумма          ") != comparedFields.end())
		if (objr.getSum() == objl.getSum())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "Валюта         ") != comparedFields.end())
		if (objr.getCrnc() == objl.getCrnc())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "Категория      ") != comparedFields.end())
		if (objr.getCategory() == objl.getCategory())
			++counter;
	return counter == comparedFields.size();   //если количество выбранных полей равно счётчику, то объекты равны
}

bool comparator::operator()(const Income & objr, const Income & objl)   //сравнение доходов
{
	int counter{};   //если поля совпадают увеличиваем счётчик
	if (find(comparedFields.begin(), comparedFields.end(), "Сумма          ") != comparedFields.end())
		if (objr.getSum() == objl.getSum())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "Валюта         ") != comparedFields.end())
		if (objr.getCrnc() == objl.getCrnc())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "Категория      ") != comparedFields.end())
		if (objr.getCategory() == objl.getCategory())
			++counter;
	return counter == comparedFields.size();   //если количество выбранных полей равно счётчику, то объекты равны
}


bool comparator::operator()(const Deposit & objr, const Deposit & objl)   //сравнение вкладов
{
	int counter{};   //если поля совпадают увеличиваем счётчик
	if (find(comparedFields.begin(), comparedFields.end(), "Сумма          ") != comparedFields.end())
		if (objr.getSum() == objl.getSum())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "Валюта         ") != comparedFields.end())
		if (objr.getCrnc() == objl.getCrnc())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "Процент        ") != comparedFields.end())
		if (objr.getPercent() == objl.getPercent())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "Тип            ") != comparedFields.end())
			if (objr.getType() == objl.getType())
				++counter;
	return counter == comparedFields.size();   //если количество выбранных полей равно счётчику, то объекты равны
}

bool comparator::operator()(const Currency & objr, const Currency & objl)   //сравнение валют
{
	int counter{};   //если поля совпадают увеличиваем счётчик
	if (find(comparedFields.begin(), comparedFields.end(), "Имя валюты     ") != comparedFields.end())
		if (objr.getName() == objl.getName())
			++counter;
	if (find(comparedFields.begin(), comparedFields.end(), "Курс(1 отн.BYN)") != comparedFields.end())
		if (objr.getRate() == objl.getRate())
			++counter;
	return counter == comparedFields.size();   //если количество выбранных полей равно счётчику, то объекты равны
}
