#include<stdio.h>
int huiwen(long n){
	int a=0,b=n,c=n;
	while(b!=0){
		a=a*10+b%10;
		b=b/10;
	}
	if(a==c){
		return 1;
	}
	else{
		return 0;
	}
}
	
int main(){
	int i;
	for(i=1;i<=300;i++){
		if(huiwen(i)==1 && huiwen(i*i)==1){
			printf("%d\n",i);
		}
	}
}
