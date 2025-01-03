#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double f(double x){
	return 0.25*x*x-sin(x);
}
double root(double a,double b){
	if(fabs(f((a+b)/2.0))<=1e-8){
		return (a+b)/2.0;
	}
	else{
		if (f((a+b)/2.0)*f(a)>0){
			return root((a+b)/2.0,b);
		} 
		else{
			return root(a,(a+b)/2.0);
		}
	}
}
int main(){
	if(f(1)*f(2)<=0){
		printf("%lf",root(1,2)) ;
	}
	else{
		return 0;
	}
	system("pause");
}
