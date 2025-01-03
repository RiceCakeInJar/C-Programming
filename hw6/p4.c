#include<stdio.h>
int main(){
    int a=2,b=3,flag=1,count=18;
    printf("%d %d ",a,b);
    while(count>0){
        switch(flag){
            case 1:
                printf("%d ",a+b);
                int i=a+b;
                a=b;
                b=i;
                flag=-flag;
                count--;
                break;
            case -1:
                printf("%d ",a-b);
                int i_=a-b;
                a=b;
                b=i_;
                flag=-flag;
                count--;
                break;
        }
    }
}
