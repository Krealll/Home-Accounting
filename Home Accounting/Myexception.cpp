#include "Myexception.h"

Myexception::~Myexception()   //деструктор
{
}

string & Myexception::what()   //метод возврата строки ошибки
{
	return errorStr;
}
