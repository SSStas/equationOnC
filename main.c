#include <stdio.h>
#include <locale.h>
#include <math.h>

#define ONE_SOLUTION 0
#define TWO_SOLUTIONS 1
#define NO_SOLUTIONS 2
#define ALL_SOLUTIONS 3

struct X
{
	double value[2];
	short answer;
};

struct X getAnswer(double value[], short answer)
{
	struct X newX;
	newX.value[0] = ((int) sizeof(value) >= 1 ? value[0] : 0);
	newX.value[1] = ((int) sizeof(value) >= 2 ? value[1] : 0);
	newX.answer = answer;
	return newX;
}

void showAnswer(struct X x)
{
	switch (x.answer)
	{
	case ONE_SOLUTION:	printf("Ответ: x = %lf\n", x.value[0]);	break;
	case TWO_SOLUTIONS: printf("Ответ: x1 = %lf, x2 = %lf\n", x.value[0], x.value[1]); break;
	case ALL_SOLUTIONS: printf("Ответ: При любом x\n");	break;
	case NO_SOLUTIONS: printf("Ответ: Ни при каком x\n");	break;
	default:			printf("Ошибка\n");	break;
	}
}

// решение уравнения вида b*x + c = 0
struct X linearEq(double b, double c)
{
	if (b != 0) {
		double arr[2] = { -c / b };
		return getAnswer(arr, ONE_SOLUTION);
	}
	else if (c != 0) {
		double arr[2];
		return getAnswer(arr, NO_SOLUTIONS);
	}
	else {
		double arr[2];
		return getAnswer(arr, ALL_SOLUTIONS);
	}
}

// решение уравнения вида a*x^2 + b*x + c = 0
struct X quadraticEq(double a, double b, double c)
{
	if (a == 0)
		return linearEq(b, c);

	double d = pow(b, 2) - 4 * a * c;
	if (d == 0) {
		double arr[2] = { -b / (2 * a) };
		return getAnswer(arr, ONE_SOLUTION);
	}
	else if (d > 0) {
		double arr[2] = { (-b - sqrt(d)) / (2 * a), (-b + sqrt(d)) / (2 * a) };
		return getAnswer(arr, TWO_SOLUTIONS);
	}
	else {
		double arr[2];
		return getAnswer(arr, NO_SOLUTIONS);
	}
}

int main()
{
	char *locale = setlocale(LC_ALL, "");

	double a, b, c;
	printf("Введите константы a, b и c (через пробелы):\n");
	scanf("%lf%lf%lf", &a, &b, &c);

	struct X x = quadraticEq(a, b, c);
	showAnswer(x);


	return 0;
}
