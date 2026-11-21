#include <stdio.h>
#include <math.h>

int main() {
    int n;
    long long ops = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    double x = 1.0 / 3.0;
    ops += 2;

    double factor = -4.0 * x * x;
    ops += 3;

    double term = x * x;
    double sum = term;
    ops += 3;

    ops += 1;
    for (int i = 2; i <= n; i++) {
        ops += 1; 

        term = term * factor / ((2 * i - 1) * (2 * i));
        ops += 6; 

        sum += term;
        ops += 2; 

        ops += 1; 
    }
    ops += 1;

    double S = 1.0 - sum;
    ops += 2; 

    double exact = cos(x) * cos(x);
    double error = fabs(S - exact);

    printf("S = %.7lf\n", S);
    printf("Operations = %lld\n", ops);
    printf("Exact = %.7lf, Error = %.4e\n", exact, error);

    return 0;
}