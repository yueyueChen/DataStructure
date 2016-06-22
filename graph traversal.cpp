#include <stdlib.h>

#include <iostream>
using namespace std;

#define MAX_VERTEX_NUM 20
bool visited[MAX_VERTEX_NUM];
typedef struct ArcNode
{
    int adjvex;
    struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode
{
    char *data;
    //num 存储结点的下标信息 与arcNode中的adjvex相对应
    int num;
    ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertex;
    int vexnum;
    int arcnum;
}Graph;

//队列的类型定义
typedef struct
{
    int data[MAX_VERTEX_NUM];
    int QueueFront,QueueRear;
}Queue;

Graph *create();
Queue *EnQueue(Queue *Q,int x);
Queue* DeQueue(Queue *Q,int &u);
int nextAdjvex(Graph *G,int v,int w);
void DFS(Graph *G,int v);
void DFStraverse(Graph *G);
void BFS(Graph *G);

Graph *create()
{
    Graph *G = (Graph*)malloc(sizeof(Graph));
    cout << "please input the node number and the arc number :" << endl;
    cin >> G->vexnum >> G->arcnum;
    for(int i = 0; i < G->vexnum; ++i)
    {
        G->vertex[i].data = (char*)malloc(sizeof(char)*10);
        cout <<"please input the "<<i+1<< " node value:" << endl;
        cin >> G->vertex[i].data;
        G->vertex[i].num = i;
        G->vertex[i].firstarc = NULL;
    }
    for(int i = 0;i < G->arcnum; ++i)
    {
        int j,k;
        cout << "please input the arcs ..." << endl;
        cin >> j >> k;
        ArcNode *s = (ArcNode*)malloc(sizeof(ArcNode));
        s->adjvex = j-1;
        s->nextarc = G->vertex[k-1].firstarc;
        G->vertex[k-1].firstarc = s;
        s = (ArcNode*)malloc(sizeof(ArcNode));
        s->adjvex = k-1;
        s->nextarc = G->vertex[j-1].firstarc;
        G->vertex[j-1].firstarc = s;
    }
    return G;
}
Queue *EnQueue(Queue *Q,int x)
{
    if((Q->QueueRear+1)%MAX_VERTEX_NUM == Q->QueueFront)
        cout << "Queue overflow !!" << endl;
    else
    {
        //优化 对于还在队列中没有被访问过的 防止重复进入队列
        visited[x] = true;
        Q->data[Q->QueueRear] = x;
        Q->QueueRear = (Q->QueueRear+1)%MAX_VERTEX_NUM;
    }
    return Q;
}
Queue* DeQueue(Queue *Q,int &u)
{
    u = Q->data[Q->QueueFront];
    Q->QueueFront = (Q->QueueFront+1)%MAX_VERTEX_NUM;
    return Q;
}


//实现DFS的代码
int nextAdjvex(Graph *G,int v,int w)
{
    ArcNode *p = G->vertex[v].firstarc;
    while(p)
    {
        if(p->adjvex != w)
            p = p->nextarc;
        else
            break;
    }
    if(p == NULL)
        return -1;
    if(p->nextarc)
        return p->nextarc->adjvex;
    else
        return -1;
}
void DFS(Graph *G,int v)
{
    visited[v] = true;
    cout << "DFS traversal : " << G->vertex[v].data << endl;
    if(!G->vertex[v].firstarc)
        return;
    for(int w = G->vertex[v].firstarc->adjvex;w != -1 ; w = nextAdjvex(G,v,w))
        if(!visited[w])
            DFS(G,w);
}
void DFStraverse(Graph *G)
{
    for(int i = 0 ; i < G->vexnum; ++i)
        visited[i] = false;
    for(int i = 0 ; i < G->vexnum;++i)
        if(!visited[i])
            DFS(G,i);
}

//实现BFS的代码
void BFS(Graph *G)
{
    Queue *Q = (Queue*)malloc(sizeof(Queue));
    Q->QueueFront = Q->QueueRear = 0;

    for(int i = 0 ; i < G->vexnum; ++i)
        visited[i] = false;
    for(int i = 0 ; i < G->vexnum; ++i)
    {
        if(!visited[i])
        {
            Q = EnQueue(Q,i);
            while(Q->QueueFront != Q->QueueRear)
            {
                int u = 0;
                Q = DeQueue(Q,u);
                cout << "BFS traversal :" << G->vertex[u].data << endl;
                if(!G->vertex[u].firstarc)
                    return;
                for(int w = G->vertex[u].firstarc->adjvex; w != -1 ; w = nextAdjvex(G,u,w))
                    if(!visited[w])
                    Q = EnQueue(Q,w);
            }
        }
    }
}

int main()
{
    Graph *G = create();
    DFStraverse(G);
    cout << ".......我是分割线......."  << endl;
    BFS(G);
}












