#include<stdio.h>
double f(double x){
	return 0.8*(x-1);
}
int peach(int ans){
	if (f(f(f(f(f(ans)))))==(int)(f(f(f(f(f(ans)))))))
	{
		return ans;
	}
	else{
		return peach(ans+1);
	}
}
int main(){
	printf("%d",peach(1));
}