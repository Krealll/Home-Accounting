#include "Myexception.h"

Myexception::~Myexception()   //����������
{
}

string & Myexception::what()   //����� �������� ������ ������
{
	return errorStr;
}
