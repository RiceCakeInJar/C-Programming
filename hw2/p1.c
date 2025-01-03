#include<stdio.h>
int main(){
    float input,xiaoshu=.0;
    char oper='+';
    int zhengshu=0;
    scanf("%f",&input);
    if(input < 0){
        oper = '-';
        input = -input;
    }
    zhengshu = input/1;
    xiaoshu = input - zhengshu;
    printf("sign: %c\n",oper);
    printf("integral part: %d\n",zhengshu);
    printf("decimal fraction part: %f\n",xiaoshu);
}