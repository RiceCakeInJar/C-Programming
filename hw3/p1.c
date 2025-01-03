#include<stdio.h>
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    if(a%b==0 || b%a==0){
        printf("%s","true");
    }
    else{
        printf("%s","false");
    };
}