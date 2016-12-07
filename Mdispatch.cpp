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

//����ģ�飬���̵���ģ�顢�������ģ�飬���̵���ģ��ɶ������У����ڽ��̵���ģ�����������������
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

		//�Ƚ��пռ���գ���Ȼ�������ִ������

		// ###���ڶ����ж���ʣ��ʱ��0�Ľ��̽�����յ��߼��ж�ʵ�֡�
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
				//ѭ���иı���vectorԪ�� i������ʧЧ ����������գ����������
			}
			else
				i++;//���ֲ�ͬ������µ�����end()�ķ���
		}
		//remove_if(processes.begin(),processes.end(),[](const Process p){if(p.runTime<=0) return true;});

		//����µĽ��̣����ý������е�ʱ��Ƭ
		int runTime;
		if (!processes.empty())
		{

			cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n" << endl;
			cout << "����Ҫ���е�ʱ��Ƭ(����-1������µĽ���,����-2��ֹ����):" << endl;
			cin >> runTime;
			if (runTime == -2)
				break;
			if (runTime == -1)
			{
				addNewProcesses(processes);
				cout << "����Ҫ���е�ʱ��Ƭ��" << endl;
				cin >> runTime;
			}
		}
		else
		{
			cout << "��û�о���̬�Ľ���...." << endl;
			stable_sort(freePartTable.begin(), freePartTable.end(), [](const FreePart t1, const FreePart t2) {return t1.startAddress < t2.startAddress; });

			if (freePartTable.capacity() > 1)
			{
				freePartTable.clear();
				freePartTable.push_back(FreePart(0, MaxAddress));
			}
			printTable(freePartTable);
			addNewProcesses(processes);
			cout << "����Ҫ���е�ʱ��Ƭ:" << endl;
			cin >> runTime;
		}
		//�����ڴ�ռ�
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
	cout << "------------*���з����� *---------------" << endl;
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
		//ʱ��Ϊ��Ľ��̳����з���run()���������ʹ��freepartTable���л��գ����ٲ���Ҫ�Ĵ��Ρ�
	}
	cout << endl;
	cout << "------------*���̶��б� *---------------" << endl;
	cout << "|PID|Priority|LastTime|startAddress|Size|  " << endl;
	for (auto c : processes)
		cout << c.PID << "\t" << c.priority << "\t" << c.runTime << "\t" << c.startAddress << " \t\t" << c.size << endl;
}

void addNewProcesses(vector<Process> &processes)
{
	int num;
	cout << "����Ҫ��ӵĽ��̵ĸ���:" << endl;
	cin >> num;
	int _PID, _runTime, _priority, _size;
	for (int i = 0; i < num; ++i)
	{
		cout << "�������� PID ����ʱ�� ���ȼ� ��С:" << endl;
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
	cout << "ѡ�����IDΪ" << process.PID << "�Ľ���ʹ�õĿ��з������䷽ʽ:" << endl;
	cout << "(1)������Ӧ�㷨" << endl;
	cout << "(2)�����Ӧ�㷨" << endl;
	cout << "(3)���Ӧ�㷨" << endl;
	cin >> method;
	if (method == 1)
		firstFitAllocate(freePartTable, process);
	else if (method == 2)
		bestFitAllocate(freePartTable, process);
	else
		worstFitAllocate(freePartTable, process);
}
//������˳����ҵ�һ������Ҫ��Ŀռ�
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
	cout << "�����ڴ�ʧ�ܣ�δ�ҵ�����Ҫ��������ռ䣡�ý��̽����߳�����...." << endl;
}
//������Ҫ������С�Ŀռ����
void bestFitAllocate(vector<FreePart>&freePartTable, Process &process)
{
	//��sizeΪ�Ƚ����������ٽ��з���
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
//��ѡ���ķ����ָ�ʹ��
void worstFitAllocate(vector<FreePart>&freePartTable, Process &process)
{
	stable_sort(freePartTable.begin(), freePartTable.end(), [](const FreePart t1, const FreePart t2) {return t1.size > t2.size; });
	
	if (freePartTable.front().size < process.size)
		cout << "�����ڴ�ʧ�ܣ�δ�ҵ�����Ҫ��������ռ䣡�ý��̽����߳�����...." << endl;
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
