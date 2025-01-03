#include<stdio.h>
int main(){
    int a,b,c,d;
    printf("Please input complex number one\nrealpart:\n");
    scanf("%d",&a);
    printf("imagpart:\n");
    scanf("%d",&b);
    printf("Please input complex number two\nrealpart:\n");
    scanf("%d",&c);
    printf("imagpart:\n");
    scanf("%d",&d);
    printf("sum=%d%+di\nminus=%d%+di\nproduct=%d%+di",(a+c),(b+d),(a-c),(b-d),(a*c-b*d),(a*d+b*c));
}