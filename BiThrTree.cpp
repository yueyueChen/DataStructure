#include <iostream>
#include <stdlib.h>
using namespace std;

typedef char ElemType;
typedef struct BiThrNode
{
    ElemType data;
    struct BiThrNode *lchild,*rchild;
    int ltag,rtag;
}BiThrNode;
typedef BiThrNode *BiThrTree;

BiThrTree create();
BiThrTree InOrderThr(BiThrTree T);
void InThreading(BiThrTree T);
BiThrTree InOrderPre(BiThrTree T);
BiThrTree InOrderNext(BiThrTree T);
void InOrderTracersal(BiThrTree T);

BiThrTree pre;

BiThrTree create()
{
    BiThrTree T;
    char value;
    cout << "please input a Node's value :" << endl;
    cin >> value;
    if(value != '#')
    {
        T = (BiThrTree)malloc(sizeof(BiThrNode));
        T->ltag = T->rtag = 0;

        T->data = value;
        T->lchild = create();
        if(T->lchild == NULL)
            T->ltag = 1;
        T->rchild = create();
        if(T->rchild == NULL)
            T->rtag = 1;
    }
    else
        T = NULL;
    return T;
}
BiThrTree InOrderThr(BiThrTree T)
{
   BiThrTree head = (BiThrTree)malloc(sizeof(BiThrNode));
   head->ltag = 0;
   head->rtag = 1;
   head->rchild = head;
   if(T ==NULL)
        head->lchild = head;
    else
    {
        head->lchild = T;
        pre = head;
        InThreading(T);
        pre->rchild = head;
        pre->rtag = 1;
        head->rchild = pre;
    }
    return head;
}
void InThreading(BiThrTree T)
{
    if(T)
    {
        InThreading(T->lchild);
        if(!T->lchild)
        {
            T->ltag =1;
            T->lchild = pre;
        }
        //左孩子与右孩子不对等。并非同时线索化
        if(!pre->rchild)
        {
            pre->rtag = 1;
            pre->rchild = T;
        }
        pre = T;
        InThreading(T->rchild);
    }
}
BiThrTree InOrderPre(BiThrTree T)
{
    if(T->ltag == 1)
        return T->lchild;
    BiThrTree p = T->lchild;
    while(p->rchild == 0)
        p = p->lchild;
    return p;
}
BiThrTree InOrderNext(BiThrTree T)
{
    if(T->rtag == 1)
        return T->rchild;
    BiThrTree p = T->rchild;
    while(p->ltag == 0)
        p = p->lchild;
    return p;
}
void InOrderTracersal(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;
    if(p != T)
    {
        while(p->ltag == 0)
            p = p->lchild;
        do
        {
            cout << p->data << endl;
            p = InOrderNext(p);
        }while(p!=T);
    }
}
int main()
{
    BiThrTree T = create();
    T = InOrderThr(T);
    InOrderTracersal(T);
    return 0;
}






