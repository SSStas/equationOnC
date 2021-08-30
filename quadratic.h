#ifndef QUADRATIC_H_INCLUDED
#define QUADRATIC_H_INCLUDED

enum SolutionsKinds {ONE_SOLUTION, TWO_SOLUTIONS, NO_SOLUTIONS, ALL_SOLUTIONS};

struct RootsOfEquation
{
	double value[2];
	enum SolutionsKinds solutionsCount;
};


int checkEqualityWithZero(double value);
char getSignOfDouble(double value);
double getRoundSmallDouble(double value);
void showAnswer(struct RootsOfEquation answer);
void showFuncOfQuadraticEq(double a, double b, double c);
struct RootsOfEquation linearEq(double b, double c);
struct RootsOfEquation quadraticEq(double a, double b, double c);


#endif // QUADRATIC_H_INCLUDED
