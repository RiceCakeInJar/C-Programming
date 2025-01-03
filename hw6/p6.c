#include <stdio.h>
#include <math.h>
#define eps 0.000001

double f(double x) {
    return exp(x) + x;
}

int main() {
    double a = -1.0, b = 1.0;
    double mid;
    while (fabs(b - a) > eps) {
        mid = (a + b) / 2;
        if (f(mid) > 0) {
            b = mid;
        } else {
            a = mid;
        }
    }
    printf("x=%.6lf\n", mid);
    return 0;
}
