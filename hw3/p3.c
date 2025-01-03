#include<stdio.h>
int main(){
    float a,b,c,d,e,A,B,C,D,E;
    scanf("%f%f%f%f%f",&a,&b,&c,&d,&e);
    A=fabs(a);
    B=fabs(b);
    C=fabs(c);
    D=fabs(d);
    E=fabs(e);
    printf("   x            |x|\n%10.6f %10.2f\n%10.6f %10.2f\n%10.6f %10.2f\n%10.6f %10.2f\n%10.6f %10.2f\n",a,A,b,B,c,C,d,D,e,E);
}