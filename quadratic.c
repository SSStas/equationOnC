#include <stdio.h>
#include <locale.h>
#include <math.h>


#define ONE_SOLUTION 0
#define TWO_SOLUTIONS 1
#define NO_SOLUTIONS 2
#define ALL_SOLUTIONS 3


struct RootsOfEquation
{
	double value[2];
	short solutionsCount;
};

struct RootsOfEquation getAnswer(double value[2], short solutionsCount)
{
	struct RootsOfEquation newRoots;
	newRoots.value[0] = value[0];
	newRoots.value[1] = value[1];
	newRoots.solutionsCount = solutionsCount;
	return newRoots;
}

void showAnswer(struct RootsOfEquation answer)
{
	switch (answer.solutionsCount)
	{
	case ONE_SOLUTION:	printf("Answer: x = %lf\n", answer.value[0]);	break;
	case TWO_SOLUTIONS: printf("Answer: x1 = %lf, x2 = %lf\n", answer.value[0], answer.value[1]); break;
	case ALL_SOLUTIONS: printf("Answer: For any value of x\n");	break;
	case NO_SOLUTIONS: printf("Answer: Not at any value of x\n");	break;
	default:			printf("Error\n");	break;
	}
}

// решение уравнения вида b*x + c = 0
struct RootsOfEquation linearEq(double b, double c)
{
	if (b != 0) {
		double arr[2] = { -c / b, 0 };
		return getAnswer(arr, ONE_SOLUTION);
	}
	else if (c != 0) {
		double arr[2] = { 0, 0 };
		return getAnswer(arr, NO_SOLUTIONS);
	}
	else {
		double arr[2] = { 0, 0 };
		return getAnswer(arr, ALL_SOLUTIONS);
	}
}

// решение уравнения вида a*x^2 + b*x + c = 0
struct RootsOfEquation quadraticEq(double a, double b, double c)
{
	if (a == 0)
		return linearEq(b, c);

	double d = pow(b, 2) - 4 * a * c;

	if (0 <= d && d <= 0.0001) {
		double arr[2] = { -b / (2 * a), 0 };
		return getAnswer(arr, ONE_SOLUTION);
	}
	else {
        if (d > 0) {
            double arr[2] = { (-b - sqrt(d)) / (2 * a), (-b + sqrt(d)) / (2 * a) };
            return getAnswer(arr, TWO_SOLUTIONS);
        }
        else {
            double arr[2] = { 0, 0 };
            return getAnswer(arr, NO_SOLUTIONS);
        }
    }
}
