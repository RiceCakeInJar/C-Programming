#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,i,sum;
	for(n=1;n<=1000;n++){
		sum=0;
		for(i=1;i<n;i++){
			if(n%i==0){
				sum += i;
			}
		}
		if(sum==n){
			printf("%d ",n);
		}
	}
	system("pause");
}
