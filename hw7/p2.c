#include<stdio.h>
int prime(int n){
	int i;
	if(n<=1){
		return 0;
	}
	for(i=2;i<n;i++){
		if(n%i==0){
			return 0;
		}
	}
	return 1;
}
int main(){
	int m,n,ans=0,i;
	scanf("%d%d",&m,&n);
	i=m;
	for(i;i<=n-2;i++){
		if(prime(i)){
			if(prime(i+2)){
				printf("(%d,%d)\n",i,i+2);
				ans++;
			}
		}
	}
	if(ans==0){
		printf("该区间内无孪生素数\n");
	}
	else{
		printf("t=%d\n",ans);
	}
}
