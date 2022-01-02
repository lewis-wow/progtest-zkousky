#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int epsilonEquality(double a, double b) {
    double epsilon = 5e-5;

    if(fabs(a - b) < epsilon) return 0;
    if(a < b) return -1;
    return 1;
}

int main(void) {
    double a, b;

    printf("Vstupy a, b:\n");
    scanf(" %lf %lf", &a, &b);

    int check = epsilonEquality(a, b);
    printf("a(%lf) %c b(%lf)\n", a, check == 0 ? '=' : check == -1 ? '<' : '>', b);

    return 0;
}
