#include<stdio.h>
int check_1(int n){
	int i=2,flag=1;
	for(i;i<n;i++){
		if(n%i==0){
			flag=0;
		}
	}
	return flag;
}
int check_2(int n){
	if((n%10+(n/10)%10)%10==n/100){
		return 1;
	}
	else{
		return 0;
	}
}

int main(){
	int i;
	for(i=101;i<=999;i=i+2){
		if(check_1(i) && check_2(i)){
			printf("%d\n",i);
		}
	}
}
