// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<vector>

using namespace std;

typedef struct {
	int pid;
	int runTime;
	int priority;
}PCB;

int sortProcess(PCB *processes, int num);
PCB runProcess(PCB process);
PCB *initialPCB(int num);
void run(PCB *processes, int num);
vector<int> processOrder;

int _tmain(int argc, _TCHAR* argv[])
{
	int num;
	cout << "please input the processes' number:" << endl;
	cin >> num;
	PCB *processes = initialPCB(num);
	run(processes, num);
	system("pause");
	return 0;
}

PCB *initialPCB(int num)
{
	PCB *processes = new PCB[num];
	for (int i = 0; i != num; ++i)
	{
		processes[i].pid = i + 1;
		cout << "please input the " << i + 1 << " process's priority:" << endl;
		cin >> processes[i].priority;
		cout << "please input the " << i + 1 << " process's runtime:" << endl;
		cin >> processes[i].runTime;
	}
	return processes;
}


int sortProcesses(PCB *processes, int num)
{
	int zeroRunTimeCount = 0;
	for (int i = 0; i < num; ++i)
	if (processes[i].runTime == 0)
		zeroRunTimeCount++;
	for (int i = 0; i < num; ++i)
	{
		int k;
		if (processes[i].runTime == 0)
		{
			int tmp = 0;
			k = i;
			for (int j = i; j < num; ++j)
			{

				if (processes[j].priority > tmp && processes[j].runTime != 0)
				{
					k = j;
					tmp = processes[k].priority;
				}
			}
		}
		else if (processes[i].runTime != 0)
		{
			k = i;
			for (int j = i; j < num; ++j)
			{
				if (processes[j].priority > processes[k].priority && processes[j].runTime != 0)
					k = j;
			}
		}
		PCB tmp;
		tmp.pid = processes[i].pid;
		processes[i].pid = processes[k].pid;
		processes[k].pid = tmp.pid;
		tmp.runTime = processes[i].runTime;
		processes[i].runTime = processes[k].runTime;
		processes[k].runTime = tmp.runTime;
		tmp.priority = processes[i].priority;
		processes[i].priority = processes[k].priority;
		processes[k].priority = tmp.priority;
	}
	return zeroRunTimeCount;
}
PCB runProcess(PCB process)
{
	process.priority--;
	process.runTime--;
	if (process.runTime >= 0)
		cout << "  |  " << process.pid << "   |  " << process.priority << "          |    " << process.runTime << "     |";
	if (process.runTime == 0)
	{
		cout << " process " << process.pid << " over..." << endl;
		processOrder.push_back(process.pid);
	}
	else
		cout << endl;
	return process;
}

void run(PCB *processes, int num)
{
	cout << "  | PID  |  PRIORITY    |  RUNTIME" << endl;
	while (num > 0)
	{
		num -= sortProcesses(processes, num);
		processes[0] = runProcess(processes[0]);
	}
	cout << "the process's over order is :" << endl;
	for (auto &c : processOrder)
		cout << c << "\t";
	cout << endl;
}




















