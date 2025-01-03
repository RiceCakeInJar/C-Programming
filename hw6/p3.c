#include<stdio.h>
double fac(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * fac(n-1);
    }
}
double main(){
    double x, c, sum;
    int i;
    scanf("%lf", &x);

    sum = c = x;
    i = 1;
    while (c >= 0.00000001 || c <= -0.00000001) {
        c = -c * x * x / ((2 * i) * (2 * i + 1));
        sum += c;
        i++;
    }
    printf("%.1lf\n",sum);
}