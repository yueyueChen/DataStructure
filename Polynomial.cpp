#include<stdio.h>
#include<stdlib.h>
#define MaxDegree 100
typedef struct{
	int coeffArray[MaxDegree];
	int highPower;
}  p;
typedef p *Polynomial;

void ZeroPolynomial(Polynomial Poly)
{
	int i;
	for( i = 0; i<=MaxDegree;++i)
		Poly->coeffArray[i] = 0;
		Poly->highPower = 0;
}

void AddPolynomial(const Polynomial Poly1,const Polynomial Poly2,Polynomial PolySum)
{
	int i;
	ZeroPolynomial(PolySum);
	if(Poly1->highPower>=Poly2->highPower)
		PolySum->highPower = Poly1->highPower;
	else
		PolySum->highPower = Poly2->highPower;
	
	for(i = PolySum->highPower;i>=0;--i)
		PolySum->coeffArray[i] = Poly1->coeffArray[i] + Poly2->coeffArray[i];
}
void MultPolynomial(const Polynomial Poly1,const Polynomial Poly2,Polynomial PolyProd)
{
	int i,j;
	
	ZeroPolynomial(PolyProd);
	PolyProd->highPower = Poly1->highPower + Poly2->highPower;
	if(PolyProd->highPower>MaxDegree)
		printf("error:Esceeded arry size.");
	else
	{
		for(i = 0;i<= Poly1->highPower;++i)
			for(j = 0;j <= Poly2->highPower;++j)
				PolyProd->coeffArray[i+j] += Poly1->coeffArray[i] * Poly2->coeffArray[j];
	}
}

Polynomial CreatePoly()
{
	Polynomial Poly = (Polynomial)malloc(sizeof(p));
	int  i,x;
	for(i = 0;i<=MaxDegree;i++)
	{
	printf("\nplease input the number:");
	scanf("%d",&x);
	if(x==-1)
		break;
	Poly->coeffArray[i] = x;
	Poly->highPower = i;
	}
	return Poly;
}
void display(Polynomial Poly)
{
	int i =0;
	printf("\nthe number is :\n");
	for(i = Poly->highPower;i>= 0;--i)
		printf("  %d",Poly->coeffArray[i]);
}
int main()
{
	Polynomial Poly1 = CreatePoly();
	display(Poly1);
	Polynomial Poly2 = CreatePoly();
	display(Poly2);
	Polynomial PolySum =(Polynomial)malloc(sizeof(p));
	ZeroPolynomial(PolySum);
	MultPolynomial(Poly1,Poly2,PolySum);
	display(PolySum);
}

