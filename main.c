#include <stdio.h>
#include <locale.h>
#include <math.h>
#include "quadratic.h"
#include "input.h"


int main()
{

    double a = NAN, b = NAN, c = NAN;

    printf("Enter the values of the variables a, b and c (separated by a space):\n");
    getConstants(&a, &b, &c);

	struct RootsOfEquation answer = quadraticEq(a, b, c);
	showFuncOfQuadraticEq(a, b, c);
	showAnswer(answer);


	return 0;
}
