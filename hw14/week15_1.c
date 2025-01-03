#include<stdio.h>
#include<stdlib.h>

int rever(int num) {
    int reversedNum = 0;
    while (num != 0) {
        int remainder = num % 10;
        reversedNum = reversedNum * 10 + remainder;
        num /= 10;
    }
    return reversedNum;
}//反序数

int prime(int num){
    if(num<=1){return 0;}
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}//素数

int rev_prime(int m,int n,int x[]){
    int* ptr=x;
    int count=0;
    for(int i=m;i<=n;i++){
        if(prime(rever(i))){
            *ptr=rever(i);
            ptr++;
            count++;
        }
    }
    return count;
}

int main(){
    int m=0,n=0,count=0;
    printf("请输入两个非负整数，并以空格间隔区分:");
    scanf("%d %d",&m,&n);
    int* x = (int *)calloc(abs(m-n),sizeof(int));
    count=rev_prime(m,n,x);
    FILE* answer = fopen("out.txt","a");
    if(answer==NULL){
        printf("无法打开文件out.txt");
        return 0;
    }
    for(int i=0;i<count;i++){
        fprintf(answer,"%d  ",x[i]);
    }
    fclose(answer);
    free(x);
    return 0;
}