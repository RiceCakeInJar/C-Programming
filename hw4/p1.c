#include<stdio.h>
#include<stdlib.h>
int main(){
	printf("���������ʵ��"); 
	double a,b,c,d,e;
	scanf("%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e);
	if(a<=b&&b<=c&&c<=d&&d<=e){
		printf("%s\n","YES");
	}
	else{
		printf("%s\n","NO");
	}
	system("pause");
}
