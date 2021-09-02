#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "quadratic.h"


int isTwoDoubleEqual(double value1, double value2)
{
    return ( (isfinite(value1) && isfinite(value2)) ? (fabs(value1 - value2) < 0.000001) : 0 );
}

char getSignOfDouble(double value)
{
    assert( isfinite(value) );

    return (value >= 0.0 ? '+' : '-');
}

void swapDoubles(double *value1, double *value2)
{
    assert( value1 != NULL );
    assert( value2 != NULL );

    double saveRoot = *value1;
    *value1 = *value2;
    *value2 = saveRoot;
}

void showAnswer(struct RootsOfEquation answer)
{
    if ( !isfinite(answer.value[0]) && answer.solutionsCount == ONE_SOLUTION) {
        printf("Error: Invalid value of answer\n");
        return;
    }

    if ( (!isfinite(answer.value[0]) || !isfinite(answer.value[1]))  && answer.solutionsCount == TWO_SOLUTIONS) {
        printf("Error: Invalid value(s) of answer\n");
        return;
    }

	switch (answer.solutionsCount)
	{
        case ONE_SOLUTION:
            printf("Answer: x = %lf\n", answer.value[0]); break;
        case TWO_SOLUTIONS:
            printf("Answer: x1 = %lf, x2 = %lf\n", answer.value[0], answer.value[1]); break;
        case ALL_SOLUTIONS:
            printf("Answer: For any value of x\n"); break;
        case NO_SOLUTIONS:
            printf("Answer: Not at any value of x\n"); break;
        default:
            printf("Error: There is no correct answer\n"); break;
	}
}

void showFuncOfQuadraticEq(double a, double b, double c)
{
    if ( !(isfinite(a) && isfinite(b) && isfinite(c)) ) {
        printf("Error: Invalid value types\n");
        return;
    }

    char bSign = getSignOfDouble(b), cSign = getSignOfDouble(c);
    double formatedB = fabs(b), formatedC = fabs(c);
    printf("%lf * x^2 %c %lf * x %c %lf = 0\n", a, bSign, formatedB, cSign, formatedC);
}

// решение уравнения вида b*x + c = 0
struct RootsOfEquation linearEq(double b, double c)
{
    if ( !(isfinite(b) && isfinite(c)) )
        return { { NAN, NAN }, DOES_NOT_EXIST };

	if (isTwoDoubleEqual(b, 0.0)) {

        if (isTwoDoubleEqual(c, 0.0))
            return { { 0, 0 }, ALL_SOLUTIONS };
        else
            return { { 0, 0 }, NO_SOLUTIONS };

	} else
		return { { -c / b, 0 }, ONE_SOLUTION };
}

// решение уравнения вида a*x^2 + b*x + c = 0
struct RootsOfEquation quadraticEq(double a, double b, double c)
{
    if ( !(isfinite(a) && isfinite(b) && isfinite(c)) )
        return { { NAN, NAN }, DOES_NOT_EXIST };

	if (isTwoDoubleEqual(a, 0.0))
		return linearEq(b, c);

	double d = b * b - 4.0 * a * c;

	if (0 <= d && d <= 0.000001)
		return { { -b / (2 * a), 0 }, ONE_SOLUTION };
	else {

        if (d > 0) {
            double root1 = (-b - sqrt(d)) / (2 * a), root2 = (-b + sqrt(d)) / (2 * a);
            if (root1 > root2)
                swapDoubles(&root1, &root2);

            return { { root1, root2 }, TWO_SOLUTIONS };
        }
        else
            return { { 0, 0 }, NO_SOLUTIONS };

    }
}

