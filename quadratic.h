#ifndef QUADRATIC_H_INCLUDED
#define QUADRATIC_H_INCLUDED


enum SolutionsKinds {
    ONE_SOLUTION = 0,
    TWO_SOLUTIONS = 1,
    NO_SOLUTIONS = 2,
    ALL_SOLUTIONS = 3,
    DOES_NOT_EXIST = 4
};

///< Решения квадратного уравнения
struct RootsOfEquation
{
	double value[2];
	enum SolutionsKinds solutionsCount;
};

/*!
    \brief Выводит на экран решения квадратного уравнения
    \warning В случае если решения не существует, функция выводит на экран соответствующую ошибку, без принудительного завершения программы
    \param [in] answer структура, содержащая ответ на квадратное уравнение
    \return Ничего
*/
void showAnswer(struct RootsOfEquation answer);

/*!
    \brief Выводит вид функции квадратного уравнения с подставленными константами на экран
    \warning В случае если константы не являются числами, функция выводит на экран соответствующую ошибку, без принудительного завершения программы
    \param [in] a константа квадратного уравнения
    \param [in] b константа квадратного уравнения
    \param [in] c константа квадратного уравнения
    \return Ничего
*/
void showFuncOfQuadraticEq(double a, double b, double c);

/*!
    \brief Вычисляет линейное уравнение вида b*x + c = 0
    \warning В случае если константы не являются числами, функция возвращае структуру, не содержащую ответ
    \param [in] b константа линейного уравнения
    \param [in] c константа линейного уравнения
    \return Структуру, содержащую ответ на линейное уравнение
*/
struct RootsOfEquation linearEq(double b, double c);

/*!
    \brief Вычисляет линейное уравнение вида a*x^2 + b*x + c = 0
    \warning В случае если константы не являются числами, функция возвращае структуру, не содержащую ответ
    \param [in] a константа квадратного уравнения
    \param [in] b константа квадратного уравнения
    \param [in] c константа квадратного уравнения
    \return Структуру, содержащую ответ на квадратное уравнение
*/
struct RootsOfEquation quadraticEq(double a, double b, double c);


#endif // QUADRATIC_H_INCLUDED
