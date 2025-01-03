#include<stdio.h>

int gcd(int a,int b){
    if(a==1 || b==1){
        return 1;
    }
    else if(a==b){
        return a;
    }
    else{
        if(a>b){
            return gcd(a-b,b);
        }
        else{
            return gcd(a,b-a);
        }
    }
}

int  Del_findgcd(int a[],int n,int *f){
    int i,ans=0;
    *f=a[0];
    for(i=0;i<n;i=i+2){
        printf("%d  ",a[i]);
        ans++;
        *f=gcd(*f,a[i]);
    }
    printf(",max common divisor is %d",*f);
    return ans;
}

int main(){
    int *gcd,ARRAY[]={6,8,9,11,12,13,15,16,18,19},N=10;
    Del_findgcd(ARRAY,N,gcd);
}