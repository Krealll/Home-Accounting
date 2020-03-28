#pragma once
#include <fstream>
#include"Myexception.h"

using namespace std;

class File   //класс файла для работы с потоками
{
protected:
	ofstream fo{};   //объект класса выходного потока
	ifstream fi{};   //объект класса входного потока
	string path{};   //путь к файлу
public:
	File(string _path) : path(_path){}
	~File()   //деструктор файла
	{
		fo.close();
		fi.close();
	}
	void openOut();   //метод открытия файла для вывода
	void openIn();   //метод открытия файла для ввода
	void putStr(string str);   //метод вывода строки в поток
	template <typename T>
	void putObj(T& obj);   //шаблонный метод вывода обьекта в поток
	template <typename T>
	bool readLine(T& obj);   //шаблонный метод считывания строки из файла
};

template<typename T>
inline void File::putObj(T & obj)   //шаблонный метод вывода обьекта в поток
{
	fo << obj << endl;
}

template<typename T>
inline bool File::readLine(T& obj)   //шаблонный метод считывания строки из файла
{
	while (fi.peek() == '\n')    //пропускаем символы новой строки, которые могли остаться в файле 
		fi.get();
	if (fi.eof())   //если конец файла
		return false;   //возращает false
	getline(fi, obj);    //считываем строку из файла
	return true;
}