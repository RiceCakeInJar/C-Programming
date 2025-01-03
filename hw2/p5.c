#include<stdio.h>
#define price 114.514
#define pi 3.1415
int main(){
    int r,h,p;
    scanf("%d%d%d",&r,&h,&p);
    printf("体积为:%f\n价值为:%f¥\n",pi*h*r*r,pi*h*r*r*p*price);
}