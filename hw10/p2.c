#include<stdio.h>
void  line_sort(int a[][4],int b[],int n){
    int i,i_,sum,idx,temp;
    for(i=0;i<=n-1;i++){
        sum=0;
        for(i_=0;i_<=3;i_++){
            sum+=a[i][i_];
        }
        b[i]=sum;
    }//求和并写入b中
    for(i=0;i<=n-2;i++){
        for(i_=i+1;i_<=n-1;i_++){
            if(b[i]>b[i_]){
                temp=b[i];
                b[i]=b[i_];
                b[i_]=temp;
                //交换一维数据
                for(idx=0;idx<=3;idx++){
                    temp=a[i][idx];
                    a[i][idx]=a[i_][idx];
                    a[i_][idx]=temp;
                }
                //交换二维数组
            }
        }
    }


}
int main(){
    int array[5][4],b[5];
    int i,i_;
    for(i=0;i<=4;i++){
        for(i_=0;i_<=3;i_++){
            scanf("%d",&array[i][i_]);
        }
    }
    //写入二维数组
    line_sort(array,b,5);
    //执行变化过程
    for(i=0;i<=4;i++){
        for(i_=0;i_<=3;i_++){
            printf("%d ",array[i][i_]);
        }
        printf("\n");
    }
    //输出变化数组
    printf("sum\n");
    for(i=0;i<=4;i++){
        printf("%d ",b[i]);
    }
}
