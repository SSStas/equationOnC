#include <stdio.h>
#include <locale.h>
#include <math.h>
#include "quadratic.h"


int checkEqualityWithZero(double value)
{
    return -0.0000005 < value && value < 0.0000005;
}

char getSignOfDouble(double value)
{
    return (value >= 0.0 ? '+' : '-');
}

double getRoundDouble(double value, int signsAfterPoint)
{
    return roundf(value * pow(10, signsAfterPoint)) / pow(10, signsAfterPoint);
}

void swapDoubles(double *value1, double *value2)
{
    double saveRoot = *value1;
    *value1 = *value2;
    *value2 = saveRoot;
}

void showAnswer(struct RootsOfEquation answer)
{
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
            printf("Error\n"); break;
	}
}

void showFuncOfQuadraticEq(double a, double b, double c)
{
    char bSign = getSignOfDouble(getRoundDouble(b, 6)), cSign = getSignOfDouble(getRoundDouble(c, 6));
    double formatedB = fabs(getRoundDouble(b, 6)), formatedC = fabs(getRoundDouble(c, 6));
    printf("%lf * x^2 %c %lf * x %c %lf = 0\n", getRoundDouble(a, 6), bSign, formatedB, cSign, formatedC);
}

// решение уравнения вида b*x + c = 0
struct RootsOfEquation linearEq(double b, double c)
{
	if (checkEqualityWithZero(b)) {

        if (checkEqualityWithZero(c))
            return { { 0, 0 }, ALL_SOLUTIONS };
        else
            return { { 0, 0 }, NO_SOLUTIONS };

	} else
		return { { getRoundDouble( -c / b, 6), 0 }, ONE_SOLUTION };
}

// решение уравнения вида a*x^2 + b*x + c = 0
struct RootsOfEquation quadraticEq(double a, double b, double c)
{
	if (checkEqualityWithZero(a))
		return linearEq(b, c);

	double d = b * b - 4.0 * a * c;

	if (0 <= d && d <= 0.000001)
		return { { getRoundDouble(-b / (2 * a), 6), 0 }, ONE_SOLUTION };
	else {

        if (d > 0) {
            double root1 = (-b - sqrt(d)) / (2 * a), root2 = (-b + sqrt(d)) / (2 * a);
            if (root1 > root2)
                swapDoubles(&root1, &root2);

            return { { getRoundDouble( root1, 6 ), getRoundDouble( root2, 6 ) }, TWO_SOLUTIONS };
        }
        else
            return { { 0, 0 }, NO_SOLUTIONS };

    }
}

