#include<stdio.h>
#include<stdlib.h>
int main(){
	int n,ans=1;
	scanf("%d",&n);
	while(n>9){
		n=n/10;
		ans++;
	}
	printf("%d",ans);
	system("pause");
}
