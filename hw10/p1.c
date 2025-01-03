#include<stdio.h>
int prime(int x){
    int i=2;
    if(x==1){
        return 0;
    }
    for (i; i < x; i++)
    {
        if ((x%i==0)){
            return 0;
        }
    }
    return 1;
}
int change(int x){
    if(prime(x)==0){
        return 0;
    }
    else{
        while(x++){
            if(prime(x)){
                return x;
            }
        }
    }
}
int main(){
    int array[4][4];
    int i,i_,count=0;
    for(i=0;i<=3;i++){
        for(i_=0;i_<=3;i_++){
            scanf("%d",&array[i][i_]);
        }
    }
    for(i=0;i<=3;i++){
        for(i_=0;i_<=i;i_++){
            if(prime(array[i][i_])){
                count++;
            }
        }
    }
    for(i=0;i<=3;i++){
        for(i_=0;i_<=i;i_++){
            array[i][i_]=change(array[i][i_]);
        }
    }
    for(i=0;i<=3;i++){
        for(i_=0;i_<=3;i_++){
            printf("%d ",array[i][i_]);
        }
        printf("\n");
    }
    printf("count=%d",count);
}