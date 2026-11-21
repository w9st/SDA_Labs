#include <stdio.h>
#include <math.h>

int main() {
    int n;
    long long ops = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    double x = 1.0 / 3.0; 
    ops += 2; 

    double sum = 0.0;
    ops += 1; 

    ops += 1; 
    for (int i = 1; i <= n; i++) {
        ops += 1; 

        double sign = 1.0;
        double pow2 = 1.0;
        double powx = 1.0;
        double fact = 1.0;
        ops += 4; 

        ops += 1;
        for (int j = 1; j <= i + 1; j++) {
            ops += 2;
            sign *= -1.0;
            ops += 2; 
            ops += 1; 
        }
        ops += 2; 

        ops += 1; 
        for (int j = 1; j <= 2 * i - 1; j++) {
            ops += 3; 
            pow2 *= 2.0;
            ops += 2; 
            ops += 1; 
        }
        ops += 3; 

        ops += 1; 
        for (int j = 1; j <= 2 * i; j++) {
            ops += 2; 
            powx *= x;
            fact *= j;
            ops += 4; 
            ops += 1; 
        }
        ops += 2; 

        sum += sign * pow2 * powx / fact;
        ops += 5; 

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