#include <stdio.h>
#include <locale.h>
#include <math.h>
#include "quadratic.c"
#include "input.c"


int main()
{

    double a = NAN, b = NAN, c = NAN;

    printf("enter the values of the variables a, b and c (separated by a space):\n");
    getConstants(&a, &b, &c);

	struct RootsOfEquation answer = quadraticEq(a, b, c);
	printf("%lf * x^2 + %lf * x + %lf = 0\n", a, b, c);
	showAnswer(answer);


	return 0;
}
