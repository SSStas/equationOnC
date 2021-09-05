#include <stdio.h>
#include <locale.h>
#include <math.h>
#include "quadratic.h"


void getConstants(double *a, double *b, double *c) {
    while (1) {
        if (scanf("%lf %lf %lf", a, b, c) != 3)
            printf("Incorrect input\n");
        else
            break;

        fflush(stdin);
    }
}

int main() {
    double a = NAN, b = NAN, c = NAN;

    printf("Enter the values of the variables a, b and c (separated by a space):\n");
    getConstants(&a, &b, &c);

    struct RootsOfEquation answer = quadraticEq(a, b, c);
    showFuncOfQuadraticEq(a, b, c);
    showAnswer(answer);

    return 0;
}
