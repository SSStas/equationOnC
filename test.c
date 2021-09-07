#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "quadratic.h"


enum TestResults {
    WRONG_ANSWER = 0,
    OK = 1
};

struct TestData {
    double a;
    double b;
    double c;
    struct RootsOfEquation testSolution;
};

void showTestParam(int number, struct TestData test, struct RootsOfEquation programSolution) {
    if ( !(isfinite(test.a) && isfinite(test.b) && isfinite(test.c)) ) {
        printf("Error: Incorrect format of test");
        return;
    }

    int lenTitle = floorf(log10(number)) + 7;
    for (int sizeLine = 0; sizeLine < lenTitle; sizeLine++)
        printf("-");

    printf("\nTest #%d\n", number);
    for (int sizeLine = 0; sizeLine < lenTitle; sizeLine++)
        printf("-");

    printf("\n\nEquation: ");
    showFuncOfQuadraticEq(test.a, test.b, test.c);
    printf("\nProgram output:\n");
    showAnswer(programSolution);
    printf("\nTest output:\n");
    showAnswer(test.testSolution);
    printf("\n");
}

void testingQuadraticEq(struct TestData testsData[], int maxLenTestsArray) {
    assert(testsData != NULL);
    assert(maxLenTestsArray > 0);

    enum TestResults finalResult[maxLenTestsArray];

    for (int testIndex = 0; testIndex < maxLenTestsArray; testIndex++) {

        double a = testsData[testIndex].a, b = testsData[testIndex].b, c = testsData[testIndex].c;
        struct RootsOfEquation testSolution = testsData[testIndex].testSolution;

        if ( !(isfinite(a) && isfinite(b) && isfinite(c)) ) {
            printf("Error: Incorrect format of constants in test #%d\n", testIndex + 1);
            break;
        }

        struct RootsOfEquation programSolution = quadraticEq(a, b, c);
        switch (testSolution.solutionsCount) {
            case ONE_SOLUTION:
                if (isfinite(testSolution.value[0])) {
                    if (programSolution.solutionsCount == ONE_SOLUTION && isTwoDoubleEqual(programSolution.value[0], testSolution.value[0]))
                        finalResult[testIndex] = OK;
                    else
                        finalResult[testIndex] = WRONG_ANSWER;
                    showTestParam(testIndex + 1, testsData[testIndex], programSolution);
                } else {
                    printf("Error: Incorrect format of answer's value in test #%d\n", testIndex + 1);
                    return;
                }
                break;

            case TWO_SOLUTIONS:
                if (isfinite(testSolution.value[0]) && isfinite(testSolution.value[1])) {
                    if (programSolution.solutionsCount == TWO_SOLUTIONS
                        && isTwoDoubleEqual(programSolution.value[0], testSolution.value[0])
                        && isTwoDoubleEqual(programSolution.value[1], testSolution.value[1]))
                        finalResult[testIndex] = OK;
                    else
                        finalResult[testIndex] = WRONG_ANSWER;
                    showTestParam(testIndex + 1, testsData[testIndex], programSolution);
                } else {
                    printf("Error: Incorrect format of answer's value(s) in test #%d\n", testIndex + 1);
                    return;
                }
                break;

            case ALL_SOLUTIONS:
                if (programSolution.solutionsCount == ALL_SOLUTIONS)
                    finalResult[testIndex] = OK;
                else
                    finalResult[testIndex] = WRONG_ANSWER;
                showTestParam(testIndex + 1, testsData[testIndex], programSolution);

                break;

            case NO_SOLUTIONS:
                if (programSolution.solutionsCount == NO_SOLUTIONS)
                    finalResult[testIndex] = OK;
                else
                    finalResult[testIndex] = WRONG_ANSWER;
                showTestParam(testIndex + 1, testsData[testIndex], programSolution);
                break;

            default:
                printf("Error: Incorrect format of test's solution in test #%d\n", testIndex + 1);
                return;
        }
        printf("Result: %s\n\n\n", ((finalResult[testIndex - 1]) ? "OK" : "WRONG ANSWER"));
    }

    // коротко выводит результаты о том, какие тесты пройдены, а какие нет
    for (int testNum = 0; testNum < maxLenTestsArray; testNum++)
        printf("Test #%d: %s\n", testNum + 1, ((finalResult[testNum]) ? "OK" : "WRONG ANSWER"));
}

int main() {
    struct TestData testsData[] = {
        { 0,                    0,                  0,              { { NAN, NAN },             ALL_SOLUTIONS } },
        { 0,                    0,                  3,              { { NAN, NAN },             NO_SOLUTIONS }  },
        { 0,                    0,                  1234.5678,      { { NAN, NAN },             NO_SOLUTIONS }  },
        { 0,                    69,                 0,              { { 0, NAN },               ONE_SOLUTION }  },
        { 0,                    999,                -105,           { { 0.105105, NAN },        ONE_SOLUTION }  },
        { 0,                    8723654.123457654,  56432.3456345,  { { -0.006469, NAN },       ONE_SOLUTION }  },
        { 125,                  -50,                5,              { { 0.2, NAN },             ONE_SOLUTION }  },
        { 45,                   45,                 11.25,          { { -0.5, NAN },            ONE_SOLUTION }  },
        { -380.25,              78,                 -4,             { { 0.102564, NAN },        ONE_SOLUTION }  },
        { 3458.23456,           23456.234,          -21345.6543,    { { -7.595374, 0.812654 },  TWO_SOLUTIONS } },
        { 1,                    2,                  -3,             { { -3, 1 },                TWO_SOLUTIONS } },
        { -1,                   2,                  0,              { { 0, 2 },                 TWO_SOLUTIONS } },
        { 495564.9387465672,    -4.619452345,       558811.5568555, { { NAN, NAN },             NO_SOLUTIONS }  },
        { 5,                    10,                 1000,           { { NAN, NAN },             NO_SOLUTIONS }  },
        { -10,                  8,                  -2,             { { NAN, NAN },             NO_SOLUTIONS }  },
    };

    printf("Unit-tests of the quadratic equations:\n");
    testingQuadraticEq(testsData, sizeof(testsData) / sizeof(testsData[0]));

    return 0;
}
