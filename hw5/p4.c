#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,i;
	printf("请输入100以内的正整数\n");
	scanf("%d",&n);
	printf("%d=",n);
	for(i=2;i<=n;i++){
		while(n%i==0){
			printf("%d",i);
			n=n/i;
			if(n!=1){
				printf("*");
			}
		}
	}
	system("pause");
}
