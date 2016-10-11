// Dichotomie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<math.h>
#include <iostream>

#define MaxOrder 10

using namespace std;

double Function(double Polynimial[], int order,double x)
{
	double sum = 0;
	for (int i = order; i >= 0; --i)
	{
		sum += Polynimial[i] * pow(x, i);
	}
		return sum;
}

void dichotomie(int order)
{
	double *Polynimial = new double[MaxOrder];
	double startPoint, stopPoint;
	double deviation;
	for (int i = 0; i <= order; ++i)
	{
		cout << "please input the " << i << "order's cefficient:" << endl;
		cin >> Polynimial[i];
	}
	cout << "please input the start point's value:" << endl;
	cin >> startPoint;
	cout << "please input the stop point's value:" << endl;
	cin >> stopPoint;
	cout << "please input the devaition:" << endl;
	cin >> deviation;


	if (Function(Polynimial, order, startPoint)*Function(Polynimial, order, stopPoint) > 0)
	{
		cout << "There is No value in [" << startPoint << "," << stopPoint << "]." << endl;
		return;
	}

	int count = -1;
	double tmp;
	while(stopPoint - startPoint > deviation)
	{
		tmp = (startPoint + stopPoint) / 2;
		if (Function(Polynimial, order, tmp) == 0)
		{
			cout << "the exact root is :" << tmp << endl;
			return;
		}
		else if (Function(Polynimial, order, startPoint)*Function(Polynimial, order, tmp) < 0)
			stopPoint = tmp;
		else if (Function(Polynimial, order, tmp)*Function(Polynimial, order, stopPoint) < 0)
			startPoint = tmp;
		count++;
	}
	tmp = (startPoint + stopPoint) / 2;
	cout << "the Count if :" << count << endl;
	cout << "the root  is :" << tmp << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int num;
	cout << "please input the max Order of the f(x):" << endl;
	cin >> num;
	dichotomie(num);
	system("pause");
	return 0;
}

