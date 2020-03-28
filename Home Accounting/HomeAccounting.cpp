#include "MainMenu.h"
#include <Windows.h>

int main()
{
	system("color F1");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	MainMenu M;
	M.launch();
	return 0;
}