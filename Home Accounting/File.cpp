#include "File.h"


void File::openOut()   //����� �������� ����� ��� ������
{
	try
	{
		fo.open(path);   //�������� �����
		if (!fo.is_open())
			throw Myexception("������� ���� �� �������");   //����� ����������
	}
	catch (Myexception& obj)   //��������� ����������
	{
		cerr << "����������: " << obj.what() << endl;
		system("pause");
	}
	catch (...)   //���������� ����������
	{
		cerr << "���������� ����������\n";
	}
}

void File::openIn()   //����� �������� ����� ��� �����
{
	try
	{
		fi.open(path);   //�������� �����
		if (!fi.is_open())
			throw Myexception("������� ���� �� �������");   //����� ����������
	}
	catch (Myexception& obj)   //��������� ����������
	{
		cerr << "����������: " << obj.what() << endl;
		system("pause");
	}
	catch (...)   //���������� ����������
	{
		cerr << "���������� ����������\n";
	}
}

void File::putStr(string str)   //����� ������ ������ � �����
{
	fo << str << endl;
}
