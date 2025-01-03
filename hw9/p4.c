#include<stdio.h>
int x[10],ans=10,i,i_;
int main(){
    for(i=0;i<=9;i++){
        scanf("%d",&x[i]);
    }
    for(i=0;i<=9;i++){
        for(i_=0;i_<i;i_++){
            if(x[i]==x[i_]){
                ans--;
                break;
            }
        }
    }
    printf("%d",ans);    
}