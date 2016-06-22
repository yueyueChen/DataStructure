#include <stdio.h>
#include <stdlib.h>

struct TreeNode;
typedef struct TreeNode * Position;
typedef struct TreeNode * SearchTree;
typedef int Elemtype;

struct TreeNode
{
    Elemtype Element;
    SearchTree Left;
    SearchTree Right;
};

SearchTree MakeEmpty(SearchTree T);
Position Find(Elemtype x,SearchTree T);
Position FIndMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(Elemtype x,SearchTree T);
SearchTree Delete(Elemtype x, SearchTree T);

SearchTree MakeEmpty(SearchTree T)
{
    if(T!=nullptr)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return nullptr;
}
Position Find(Elemtype x,SearchTree T)
{
    if(T == nullptr)
        return nullptr;
    if(x < T->Element)
        return Find(x,T->Left);
    else if(x > T->Element)
        return Find(x,T->Right);
    else
        return T;
}
Position FindMax(SearchTree T)
{
    if(T == nullptr)
        return nullptr;
    else if(T->Right == nullptr)
        return T;
    else
        return FindMax(T->Right);
}
Position FIndMin(SearchTree T)
{
    if(T == nullptr)
        return nullptr;
    else if(T->Left==nullptr)
        return T;
    else
        return FIndMin(T->Left);
}
SearchTree Insert(Elemtype x,SearchTree T)
{
    if(T == nullptr)
    {
        T = (SearchTree)malloc(sizeof(struct TreeNode));
        T->Element = x;
        T->Left = T->Right = nullptr;
    }
    else if(x < T->Element)
        T->Left = Insert(x,T->Left);
    else if(x > T->Element)
        T->Right = Insert(x,T->Right);
    return T;
}
SearchTree Delete(Elemtype x,SearchTree T)
{
    Position TmpCell;

    if(T == nullptr)
        printf("Element not found.");
    else if(x < T->Element)
        T->Left = Delete(x,T->Left);
    else if(x > T->Element)
        T->Right = Delete(x,T->Right);

    else if(T->Left&&T->Right)
    {
        TmpCell = FIndMin(T->Right);
        T->Element = TmpCell->Element;
        T->Right = Delete(T->Element,T->Right);
    }

    else
    {
        TmpCell = T;
        if(T->Left == nullptr)
            T = T->Right;
        else if(T->Right == nullptr)
            T = T->Left;
        free(TmpCell);
    }
    return T;
}
int main()
{
    SearchTree T = (SearchTree)malloc(sizeof(TreeNode));
    T = nullptr;
    //MakeEmpty(T);
    T = Insert(4,T);
    T = Insert(9,T);
    T = Insert(3,T);
    T = Insert(1,T);
    T = Insert(2,T);
    printf("%d\n",T->Left->Element);
    T = Delete(3,T);
    printf("%d",T->Left->Element);

    return 0;
}


















