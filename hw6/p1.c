#include<stdio.h>
#include<stdlib.h>
int check(int n){
	int r=0,c=n;
	while(c>0){
		r=r*10+c%10;
		c=c/10;
	}
	if(r==n){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	int i=317;
	for(;i<=999;i++){
		if(check(i*i)){
			printf("%d ",i*i);
		}
	}
	system("pause");
}
