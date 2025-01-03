#include<stdio.h>
int main(){
    int n,m,i;
    scanf("%d",&n);
    int x[n],y[n];
    for(i=0;i<=n-1;i++){
        scanf("%d",&x[i]);
    }
    scanf("%d",&m);
    for(i=1;i<=m;i++){
        y[i-1]=x[i+9-m];
    }
    for(i=1;i<=n-m;i++){
        y[m+i-1]=x[i-1];
    }
    for(i=0;i<=n-1;i++){
        printf("%d ",y[i]);
    }
}