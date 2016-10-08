#include <iostream>
#include<map>

#include<math.h>

using namespace std;

#define MaxWeidgt 1000
#define MaxLeaf 6
#define MaxNode MaxLeaf*2-1

typedef struct
{
    char value;
    int weight;
    int parent;
    int lchild;
    int rchild;
    string code;
}HNodeType;

void  HuffmanTree(HNodeType HuTree[],int num)
{
    int x1,x2,m1,m2;

    for(int i = 0; i < MaxNode ;++i)
    {
        HuTree[i].weight = 0;
        HuTree[i].parent = -1;
        HuTree[i].lchild = -1;
        HuTree[i].rchild = -1;
        HuTree[i].code = "";
    }
    for(int i = 0 ; i < num; ++i)
    {
        cout << "please input the "<<i+1<<"Node's value:"<< endl;
        cin >> HuTree[i].value;
        cout << "please input the "<<i+1<<"Node's weight:"<< endl;
        cin >> HuTree[i].weight;
        //
    }
    for(int i =  0; i < num-1;i++)
    {
        m1=m2 = MaxWeidgt;
        x1=x2 = 0;
        for(int j = 0;j < num+i;++j)
        {
            if(HuTree[j].weight<m1 && HuTree[j].parent == -1)
            {
                m2=m1;
                x2=x1;
                m1=HuTree[j].weight;
                x1=j;
            }
            else if(HuTree[j].weight < m2 && HuTree[j].parent == -1)
            {
                m2 = HuTree[j].weight;
                x2=j;
            }
        }
        HuTree[x1].parent = num+i;
        HuTree[x2].parent = num+i;
        HuTree[num+i].weight = HuTree[x1].weight + HuTree[x2].weight;
        HuTree[num+i].lchild = x1;
        HuTree[num+i].rchild = x2;
    }
    cout << "Create HuffmanTree Over!" << endl;
}


void  HuffmanCode(HNodeType HuTree[],int position)
{
    if(HuTree[position].weight!=0)
    {
        string str0 ="0" ,str1 = "1";
        if(HuTree[position].lchild>=0)
        {
            HuTree[HuTree[position].lchild].code.append(HuTree[position].code);
            HuTree[HuTree[position].lchild].code.append(str0);
        }
        if(HuTree[position].rchild>=0)
        {
            HuTree[HuTree[position].rchild].code.append(HuTree[position].code);
            HuTree[HuTree[position].rchild].code.append(str1);
        }
        if(HuTree[position].lchild>=0)
            HuffmanCode(HuTree,HuTree[position].lchild);
        if(HuTree[position].rchild>=0)
            HuffmanCode(HuTree,HuTree[position].rchild);
    }
}

void HuffmanDeCode(HNodeType HuTree[],int num,string strCode)
{
    map<string,char> codeMap;
    for(int i = 0;i < num;i++)
        codeMap[HuTree[i].code] = HuTree[i].value;

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

}

void CodeEfficiency(HNodeType HuTree[],int num)
{
    double l=0,H=0,S=0;
    double weightSum = 0;
    for(int i = 0; i < num;++i)
        weightSum += HuTree[i].weight;
    for(int i = 0; i < num;++i)
    {
        l += HuTree[i].code.length()*HuTree[i].weight/weightSum;
        H += HuTree[i].weight/weightSum*log10(HuTree[i].weight/weightSum)/log10(2);
    }
    H = H * -1;
    S = H / l;
    cout << "the avg length is :     " << l << endl;
    cout << "the H value is :        " << H << endl;
    cout << "the Code efficiency is :" << S << endl;
}
int main()
{
    int num;
    string strCode;
    cout << "******Create HuffmanTree********" << endl;
    cout << "please input the number of the leaf Node:" << endl;
    cin >> num;
    HNodeType *HuTree = new HNodeType[MaxNode];
    HuffmanTree(HuTree,num);
    HuffmanCode(HuTree,num*2-2);

    cout << "********HuffmanCode*************" << endl;
    for(int i = 0;i< num; ++i)
        cout <<HuTree[i].value << "=" << HuTree[i].code << endl;
    cout << "output the codes Over !" << endl;

    cout << "********Code Efficiency*********" << endl;
    CodeEfficiency(HuTree,num);

    cout << "********DeCoding****************" << endl;

    cout << "please input the Code to Decoding..." << endl;
    cin >> strCode;

    cout << "the Decode content is :" ;
    HuffmanDeCode(HuTree,num,strCode);
    cout << endl;
    return 0;
}
