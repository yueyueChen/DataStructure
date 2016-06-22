#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include<iostream>
using namespace std;
#define MaxLength 100

//判断回文
typedef char Elemtype;
typedef struct seqStack
{
    Elemtype data[MaxLength];
    int top;
}seqStack;

void palindromeJudge(char A[],int N)
{
    seqStack * judgeStack = (seqStack*)malloc(sizeof(seqStack));
    judgeStack->top = -1;

    int i;
    for(i = 0; i < N; ++i)
    {
        ++judgeStack->top;
        judgeStack->data[judgeStack->top] = A[i];
        if(judgeStack->top >= MaxLength)
            printf("stack overflow !!\n");
    }
    //利用栈先入后出的性质，重新遍历一遍A[] 栈全部能弹出则是回文
    for(i = 0; i < N; ++i)
        if(A[i]==judgeStack->data[judgeStack->top])
            --judgeStack->top;
    if(judgeStack->top == -1)
        printf("the string is a palindrome !\n");
    else
        printf("the string is'nt a palindrome !\n");
    free(judgeStack);
}

int main()
{
    char *p1 = "i was able,elba saw i";
    palindromeJudge(p1,strlen(p1));

    char *p2 = "dfsfhvhgs";
    palindromeJudge(p2,strlen(p2));

	char *p3 = new char[];
	printf("please input a string:\n");
	cin >> p3;
	palindromeJudge(p3,strlen(p3));

    return 0;
}