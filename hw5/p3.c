#include<stdio.h>
#include<stdlib.h>
int sub(n){
	int n0,n1,n2;
	n0=n%10;
	n1=(n%100)/10;
	n2=n/100;
	if(n2>=n1&&n1>=n0){return (99*(n2-n0));}
	else if(n2>=n0&&n0>=n1){return (99*(n2-n1));}
	else if(n1>=n2&&n2>=n0){return (99*(n1-n0));}
	else if(n1>=n0&&n0>=n2){return (99*(n1-n2));}
	else if(n0>=n1&&n1>=n2){return (99*(n0-n2));}
	else if(n0>=n2&&n1>=n1){return (99*(n0-n1));}
	else return 0;
}
int main(){
	int n,check=1;
	do{
		scanf("%d",&n);
		if(n%10==(n%100)/10 || n%10==n/100 || n/100==(n%100)/10){
			check=0;
			printf("请输入一个各位数字不同的三位数");
		}
	}while(check==0);
	int check_num=0;
	do{
		printf("%d ",n);
		n=sub(n);
		check_num++;
		if(check_num==8){
			printf("证伪：已超过7次");
			break; 
		}
		else if(n==495){
			printf("495");
			break;
		}
	}while(n!=495);
	system("pause");
} 
