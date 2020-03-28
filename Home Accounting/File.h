#pragma once
#include <fstream>
#include"Myexception.h"

using namespace std;

class File   //����� ����� ��� ������ � ��������
{
protected:
	ofstream fo{};   //������ ������ ��������� ������
	ifstream fi{};   //������ ������ �������� ������
	string path{};   //���� � �����
public:
	File(string _path) : path(_path){}
	~File()   //���������� �����
	{
		fo.close();
		fi.close();
	}
	void openOut();   //����� �������� ����� ��� ������
	void openIn();   //����� �������� ����� ��� �����
	void putStr(string str);   //����� ������ ������ � �����
	template <typename T>
	void putObj(T& obj);   //��������� ����� ������ ������� � �����
	template <typename T>
	bool readLine(T& obj);   //��������� ����� ���������� ������ �� �����
};

template<typename T>
inline void File::putObj(T & obj)   //��������� ����� ������ ������� � �����
{
	fo << obj << endl;
}

template<typename T>
inline bool File::readLine(T& obj)   //��������� ����� ���������� ������ �� �����
{
	while (fi.peek() == '\n')    //���������� ������� ����� ������, ������� ����� �������� � ����� 
		fi.get();
	if (fi.eof())   //���� ����� �����
		return false;   //��������� false
	getline(fi, obj);    //��������� ������ �� �����
	return true;
}