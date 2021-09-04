#ifndef QUADRATIC_H_INCLUDED
#define QUADRATIC_H_INCLUDED

//==================================================================================================

//                               функции для работы с квадратным уравнением

//==================================================================================================

enum SolutionsKinds {
    ONE_SOLUTION = 0,
    TWO_SOLUTIONS = 1,
    NO_SOLUTIONS = 2,
    ALL_SOLUTIONS = 3,
    DOES_NOT_EXIST = 4
};

///< Решения квадратного уравнения.
struct RootsOfEquation {
	double value[2];
	enum SolutionsKinds solutionsCount;
};

/*!
    \brief Выводит на экран решения квадратного уравнения.
    \param [in] answer  структура, содержащая ответ на квадратное уравнение.
*/
void showAnswer(struct RootsOfEquation answer);

/*!
    \brief Выводит вид функции квадратного уравнения с подставленными константами на экран.
    \param [in] a коэффициент квадратного уравнения.
    \param [in] b коэффициент квадратного уравнения.
    \param [in] c коэффициент квадратного уравнения.
*/
void showFuncOfQuadraticEq(double a, double b, double c);

/*!
    \brief Вычисляет линейное уравнение вида b*x + c = 0.
    \param [in] b коэффициент линейного уравнения.
    \param [in] c коэффициент линейного уравнения.
    \return RootsOfEquation структура, содержащая ответ на линейное уравнение.
*/
struct RootsOfEquation linearEq(double b, double c);

/*!
    \brief Вычисляет линейное уравнение вида a*x^2 + b*x + c = 0.
    \param [in] a коэффициент квадратного уравнения.
    \param [in] b коэффициент квадратного уравнения.
    \param [in] c коэффициент квадратного уравнения.
    \return RootsOfEquation структура, содержащая ответ на квадратное уравнение.
*/
struct RootsOfEquation quadraticEq(double a, double b, double c);


/*!
    \brief Сравнивает два вещественных числа.
    \param [in] value1  первое число.
    \param [in] value2  второе число.
    \return 1 - если два числа равны и 0 - если нет.

    \note Сравнение происходит с погрешностью  до 0.000001
*/
int isTwoDoubleEqual(double value1, double value2);

#endif // QUADRATIC_H_INCLUDED
