#include <stdio.h>
#include <locale.h>
#include <math.h>
#include "quadratic.h"


void cleanBuffer() {
    while (getchar() != '\n') {;}
}

void getConstants(double *a, double *b, double *c) {
    int isContinue = 1;
    while (isContinue) {
        int countOfConstants = scanf("%lf %lf %lf", a, b, c);
        if (countOfConstants != 3)
            printf("Incorrect input\n");
        else
            isContinue = 0;
        cleanBuffer();
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
