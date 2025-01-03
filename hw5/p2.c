#include<stdio.h>
#include<stdlib.h>

int main(){
	int n,n0,n1,n2;
	for(n=100;n<=999;n++){
		if(n%37==0){
			n0=n/100;
			n1=(n%100)*10+n0;
			n2=(n%10)*100+(n/10);
			if(n1%37==0 && n2%37==0){
				printf("%d ",n);
			}
			else{
				printf("wrong");
			}
		} 
	} 
	system("pause");
}
