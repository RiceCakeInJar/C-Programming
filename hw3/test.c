#include<stdio.h>
int x=50,y;
int main(){
	int x=30;
	{
		int x=77;
		printf("%d\n",x);
	}
	printf("%d\n",x+y);
	while(x++<33){
		int x=100;
		x++;
		printf("%d\n",x);
	}
	return 0;
}