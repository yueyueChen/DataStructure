// MMdispatch.cpp : Defines the entry point for the console application.
//

// MMDispatch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define MaxAddress 2000

typedef struct FreePart
{
	int startAddress;
	int size;

	FreePart(int _startAddress, int _size)
	{
		startAddress = _startAddress;
		size = _size;
	}
}FreePart;

typedef struct Process
{
	int PID;
	int runTime;
	int priority;
	int startAddress;
	int size;

	Process(int _PID, int _runTime, int _priority, int _startAddress, int _size = 0)
	{
		PID = _PID;
		runTime = _runTime;
		priority = _priority;
		startAddress = _startAddress;
		size = _size;
	}
}Process;

//两个模块，进程调度模块、主存分配模块，进程调度模块可独立运行，不在进程调度模块加入主存分配的内容
void run(vector<FreePart> &freePartTable, vector<Process>&processes);
void MFree(vector<FreePart> &freePartTable, Process &process);
void printTable(vector<FreePart> &table);

void MAllocate(vector<FreePart>&freePartTable, Process &process);

void firstFitAllocate(vector<FreePart>&freePartTable, Process &process);
void bestFitAllocate(vector<FreePart>&freePartTable, Process &process);
void worstFitAllocate(vector<FreePart>&freePartTable, Process &process);

void addNewProcesses(vector<Process>&processes);
void runProcess(vector<Process> &process, int time);

int main()
{
	vector<FreePart> freePartTable;
	freePartTable.push_back(FreePart(0, MaxAddress));

	vector<Process> processes;
	addNewProcesses(processes);

	run(freePartTable, processes);
	return 0;
}

void run(vector<FreePart> &freePartTable, vector<Process>&processes)
{
	while (true)
	{

		//先进行空间回收，不然分配会出现错误情况

		// ###对于队列中都是剩余时间0的进程进行清空的逻辑判断实现。
		for (auto i = processes.begin(); i != processes.end();)
		{
			if ((*i).runTime ==0)
			{
				
				if (processes.size() > 1)
				{
					MFree(freePartTable, *i);
					i = processes.erase(i);				
				}
				else
				{
					MFree(freePartTable, (*i));
					processes.clear();
					break;
				}
				//循环中改变了vector元素 i迭代器失效 或者容器清空；程序崩掉了
			}
			else
				i++;//两种不同的情况下迭代到end()的方法
		}
		//remove_if(processes.begin(),processes.end(),[](const Process p){if(p.runTime<=0) return true;});

		//添加新的进程，设置进程运行的时间片
		int runTime;
		if (!processes.empty())
		{

			cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
			cout << "输入要运行的时间片(输入-1来添加新的进程,输入-2终止程序):" << endl;
			cin >> runTime;
			if (runTime == -2)
				break;
			if (runTime == -1)
			{
				addNewProcesses(processes);
				cout << "输入要运行的时间片：" << endl;
				cin >> runTime;
			}
		}
		else
		{
			cout << "已没有就绪态的进程...." << endl;
			stable_sort(freePartTable.begin(), freePartTable.end(), [](const FreePart t1, const FreePart t2) {return t1.startAddress < t2.startAddress; });

			if (freePartTable.capacity() > 1)
			{
				freePartTable.clear();
				freePartTable.push_back(FreePart(0, MaxAddress));
			}
			printTable(freePartTable);
			addNewProcesses(processes);
			cout << "输入要运行的时间片:" << endl;
			cin >> runTime;
		}
		//分配内存空间
		for (auto &s : processes)
			if (s.startAddress == -1)
				MAllocate(freePartTable, s);

		stable_sort(freePartTable.begin(), freePartTable.end(), [](const FreePart t1, const FreePart t2) {return t1.startAddress < t2.startAddress; });
		runProcess(processes, runTime);
		printTable(freePartTable);
	}
}


void printTable(vector<FreePart> &table)
{
	stable_sort(table.begin(), table.end(), [](const FreePart t1, const FreePart t2) {return t1.startAddress < t2.startAddress; });

	cout << endl;
	cout << "------------*空闲分区表 *---------------" << endl;
	cout << "| ID    |   STARTADDRESS  |   Size      |" << endl;
	int count = 1;
	for (auto c : table)
		cout << count++ << " \t    " << c.startAddress << "   \t\t" << c.size << endl;
	cout << endl;

}

void runProcess(vector<Process> &processes, int time)
{
	for (int i = 0; i < time; ++i)
	{
		for (auto i = processes.begin(); i != processes.end(); ++i)
			if ((*i).startAddress == -1)
				processes.erase(i);

		stable_sort(processes.begin(), processes.end(), [](const Process p1, const Process p2){return p1.priority>p2.priority; });
		if (processes.front().runTime > 0)
		{
			processes.front().priority--;
			processes.front().runTime--;
		}
		//时间为零的进程出队列放在run()函数里，方便使用freepartTable进行回收，减少不必要的传参、
	}
	cout << endl;
	cout << "------------*进程队列表 *---------------" << endl;
	cout << "|PID|Priority|LastTime|startAddress|Size|  " << endl;
	for (auto c : processes)
		cout << c.PID << "\t" << c.priority << "\t" << c.runTime << "\t" << c.startAddress << " \t\t" << c.size << endl;
}

void addNewProcesses(vector<Process> &processes)
{
	int num;
	cout << "输入要添加的进程的个数:" << endl;
	cin >> num;
	int _PID, _runTime, _priority, _size;
	for (int i = 0; i < num; ++i)
	{
		cout << "依次输入 PID 运行时间 优先级 大小:" << endl;
		cin >> _PID >> _runTime >> _priority >> _size;
		processes.push_back(Process(_PID, _runTime, _priority, -1, _size));
	}
}

void MFree(vector<FreePart> &freePartTable, Process &process)
{
	int freeFlag = 0;
	for (vector<FreePart>::iterator i = freePartTable.begin(); i != freePartTable.end(); ++i)
	{
		if ((*i).startAddress + (*i).size == process.startAddress)
		{
			(*i).size += process.size;
			process.startAddress = -1;
			if (i + 1 != freePartTable.end() && ((*(i + 1)).startAddress == (*i).startAddress + (*i).size))
			{
				(*i).size += (*(i + 1)).size;
				freePartTable.erase(i + 1);
			}
			freeFlag = 1;
			break;
		}
		else if ((*i).startAddress == process.startAddress + process.size)
		{
			(*i).startAddress = process.startAddress;
			(*i).size += process.size;
			process.startAddress = -1;
			if (i != freePartTable.begin() && (*(i - 1)).startAddress + (*(i - 1)).size == (*i).startAddress)
			{
				(*(i - 1)).size += (*i).size;
				freePartTable.erase(i);
			}
			freeFlag = 1;
			break;
		}
	}
	if (freeFlag == 0)
		freePartTable.push_back(FreePart(process.startAddress, process.size));
}

void MAllocate(vector<FreePart>&freePartTable, Process &process)
{
	int method;
	cout << "选择进程ID为" << process.PID << "的进程使用的空闲分区分配方式:" << endl;
	cout << "(1)最先适应算法" << endl;
	cout << "(2)最佳适应算法" << endl;
	cout << "(3)最坏适应算法" << endl;
	cin >> method;
	if (method == 1)
		firstFitAllocate(freePartTable, process);
	else if (method == 2)
		bestFitAllocate(freePartTable, process);
	else
		worstFitAllocate(freePartTable, process);
}
//从链首顺序查找到一个满足要求的空间
void firstFitAllocate(vector<FreePart>&freePartTable, Process &process)
{
	for (auto i = freePartTable.begin(); i != freePartTable.end(); ++i)
	{
		if ((*i).size == process.size)
		{
			process.startAddress = (*i).startAddress;
			freePartTable.erase(i);
			return;
		}
		else if ((*i).size > process.size)
		{
			process.startAddress = (*i).startAddress;
			(*i).startAddress += process.size;
			(*i).size -= process.size;
			return;
		}
	}
	cout << "申请内存失败！未找到满足要求的连续空间！该进程将被踢出队列...." << endl;
}
//能满足要求且最小的空间分配
void bestFitAllocate(vector<FreePart>&freePartTable, Process &process)
{
	//以size为比较条件排序再进行分配
	stable_sort(freePartTable.begin(), freePartTable.end(), [](const FreePart t1, const FreePart t2) {return t1.size < t2.size; });
	for (auto i = freePartTable.begin(); i != freePartTable.end(); ++i)
	{
		if ((*i).size == process.size)
		{
			process.startAddress = (*i).startAddress;
			freePartTable.erase(i);
			return;
		}
		else if ((*i).size > process.size)
		{
			process.startAddress = (*i).startAddress;
			(*i).startAddress += process.size;
			(*i).size -= process.size;
			return;
		}
	}
}
//挑选最大的分区分割使用
void worstFitAllocate(vector<FreePart>&freePartTable, Process &process)
{
	stable_sort(freePartTable.begin(), freePartTable.end(), [](const FreePart t1, const FreePart t2) {return t1.size > t2.size; });
	
	if (freePartTable.front().size < process.size)
		cout << "申请内存失败！未找到满足要求的连续空间！该进程将被踢出队列...." << endl;
	else if (freePartTable.front().size == process.size)
	{
		process.startAddress = freePartTable.front().startAddress;
		freePartTable.erase(freePartTable.begin());
	}
	else if (freePartTable.front().size > process.size)
	{
		process.startAddress = freePartTable.front().startAddress;
		freePartTable.front().startAddress += process.size;
		freePartTable.front().size -= process.size;
	}
}
