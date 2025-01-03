#include<stdio.h>
#include<math.h>

double integral(double a,double b,long n,double (*p)(double)){
	double d=(b-a)/n;
	double ans=0;
	int i=1;
	for(i;i<=n;i++){
		ans+=(d*0.5*(p(a+i*d-d)+p(a+i*d)));
	}
	return ans; 
}
double f(double x){
	return 2*x+1;
}

int main(){
	double a,b,n;
	scanf("a=%lf,b=%lf,n=%lf",&a,&b,&n);
	printf("integral cos:%.6lf\nintegral sin:%.6lf\nintegral 2x+1:%.6lf\n",integral(a,b,n,&cos),integral(a,b,n,&sin),integral(a,b,n,&f));
}
