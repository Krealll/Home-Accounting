#pragma once
#include "Income.h"
#include"Expenses.h"
#include "Deposit.h"
#include "Interface.h"
#include"Currency.h"

class MainMenu   //����� �������� ����
{
private:
	Account budget;   //��������� ������� ������ ������ ����
public:
	MainMenu();  
	void launch();   //����� ������� �������� ����

	void chooseCurrency(Currency& curr);   //����� ������� ���� ������

	void budgetAnalysis();   //����� ������� ������� �����
	void depositAnalysis();   //����� ������� ������� ���������
	void inputBudget();   //���� ��������� �������

	template<typename T>
	void analysis(Interface<T>& I)   //��������� ����� ������� ������
	{
		T most;   //�������� ������ ��� ������
		I.load();   //��������� � ������ ���������� ������ �� �����
		cout << "\n";
		if (I.data.getRoot())   //���� ���� �� ���� 
			I.show(I.data);   //����� ������� ������
		else
		{
			cout << "\n ��� ������ ��� ������� � ������� " << I.Name(most) << endl;
			return;
		};
		double bdg = budget.getSum();   //��������� �������� �������
		double temp = findSum(I.data);   //������� �� ������ ������ ����� 
		most = findMost(I.data);   //������� ���������� ������ �� ���� �����
		cout.precision(2);
		cout << fixed;
		cout << "�������� :" << temp << " " << ((budget.getCrnc()).getName()) << endl;
		cout << "����� ������������ ��������� - " << most.getCategory() << ": "  << most.getSum() << " " << ((most.getCrnc()).getName()) << endl;
		bdg += temp;
		budget.setSum(bdg);
		cout << "� ������  ������� �������: " << budget.getSum() << " " << ((budget.getCrnc()).getName()) << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||\n\n";
	}
	template<>
	void analysis(Interface<Income>& I)   //������������� ��� ������ ������� �������
	{
		Income most;   //��������� ������ ��� ������
		I.load();   //��������� ������ ������ �� �����
		cout << "\n";
		if (I.data.getRoot())
			I.show(I.data);   //���� ���� �� ���� - ���������� �������
		else
		{
			cout << "\n ��� ������ ��� ������� � ������� " << I.Name(most) << endl;
			return;
		};
		double bdg = budget.getSum();   //���������� �������� ������� 
		double temp = findSum(I.data);   //������� ��������� �����
		most = findMost(I.data);   //����� �������� ��������� �������
		cout.precision(2);
		cout << fixed;
		cout << "��������� �����:" <<  temp<< " " << ((budget.getCrnc()).getName())<<endl;
		cout << "����� �������� ��������� - " << most.getCategory() <<": " << most.getSum() << " " << ((most.getCrnc()).getName()) << endl;
		bdg += temp;
		budget.setSum(bdg);
		cout << "� ������ ������� ������� �������: " << budget.getSum()<<" "<<((budget.getCrnc()).getName()) << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||\n\n";
	}
	template<>
	void analysis(Interface<Expenses>& I)   //������������� ��� ������ ������� �������
	{
		Expenses most;   //��������� ������ �������� ��� ������
		I.load();   //�������� ������ �������� �� �����
		cout << "\n";
		if (I.data.getRoot())
			I.show(I.data);   //���� ���� �� ���� - ����� ������� ��������
		else
		{
			cout << "\n ��� ������ ��� ������� � ������� " << I.Name(most) << endl;
			return;
		};
		double bdg = budget.getSum();   //���������� ��������  �������
		double temp = findSum(I.data);   //������� ��������� ������
		most = findMost(I.data);   //����� �������� ���������� �������
		cout.precision(2);
		cout << fixed;
		cout << "��������� ������:" << temp << " " << ((budget.getCrnc()).getName())<< endl;
		bdg -= temp;
		if (bdg < 0)   //���� �������� ������� 
		{
			cout << "�� ���������  ������. ������� �������, ���� ��������� �����." << endl;
		}
		cout << "����� ��������� ���������:" << most.getCategory() << ": " << most.getSum() << " " << ((most.getCrnc()).getName()) << endl;
		cout << "������� ������� ������� �� ������ ���������" << endl;
		budget.setSum(bdg);
		cout << "� ������ �������� ������� �������: " << budget.getSum() << " " << ((budget.getCrnc()).getName()) << endl;
		cout << "||||||||||||||||||||||||||||||||||||||||||||||||||\n\n";

	}

};

