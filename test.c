#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "quadratic.h"

enum TestResults {
    ERROR = 0,
    OK = 1
};

enum KindsComments {
    ITS_NOT_COMMENT = 0,
    LINEAR_COMMENT = 1,
    MULTILINEAR_COMMENT = 2
};


int isTwoDoubleEqual(double value1, double value2)
{
    return ( (isfinite(value1) && isfinite(value2)) ? (fabs(value1 - value2) < 0.000001) : 0 );
}

enum KindsComments isComment(char word[])
{
    assert( word != NULL );

    if (word[0] == '#' && word[1] == '#' && word[2] == '#')
        return MULTILINEAR_COMMENT;

    if (word[0] == '#')
        return LINEAR_COMMENT;

    return ITS_NOT_COMMENT;
}

void passLinearComments(FILE *file)
{
    assert( file != NULL );

    char ch = '0';
    while ((ch = fgetc(file)) != EOF)
        if (ch == '\n')
            break;
}

void passMultilinearComment(FILE *file)
{
    assert( file != NULL );

    char extraString[1000] = {};
    int isEOF = 0;
    while (!isEOF) {
        isEOF = ( (fscanf(file, "%s", &extraString) == -1) ? 1 : 0);

        if (isComment(extraString) == MULTILINEAR_COMMENT)
            break;
    }
}

int getIntNumFromFile(FILE *file, int *value)
{
    assert( file != NULL );
    assert( value != NULL );

    char extraString[1000] = {};
    int isGetNum = 0;
    while (!isGetNum) {
        isGetNum = fscanf(file, "%d", value);

        if (!isGetNum) {
            fscanf(file, "%s", &extraString);

            if (isComment(extraString) == LINEAR_COMMENT)
                passLinearComments(file);
            else if (isComment(extraString) == MULTILINEAR_COMMENT)
                passMultilinearComment(file);
        }
    }
    return isGetNum != -1;
}

int getDoubleNumFromFile(FILE *file, double *value)
{
    assert( file != NULL );
    assert( value != NULL );

    char extraString[1000] = {};
    int isGetNum = 0;
    while (!isGetNum) {
        isGetNum = fscanf(file, "%lf", value);

        if (!isGetNum) {
            fscanf(file, "%s", &extraString);

            if (isComment(extraString) == LINEAR_COMMENT)
                passLinearComments(file);
            else if (isComment(extraString) == MULTILINEAR_COMMENT)
                passMultilinearComment(file);
        }
    }

    return isGetNum != -1;
}

void showTestResult(int number, double a, double b, double c, struct RootsOfEquation testAnswer, struct RootsOfEquation programAnswer)
{
    assert( isfinite(a) );
    assert( isfinite(b) );
    assert( isfinite(c) );

    int lenTitle = floorf(log10(number)) + 7;
    for (int sizeLine = 0; sizeLine < lenTitle; sizeLine++) { printf("-"); }
    printf("\nTest #%d\n", number);
    for (int sizeLine = 0; sizeLine < lenTitle; sizeLine++) { printf("-"); }

    printf("\n\n");

    printf("Equation: ");
    showFuncOfQuadraticEq(a, b, c);

    printf("\nProgram output:\n");
    showAnswer(programAnswer);

    printf("\nTest output:\n");
    showAnswer(testAnswer);

    printf("\n");
}

void testingQuadraticEq()
{
    enum TestResults shortTestResults[1000] = { ERROR };
    int countTestResults = 0;
    int isErrorInFile = 0;
    FILE *dataTestsFile = fopen("tests.txt", "r");

    if (dataTestsFile == NULL) {
        printf("Error: Could not read the file \"tests.txt\"\n");
        return;
    }

    int isContinueInput = 1;
    while (isContinueInput) {
        double testA = NAN, testB = NAN, testC = NAN;

        // Переменные вида resValue хранят данные о том, смогли ли присвоить присвоить testA, testB и testC числовые значения
        int resValueA = getDoubleNumFromFile(dataTestsFile, &testA);
        int resValueB = getDoubleNumFromFile(dataTestsFile, &testB);
        int resValueC = getDoubleNumFromFile(dataTestsFile, &testC);

        if (!resValueA)
            break;

        if (!resValueB && !resValueC) {
            printf("Error: Could not read the values of the constants\n");
            isErrorInFile = 1;
            break;
        }

        if ( !(isfinite(testA) && isfinite(testB) && isfinite(testC)) )
        {
            printf("Error: Invalid values\n");
            isErrorInFile = 1;
            break;
        }

        int kindAnswer = -1;
        if (!getIntNumFromFile(dataTestsFile, &kindAnswer)) {
            printf("Error: Could not read the response format value\n");
            isErrorInFile = 1;
            break;
        }

        double testRootOfEq1 = NAN, testRootOfEq2 = NAN;

        struct RootsOfEquation programAnswer = quadraticEq(testA, testB, testC);


        switch (kindAnswer)
        {
            case ONE_SOLUTION:
                if ((isContinueInput = getDoubleNumFromFile(dataTestsFile, &testRootOfEq1)) == 1) {

                    if (programAnswer.solutionsCount == ONE_SOLUTION && isTwoDoubleEqual(programAnswer.value[0], testRootOfEq1))
                        shortTestResults[countTestResults++] = OK;
                    else
                        shortTestResults[countTestResults++] = ERROR;

                } else {
                    printf("Error: Could not read the value of the root\n");
                    isErrorInFile = 1;
                }

                break;

            case TWO_SOLUTIONS:
                if ((isContinueInput = getDoubleNumFromFile(dataTestsFile, &testRootOfEq1)) == 1) {

                    if ((isContinueInput = getDoubleNumFromFile(dataTestsFile, &testRootOfEq2)) == 1) {

                        if (programAnswer.solutionsCount == TWO_SOLUTIONS && isTwoDoubleEqual(programAnswer.value[0], testRootOfEq1) &&
                            isTwoDoubleEqual(programAnswer.value[1], testRootOfEq2))
                            shortTestResults[countTestResults++] = OK;
                        else
                            shortTestResults[countTestResults++] = ERROR;

                    } else {
                        printf("Error: Could not read the value of the second root\n");
                        isErrorInFile = 1;
                    }

                } else {
                    printf("Error: Could not read the value of the first root\n");
                    isErrorInFile = 1;
                }

                break;

            case ALL_SOLUTIONS:
                if (programAnswer.solutionsCount == ALL_SOLUTIONS)
                    shortTestResults[countTestResults++] = OK;
                else
                    shortTestResults[countTestResults++] = ERROR;

                break;

            case NO_SOLUTIONS:
                if (programAnswer.solutionsCount == NO_SOLUTIONS)
                    shortTestResults[countTestResults++] = OK;
                else
                    shortTestResults[countTestResults++] = ERROR;

                break;

            default:
                isContinueInput = 0;
                printf("Error: Invalid value of answer's type\n");
                isErrorInFile = 1;

                break;
        }

        if (isContinueInput == 1) {
            showTestResult(countTestResults, testA, testB, testC, { {testRootOfEq1, testRootOfEq2}, (enum SolutionsKinds) (kindAnswer)}, programAnswer);
            printf("Result: %s\n\n\n", ( (shortTestResults[countTestResults - 1]) ? "OK" : "ERROR"));
        }
    }


    // коротко выводит результаты о том, какие тесты пройдены, а какие нет
    if (!isErrorInFile)
        for (int testNum = 0; testNum < countTestResults; testNum++)
            printf("Test #%d: %s\n", testNum + 1, ( (shortTestResults[testNum]) ? "OK" : "ERROR") );


    fclose(dataTestsFile);
}

int main()
{

	printf("Unit-tests of the quadratic equations:\n");
	testingQuadraticEq();

	return 0;
}
