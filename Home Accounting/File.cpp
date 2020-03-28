#include "File.h"


void File::openOut()   //метод открытия файла для вывода
{
	try
	{
		fo.open(path);   //открытие файла
		if (!fo.is_open())
			throw Myexception("Открыть файл не удалось");   //вызов исключения
	}
	catch (Myexception& obj)   //обработка исключения
	{
		cerr << "Исключение: " << obj.what() << endl;
		system("pause");
	}
	catch (...)   //абсолютный обработчик
	{
		cerr << "Неожиднное исключение\n";
	}
}

void File::openIn()   //метод открытия файла для ввода
{
	try
	{
		fi.open(path);   //открытие файла
		if (!fi.is_open())
			throw Myexception("Открыть файл не удалось");   //вызов исключения
	}
	catch (Myexception& obj)   //обработка исключения
	{
		cerr << "Исключение: " << obj.what() << endl;
		system("pause");
	}
	catch (...)   //абсолютный обработчик
	{
		cerr << "Неожиднное исключение\n";
	}
}

void File::putStr(string str)   //метод вывода строки в поток
{
	fo << str << endl;
}
