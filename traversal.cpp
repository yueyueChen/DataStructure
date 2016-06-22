#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

typedef struct BiTNode
{
	char data[10];
	struct BiTNode *lchild,*rchild;
}BiTNode;
typedef BiTNode * BiTree;

BiTree createBiTree();
void preOrderTraversal(BiTree root);
void inOrderTraversal(BiTree root);
void postOrderaTraversal(BiTree root);
BiTree changeLrChild(BiTree root);

BiTree createBiTree()
{
	BiTNode *p;
	char *str = new char[];
	cout << "please input a string :\n";
	cin >> str;
	if(str[0] == '0')
		return NULL;
	p = (BiTNode*)malloc(sizeof(BiTNode));
	strcpy(p->data,str);
	p->lchild = createBiTree();
	p->rchild = createBiTree();

	return p;
}
void inOrderTraversal(BiTree root)
{
	if(root == NULL)
		return;
	inOrderTraversal(root->lchild);
	printf("%s\n",root->data);
	inOrderTraversal(root->rchild);
}
void preOrderTraversal(BiTree root)
{
	if(root == NULL)
		return;
	printf("%s\n",root->data);
	preOrderTraversal(root->lchild);
	preOrderTraversal(root->rchild);
}
void postOrderTraversal(BiTree root)
{
	if(root == NULL)
		return;
	postOrderTraversal(root->lchild);
	postOrderTraversal(root->rchild);
	printf("%s\n",root->data);
}
BiTree changeLrChild(BiTree root)
{
	if(root == NULL)
		return NULL;
	BiTNode * p = (BiTree)malloc(sizeof(BiTNode));
	p = root->lchild;
	root->lchild = root->rchild;
	root->rchild = p;
	changeLrChild(root->lchild);
	changeLrChild(root->rchild);

	return root;
}
int main()
{
	BiTree T = createBiTree();
	printf("the preOrderTraversal is :\n");
	preOrderTraversal(T);
	printf("the inOrderTraversal is :\n");
	inOrderTraversal(T);
	printf("the postOrderTraversal is :\n");
	postOrderTraversal(T);
	T = changeLrChild(T);
	printf("****change lchild and rchild..******\n");
	printf("the preOrderTraversal is :\n");
	preOrderTraversal(T);
	printf("the inOrderTraversal is :\n");
	inOrderTraversal(T);
	printf("the postOrderTraversal is :\n");
	postOrderTraversal(T);
	return 0;
}
