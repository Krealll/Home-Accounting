#include "Inputexception.h"

bool isDigit(char c)   //�������� �� �����
{
	return (c > '0' && c < '9') ? true : false;
}

bool isSpace(char c)   //�������� �� ������
{
	return (c==' ') ? true : false;
}

bool isRus(char c)   //�������� �� ���������
{
	if (c > -65 && c < 0||c=='�'||c=='�')
		return true;
	else 
		return false;
}

bool isEng(char c)   //�������� �� ��������
{
	return ((c > 'A' && c < 'Z')||(c>'a'&&c<'z')) ? true : false;
}

bool isUpper(char c)   //�������� �� ������� ������� ��������
{
	 if (c > 64 && c < 91)
		return true;
	else return false;
}

Inputexception::~Inputexception()   //����������
{
}

int Inputexception::getCode()   //����� �������� ���� ������
{
	return exCode;
}

double setDouble(double d)   //������� ���������� �� �����
{
	double temp = round(d * 100);
	return temp / 100;
}
