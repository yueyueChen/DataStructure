#include<iostream>
#include<string>
#include<map>

#include<math.h>
using namespace std;

#define MaxNode 10

typedef struct
{
	int weight;
	char value;
	string code;
}SNodeType;

void CreateNodes(SNodeType SNode[], int num)
{
	for (int i = 0; i < MaxNode; ++i)
	SNode[i].weight = 0;
	for (int i = 0; i < num; ++i)
	{
	cout << "please input the " << i + 1 << "Node's value:" << endl;
	cin >> SNode[i].value;
	cout << "please input the " << i + 1 << "Node's weight:" << endl;
	cin >> SNode[i].weight;
	}
	cout << "Create Nodes OVER ...." << endl;
}
void SwapDESC(SNodeType SNode[], int num)
{
	for (int i = 0; i < num; ++i)
	{
	int k = i;
	for (int j = i; j < num; ++j)
	{
	if (SNode[k].weight < SNode[j].weight)
	k = j;
	}
	SNodeType tmp;
	tmp.value = SNode[k].value;
	tmp.weight = SNode[k].weight;
	SNode[k].value = SNode[i].value;
	SNode[k].weight = SNode[i].weight;
	SNode[i].value = tmp.value;
	SNode[i].weight = tmp.weight;
	}
	cout << "SWAP Nodes DESC OVER ... " << endl;
}

int weightSum(SNodeType SNode[], int sbeg, int send)
{
	int sum = 0;
	for (int i = sbeg; i <= send; ++i)
	sum += SNode[i].weight;
	return sum;
}
int minValueOfSub(int subOfWeight[], int num)
{
	int k = 0;
	for (int i = 0; i < num; ++i)
	{
	if (subOfWeight[k] > subOfWeight[i])
	k = i;
	}
	return k;
}
int Devide(SNodeType SNode[], int sbeg, int send)
{

    int length = send - sbeg + 1;
    int subOfWeight[MaxNode];
    for (int i = 0; i < length-1; ++i)
    {
        subOfWeight[i] = weightSum(SNode, sbeg, sbeg + i) - weightSum(SNode, sbeg + i + 1, send);
        if (subOfWeight[i] < 0)
            subOfWeight[i] *= -1;
    }

    int devideKey = minValueOfSub(subOfWeight, length);

    string str0 = "0", str1 = "1";
    for (int i = sbeg; i <= sbeg + devideKey; i++)
        SNode[i].code.append(str0);
    for (int i = sbeg + devideKey + 1; i <= send; ++i)
        SNode[i].code.append(str1);

    if(sbeg!=sbeg+devideKey)
        Devide(SNode, sbeg, sbeg+devideKey);
    if(sbeg+devideKey+1!=send)
        Devide(SNode, sbeg+devideKey + 1, send);

}

void ShannonDeCode(SNodeType SNode[],int num,string strCode)
{
    map<string,char> codeMap;
    for(int i = 0;i < num;i++)
        codeMap[SNode[i].code] = SNode[i].value;

    string str;
    str.append(1,strCode[0]);

    for(int i = 0;i<=strCode.length();i++)
    {
        if(codeMap.find(str) !=codeMap.end())
        {
            cout << codeMap.find(str)->second ;
            str.clear();
            str.append(1,strCode[i+1]);

        }
        else
        {
            str.append(1,strCode[i+1]);
        }
    }
    cout << endl;

}

void CodeEfficiency(SNodeType SNode[],int num)
{
    double l=0,H=0,S=0;
    double weightSum = 0;
    for(int i = 0; i < num;++i)
        weightSum += SNode[i].weight;
    for(int i = 0; i < num;++i)
    {
        l += SNode[i].code.length()*SNode[i].weight/weightSum;
        H += SNode[i].weight/weightSum*log10(SNode[i].weight/weightSum)/log10(2);
    }
    H = H * -1;
    S = H / l;
    cout << "the avg length is :     " << l << endl;
    cout << "the H value is :        " << H << endl;
    cout << "the Code efficiency is :" << S << endl;
}

int main(int argc, char* argv[])
{
	int num;
	string str;
	cout << "please input the number of the Nodes:" << endl;
	cin >> num;
	SNodeType *SNode = new SNodeType[MaxNode];
	CreateNodes(SNode, num);
	SwapDESC(SNode, num);
	Devide(SNode,0,num-1);
	cout << "********ShannonCode********" << endl;
	for (int i = 0; i < num; ++i)
	cout << SNode[i].value <<"=" <<SNode[i].code << endl;

	cout << "********ShannonDeCode******" << endl;
	cout << "please input the Decode string.." << endl;
	cin>> str;
	ShannonDeCode(SNode,num,str);

	cout << "********CodeEfficiency******" << endl;
    CodeEfficiency(SNode,num);

	return 0;
}
