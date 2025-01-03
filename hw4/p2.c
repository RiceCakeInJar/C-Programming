#include<stdio.h>
#include<stdlib.h>

int main(){
	char *A,*B;
	float am,bm,ap,bp,ac,bc,as,bs,aa,ba;
	printf("�������һ��ͬѧ�������ͳɼ���");
	scanf("%c,%f,%f,%f",&A,&am,&ap,&ac); 
	as = am+ap+ac;
	aa = as/3.0;
	printf("������ڶ���ͬѧ�������ͳɼ���");
	getchar();
	scanf("%c,%f,%f,%f",&B,&bm,&bp,&bc); 
	bs = bm+bp+bc;
	ba = bs/3.0;
	printf("************************************************\n");
	printf("NAME   MATH   PHYSICS   CHEMSTRY   SUM   AVERAGE\n");
	printf("%3c%9.1f%8.1f%10.1f%9.1f%9.3f\n",A,am,ap,ac,as,aa);
	printf("%3c%9.1f%8.1f%10.1f%9.1f%9.3f\n",B,bm,bp,bc,bs,ba);
	printf("************************************************\n");
	system("pause");
}
