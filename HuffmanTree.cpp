
// Huffman tree
#include <iostream>
#include<stdlib.h>

using namespace std;

#define MAX_WEIGHT 1000
#define MAX_LEAFNODE 30
#define MAX_NODE MAX_LEAFNODE*2-1

typedef struct HNodeType
{
    int weight;
    int parent;
    int lchild,rchild;
}HNodeType;

void create(HNodeType *HuTree);

void create(HNodeType *HuTree)
{
    int n,m1,m2,x1,x2;

    //��parent==-1 ���ж��Ƿ���Ժϲ�
    for(int i = 0;i < MAX_NODE;++i)
    {
        HuTree[i].weight = 0;
        HuTree[i].rchild = HuTree[i].lchild = HuTree[i].parent = -1;
    }

    cout << "please input the Node's number :" << endl;
    cin >>n;
    for(int i = 0; i < n;++i)
    {
        cout <<"please input the " << i+1 << " Node's weight:" << endl;
        cin >> HuTree[i].weight;
    }

    //Ѱ����С�������� �ϲ���n+i ��λ���ϣ�����n+i ��Ϊѭ���Ľڵ��ظ�����
    for(int i = 0; i < n; ++i)
    {
        m1 = m2 = MAX_WEIGHT;
        x1 = x2 = 0;
        for(int j = 0; j < n+i; ++j)
        {
            if(HuTree[j].weight < m1 && HuTree[j].parent == -1)
            {
                x2 = x1;
                m2 = m1;
                x1 = j;
                m1 = HuTree[j].weight;
            }
            else if(HuTree[j].weight < m2 && HuTree[j].parent == -1)
            {
                x2 = j;
                m2 = HuTree[j].weight;
            }
        }
        HuTree[x1].parent = n+i;
        HuTree[x2].parent = n+i;
        HuTree[n+i].weight = HuTree[x1].weight + HuTree[x2].weight;
        HuTree[n+i].lchild = x1;
        HuTree[n+i].rchild = x2;
    }
}

int main()
{
    HNodeType *HuTree = (HNodeType*)malloc(sizeof(HNodeType)*MAX_NODE);
    create(HuTree);
    cout << "The N+1 value is :" << HuTree[7].weight << endl;
    return 0;
}
/* Test ��5(Nodes' number) 1 4 3 2 7

    ----------|----------
   | 1|4|3|2|7|3|6|10|17|.........
   |----------|----------
*/



