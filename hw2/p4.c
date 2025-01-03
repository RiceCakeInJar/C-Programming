#include<stdio.h>
#include<math.h>
#include<assert.h>
int main(){
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    assert(a+b>c && a+c>b && b+c>a);
    float s=(a+b+c)/2;
    printf("%f",pow(s*(s-a)*(s-b)*(s-c),0.5));
}