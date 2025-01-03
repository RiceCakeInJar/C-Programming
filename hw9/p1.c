#include<stdio.h>
#include<math.h>
int prime(int x){
    int i=2;
    for (i; i < x; i++)
    {
        if ((x%i==0)){
            return 0;
        }
    }
    return 1;
}
int swap(int *a,int *b){
    int c = *a;
    *a=*b;
    *b=c;
}
int main(){
    int x[10];
    int i,n=0,m=9;
    for(i=0;i<=9;i++){
        scanf("%d",&x[i]);
    }
    while(n<=m){
        if(prime(x[n])==1 && prime(x[m])==1){
            swap(x+n,x+m);
            n++;
            m--;
        }
        else if(prime(x[n])){
            m--;
        }
        else if(prime(x[m])){
            n++;
        }
        else{
            n++;
            m--;
        }
    }
    for(i=0;i<=9;i++){
    printf("%d ",x[i]);
    }
}