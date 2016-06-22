//  十字链表
#include <stdio.h>
#include <stdlib.h>

typedef int Elemtype;
typedef struct OrthogonalNode
{
    int row,col,value;
    struct OrthogonalNode * down,*right;
} OrthogonalNode;
typedef OrthogonalNode * OrthogonalList;

OrthogonalList createOrthogonalList();

int main()
{
    OrthogonalList H = createOrthogonalList();
    printf( "Test Over !!\n");
    printf("%d  %d",H->down->right->value,H->down->down->right->value);
    return 0;
}
/*   eg: row = 4 ,column = 3
*          1    2    3
*  0  H---H5---H6---H7
*     |
*  1  H1--
*     |
*  2  H2--
*     |
*  3  H3--
*     |
*  4  H4--
*
*/
OrthogonalList createOrthogonalList()
{
    int i,j,rowNumber,colNumber,NotZeroNumber;
    Elemtype elementV;
    OrthogonalList H = (OrthogonalList)malloc(sizeof(OrthogonalNode));

    printf("please input the rowNumber ,the colNumber and the NotZeroNumber....\n");
    scanf("%d,%d,%d",&rowNumber,&colNumber,&NotZeroNumber);
    H->row = rowNumber;
    H->col = colNumber;

    OrthogonalNode *p,*q,*r,*hd[rowNumber+colNumber+1];
    hd[0] = H;
    for(i = 1;i <= rowNumber; ++i)
    {
        p = (OrthogonalList)malloc(sizeof(OrthogonalNode));
        p->row = 0;
        p->col = 0;
        p->right = p;
        p->down = p;
        hd[i] = p;
        hd[i-1]->down  = p;
    }
    hd[rowNumber]->down = H;
    for(i = rowNumber+1;i <= rowNumber+colNumber+1; ++i)
    {
        p = (OrthogonalList)malloc(sizeof(OrthogonalNode));
        p->row = 0;
        p->col = 0;
        p->right = p;
        p->down = p;
        hd[i] = p;
        hd[i-1]->right = p;
    }
    hd[rowNumber+colNumber+1]->right = H;
    for(j = 1; j <= NotZeroNumber; ++j)
    {
        printf("please input the three tuple....\n");
        scanf("%d,%d,%d",&rowNumber,&colNumber,&elementV);
        p = (OrthogonalList)malloc(sizeof(OrthogonalNode));
        p->row = rowNumber;
        p->col = colNumber;
        p->value= elementV;
        q = hd[rowNumber];
        r = q;
        while(q->right!=hd[rowNumber]&&q->right->col<colNumber)
         {
             r = q;
             q = q->right;
         }
        p->right = r->right;
        r->right = p;
        q = hd[colNumber+rowNumber+1];
        r = q;
        while(q->down !=hd[colNumber+rowNumber+1] && (q->down->row) < rowNumber)
         {
             r = q;
             q = q->down;
         }
        p->down = r->down;
        r->down =p;
    }
    return H;
}
























