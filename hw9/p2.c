#include<stdio.h>
int x[10],y[10];
int main(){
    int i,i_,iy=1,check=9,flag=1;
    for(i=0;i<=9;i++){
        scanf("%d",&x[i]);
    }
    y[0]=x[0];
    while(check){
        for(i=1;i<=9;i++){
            flag=1;
            for(i_=0;i_<i;i_++){
                if(x[i_]==x[i]){
                    flag=0;
                    break;
                }
            }
            if(flag){
                y[iy]=x[i];
                iy++;
            }
            check--;
        }
    }
    for(i=0;i<iy;i++){
        printf("%d ",y[i]);
    }
}