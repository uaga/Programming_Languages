#include <stdio.h>

int main()
{
	float a,b,c,x;
	printf("\nВведите данные:\na=");
	scanf("%f", &a);
	printf("\nb=");
	scanf("%f", &b);
	printf("\nc=");
	scanf("%f", &c);
	x = (c - b) / a;
	printf("\nКорень уравнения:\n %.2f*x+%.2f=%.2f\nx=%.2f\n", a,b,c,x);
}
