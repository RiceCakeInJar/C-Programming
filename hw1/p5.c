#include<stdio.h>
int main(){
    int a,b,thd,hud,ten,one;
    scanf("%d",&b);
    one = b%10;
    ten = (b/10)%10;
    hud = (b/100)%10;
    thd = (b/1000)%10;
    a = one*1000+ten*100+hud*10+thd;
    printf("%d",a);
}