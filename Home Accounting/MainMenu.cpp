#include "MainMenu.h"


MainMenu::MainMenu()   //���������� �� ���������
{
	Account();
}

void MainMenu::launch()   //����� ������� �������� ����
{
	cout << "����� ���������� � ��������� �� ����� �������� �����������!" << endl;
	int ans;   //���������� ��� ����������������� �����
	do 
	{
		cout << "������� ����:\n";
		cout << "1: ������ � ���������\n";
		cout << "2: ������ � ��������\n";
		cout << "3: ������ ������ �����\n";
		cout << "4: ������ �������\n";
		cout << "5: ������ �� ��������\n";
		cout << "6: ������ �������\n";
		cout << "7: ��������� �����\n";
		cout << "0: ����� �� ���������\n";

		inputNum(cin,ans, 0, 7);   //���������� ���� ����� � ���������
		switch (ans)
		{
		case 1:
		{
		Interface<Expenses> I;   //��������� ��������
		if (!I.subMenu())   //������ ������� ������������
			return;
		break;
		}
		case 2:
		{	
			Interface<Income> I;   //��������� �������
			if (!I.subMenu())   //������ ������� ������������
				return;
			break;
		}
		case 3:
		{
			inputBudget();   //���� ��������� ������� 
			system("CLS");
			break;
		}
		case 4:
		{
			try
			{
				budgetAnalysis();   //������ ������ ������� �������
			}
			catch (Myexception& obj)
			{
				cerr << "����������: " << obj.what() << endl;   //��������� �������������� ��������
				system("pause");
				break;
			}
			catch (...)
			{
				cerr << "���������� ����������\n";   //��������� �������������� ��������
			}
			system("pause");
			system("CLS");
			break;
			
		}
		case 5:
		{
			system("CLS");
			Interface<Deposit> I;   //��������� �������
			if (!I.start())   //������ ���� �������
				return;
			break;
		}
		case 6:
		{
			system("CLS");
			try
			{
				depositAnalysis();   //������ ������ ������� �������
			}
			catch (Myexception& obj)
			{
				cerr << "����������: " << obj.what() << endl;   //��������� �������������� ��������
				system("pause");
				break;
			}
			catch (...)
			{
				cerr << "���������� ����������\n";   //��������� �������������� ��������
				system("pause");
			}
			system("CLS");
			break;
		}
		case 7:
		{
			system("CLS");
		Interface<Currency> I;   //��������� ������
			if (!I.start())   //������ ���� ������
				return;
			break;
		}
		case 0:
		{
			exit(0);   //����� �� ���������
			break;
		}
		default:
			cout << "������������ ����" << endl;
			system("pause");
			break;
		}
	} while (1);
}

void MainMenu::chooseCurrency(Currency& curr)   //���� ������ ������
{
	int i;   //���������� ��� ������ ������
	Interface<Currency> temp;   //��������� ������ ��� � ������
	temp.load();   //�������� ������ �� ����� �����
	if (!temp.data.empty())   //���� ���� ��� �� ������
	{
		cout << "������� ������" << endl;
		makeTable(temp.data.begin(), temp.data.end());   //������ ������ ������ �������
	}
	else
		throw Myexception("��� ����� ��� ������");   //����� �������������� ��������
	cout << "\n�������� ������ �������:";
	inputNum(cin,i, 1, temp.data.size());   //���������� ���� ���������� � ���������
	typename Tree<Currency>::iterator it;   //�������� ��� ������� �� ������ �����
	it = temp.data.begin();   //������������� �������� �� ������ ������
	for (; i > 1; i--)
		++it;
	curr = *it;   //������������� ��������� ������
}

void MainMenu::budgetAnalysis()   //����� ������� �������
{
	if (!budget.getSum())   //���� �������� ������ �� �����
	{
		cout << "������ ������� �������� ������:" << endl;
		system("pause");
		system("CLS");
		inputBudget();   //���� ��������� �������
	}
	double temp = budget.getSum();   //������ �������� ������� �� ��������� ����������
	cout << "������������ ������ ������ �� ������:" << endl;
	Interface<Income> I1;   //��������� �������
	Interface<Expenses> I2;   //��������� ��������
	analysis(I1);   //����� ������� ������
	analysis(I2);   

	I1.flag = 1;   //��������� ����� � ���������� ��� ������������
	I2.flag = 1;
	I1.data.destroyTree(I1.data.getRoot());   //������� ����������� ������
	I2.data.destroyTree(I2.data.getRoot());

	analysis(I1);   //����� ������� ������
	analysis(I2);
	budget.setSum(temp);   //���������� ����������� �������� ������� ��� ���������� ������
}

void MainMenu::depositAnalysis()   //����� ������� �������
{
	if (!budget.getSum())   //���� ������ �� �����
	{
		cout << "������ ������� �������� ������:" << endl;
		system("pause");
		system("CLS");
		inputBudget();   //���� �������
	}
	Interface<Deposit> I;   //��������� �������
	I.load();   //�������� ������ �� ����� �� ��������
	cout << "\n";
	if (I.data.getRoot())
	{
		double sum = findSum(I.data);   //����� ���������� ������ �� �������
		I.show(I.data);   //����� ������ ������ 
		cout << "����� ��������� ������ �������, ������ ������� ��������:" << sum << " " << ((budget.getCrnc()).getName()) << endl;
		cout << "� ������ ������ ������� ������� �������: " << budget.getSum() + sum << endl;
	}
	else
	{
		cout << "\n ��� ������ ��� ������� � ������� �������"<< endl;
		return;
	};
	system("pause");
}

void MainMenu::inputBudget()   //����� ����������� ����� ��������� �������
{
	cout << "������� ���������� ������ � BYN" << endl;
	input(cin,budget);   //������� ����������� �����
	Currency curr("BYN", 1.0);   //����� ������ ��������� �������
	this->budget.setCrnc(curr);
}

