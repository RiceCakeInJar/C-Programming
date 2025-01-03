#include <stdio.h>
#include <math.h>
#define eps 0.000001
double f(double x) {
    return cos(x) - x;
}

double df(double x) {
    return -sin(x) - 1;
}

int main() {
    double x0 = 0.5; 
    double x1;
    do {
        x1 = x0 - f(x0) / df(x0); 
        x0 = x1;
    } while (fabs(f(x1)) > eps);
    printf("x=%.6f\nf(x)=%.6f", x1,fabs(f(x1)));
    return 0;
}
