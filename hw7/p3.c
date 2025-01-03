#include<stdio.h>
int fanxu(long n){
	int a=0,b=n;
	while(b!=0){
		a=a*10+b%10;
		b=b/10;
	}
	return a;
}

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

int fun(long n, long *hw){
	int ans=0;
	do{
		if(huiwen(n)){
			*hw=n;
			return ans;
		}
		else{
			n=n+fanxu(n);
			ans++;
		}
	}while(ans<=10000);
	return -1;
}

int main(){
	long a,b,c;
	scanf("%d",&a);
	c=fun(a,&b);
	if(c==-1){
		printf("error\n");
	}
	else{
		printf("%d,%d\n",b,c);
	}
} 
