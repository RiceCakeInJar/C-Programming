#include<stdio.h>
int check(int a[],int n,int x){
    int i;
    static int true_zero=0;
    if(!x){
        if(true_zero){
            return 1;
        }
        else{
            true_zero=1;
            return 0;
        }
    }
    for(i=0;i<n;i++){
        if(a[i]==x){
            return 1;
        }
    }
    return 0;
}

int Union(int (*a)[6], int res[25]) {
    int count = 0,num;
    for (int i = 0; i < 5; i++) { 
        for (int j = 1; j <= a[i][0]; j++) { 
            num = a[i][j];
            if (!check(res,25,num)) { 
                res[count] = num;
                count++; 
            }
        }
    }
    return count; 
}

int main() {
    int sec[5][6] = {{4,12,35,3,9},
                    {3,2,35,9},
                    {5,35,12,0,1,9},
                    {1,90},
                    {2,9,0}}; // 初始化二维数组sec
    int res[25]={0};
    int count = Union(sec, res); 
    for (int i = 0; i < count; i++) {
        printf("%d ", res[i]);
    }
}
