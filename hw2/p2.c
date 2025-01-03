#include<stdio.h>
#include<math.h>
#define a 100.453627
float helper(int n){
    int b = (int)(a*pow(10,n)+0.5);
    return b/pow(10,n);
}
int main(){
    printf("%.1f\n%.2f\n%.3f\n%.4f",helper(1),helper(2),helper(3),helper(4));
}

