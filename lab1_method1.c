#include <stdio.h>

int main() {
    double x, y;
    int is_defined = 0;

    printf("enter x: ");
    scanf("%lf", &x);

    if (x >= -49) {
        if (x < -10) {
            y = 10 * x * x * x + 7 * x / 5.0 + 2;
            is_defined = 1;
        }
        else if (x > 0) {
            if (x <= 10) {
                y = 10 * x * x * x + 7 * x / 5.0 + 2;
                is_defined = 1;
            }
            else if (x > 20) {
                y = -x + 9;
                is_defined = 1;
            }
        }
    }

    if (is_defined == 1) {
        printf("y = %lf\n", y);
    }
    else {
        printf("Function is undefined for given x.\n");
    }   
    return 0;
}