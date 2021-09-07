#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "quadratic.h"


enum TestResults {
    WRONG_ANSWER = 0,
    OK = 1,
    ERROR = 2
};

enum KindsComments {
    ITS_NOT_COMMENT = 0,
    LINEAR_COMMENT = 1
};

struct TestData {
    double a;
    double b;
    double c;
    struct RootsOfEquation programSolution;
    struct RootsOfEquation testSolution;
    enum TestResults finalResult;
};

enum KindsComments isComment(char word[]) {
    assert(word != NULL);

    if (word[0] == '#')
        return LINEAR_COMMENT;

    return ITS_NOT_COMMENT;
}

void passLinearComments(FILE *file) {
    assert(file != NULL);

    char ch = '0';
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            break;
        }
    }
}

int getIntNumFromFile(FILE *file, int *value) {
    assert(file != NULL);
    assert(value != NULL);

    char extraString[1000] = {};
    int isGetNum = 0;
    while (!isGetNum) {
        isGetNum = fscanf(file, "%d", value);
        if (!isGetNum) {
            fscanf(file, "%s", &extraString);
            if (isComment(extraString) == LINEAR_COMMENT)
                passLinearComments(file);
        }
    }

    return isGetNum != -1;
}

int getDoubleNumFromFile(FILE *file, double *value) {
    assert(file != NULL);
    assert(value != NULL);

    char extraString[1000] = {};
    int isGetNum = 0;
    while (!isGetNum) {
        isGetNum = fscanf(file, "%lf", value);
        if (!isGetNum) {
            fscanf(file, "%s", &extraString);
            if (isComment(extraString) == LINEAR_COMMENT)
                passLinearComments(file);
        }
    }

    return isGetNum != -1;
}

void showTestResult(int number, struct TestData test) {
    if ( test.finalResult == ERROR || !(isfinite(test.a) && isfinite(test.b) && isfinite(test.c)) ) {
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
    showAnswer(test.programSolution);
    printf("\nTest output:\n");
    showAnswer(test.testSolution);
    printf("\nResult: %s\n\n\n", ((test.finalResult) ? "OK" : "WRONG ANSWER"));
}

int getTestsOfQuadraticEq(struct TestData testsData[], int maxLenTestsArray) {
    assert(testsData != NULL);
    assert(maxLenTestsArray > 0);

    int countTestResults = 0;
    FILE *dataTestsFile = fopen("tests.txt", "r");

    if (dataTestsFile == NULL)
        return 0;

    while (1) {
        struct TestData testNow = { NAN, NAN, NAN, { { NAN, NAN }, DOES_NOT_EXIST }, { { NAN, NAN }, DOES_NOT_EXIST }, ERROR };

        // Переменные вида resValue хранят данные о том, смогли ли присвоить присвоить testA, testB и testC числовые значения
        int resValueA = getDoubleNumFromFile(dataTestsFile, &testNow.a);
        int resValueB = getDoubleNumFromFile(dataTestsFile, &testNow.b);
        int resValueC = getDoubleNumFromFile(dataTestsFile, &testNow.c);

        if (!resValueA || countTestResults >= maxLenTestsArray) {
            fclose(dataTestsFile);
            return countTestResults;
        }

        if (!resValueB && !resValueC) {
            testsData[countTestResults++] = testNow;
            break;
        }

        if (!(isfinite(testNow.a) && isfinite(testNow.b) && isfinite(testNow.c))) {
            testsData[countTestResults++] = testNow;
            break;
        }

        int kindAnswer = -1;
        if (!getIntNumFromFile(dataTestsFile, &kindAnswer)) {
            testsData[countTestResults++] = testNow;
            break;
        }

        testNow.programSolution = quadraticEq(testNow.a, testNow.b, testNow.c);
        switch (kindAnswer) {
            case ONE_SOLUTION:
                testNow.testSolution.solutionsCount = ONE_SOLUTION;
                if (getDoubleNumFromFile(dataTestsFile, &testNow.testSolution.value[0])) {
                    if (testNow.programSolution.solutionsCount == ONE_SOLUTION
                        && isTwoDoubleEqual(testNow.programSolution.value[0], testNow.testSolution.value[0]))
                        testNow.finalResult = OK;
                    else
                        testNow.finalResult = WRONG_ANSWER;
                    testsData[countTestResults++] = testNow;
                } else {
                    testsData[countTestResults++] = testNow;
                    fclose(dataTestsFile);
                    return countTestResults;
                }
                break;

            case TWO_SOLUTIONS:
                testNow.testSolution.solutionsCount = TWO_SOLUTIONS;
                if (getDoubleNumFromFile(dataTestsFile, &testNow.testSolution.value[0])) {
                    if (getDoubleNumFromFile(dataTestsFile, &testNow.testSolution.value[1])) {
                        if (testNow.programSolution.solutionsCount == TWO_SOLUTIONS
                            && isTwoDoubleEqual(testNow.programSolution.value[0], testNow.testSolution.value[0])
                            && isTwoDoubleEqual(testNow.programSolution.value[1], testNow.testSolution.value[1]))
                            testNow.finalResult = OK;
                        else
                            testNow.finalResult = WRONG_ANSWER;
                        testsData[countTestResults++] = testNow;
                    } else {
                        testsData[countTestResults++] = testNow;
                        fclose(dataTestsFile);
                        return countTestResults;
                    }
                } else {
                    testsData[countTestResults++] = testNow;
                    fclose(dataTestsFile);
                    return countTestResults;
                }
                break;

            case ALL_SOLUTIONS:
                testNow.testSolution.solutionsCount = ALL_SOLUTIONS;
                if (testNow.programSolution.solutionsCount == ALL_SOLUTIONS)
                    testNow.finalResult = OK;
                else
                    testNow.finalResult = WRONG_ANSWER;
                testsData[countTestResults++] = testNow;
                break;

            case NO_SOLUTIONS:
                testNow.testSolution.solutionsCount = NO_SOLUTIONS;
                if (testNow.programSolution.solutionsCount == NO_SOLUTIONS)
                    testNow.finalResult = OK;
                else
                    testNow.finalResult = WRONG_ANSWER;
                testsData[countTestResults++] = testNow;
                break;

            default:
                testsData[countTestResults++] = testNow;
                fclose(dataTestsFile);
                return countTestResults;
                break;
        }
    }

    fclose(dataTestsFile);
    return countTestResults;
}

int main() {
    struct TestData testsData[1000] = {};

    printf("Unit-tests of the quadratic equations:\n");
    int countTestResults = getTestsOfQuadraticEq(testsData, 1000);

    for (int testNum = 0; testNum < countTestResults; testNum++)
        showTestResult(testNum + 1, testsData[testNum]);

    // коротко выводит результаты о том, какие тесты пройдены, а какие нет
    if (testsData[countTestResults - 1].finalResult != ERROR)
        for (int testNum = 0; testNum < countTestResults; testNum++)
            printf("Test #%d: %s\n", testNum + 1, ((testsData[testNum].finalResult) ? "OK" : "WRONG ANSWER"));

    return 0;
}
