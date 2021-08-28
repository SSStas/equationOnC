#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define IN 1
#define OUT 0


int isNumber(char word[], int lenWord)
{
    if (lenWord == 0)
        return 0;
    else if (lenWord == 1)
        return (isdigit(word[0]) ? 1 : 0);
    else if (lenWord >= 2) {

        int pointPos = -1;
        for (int letterIndex = 0; letterIndex < lenWord; letterIndex++) {
            if (word[letterIndex] == '.' || word[letterIndex] == ',') {
                if (pointPos != -1)
                    return 0;
                pointPos = letterIndex;
            }
        }

        if (pointPos + 1 == lenWord || pointPos == 0 || (word[0] == '-' && (word[1] == '.' || word[1] == ',') ))
            return 0;

        for (int letterIndex = (word[0] == '-' ? 1 : 0); letterIndex < lenWord; letterIndex++)
            if (!isdigit(word[letterIndex]) && word[letterIndex] != '.' && word[letterIndex] != ',')
                return 0;
        return 1;
    }
}

double strToDouble(char word[], int lenWord)
{
    if (!isNumber(word, lenWord))
        return NAN;

    int numMinus = (word[0] == '-' ? -1 : 1);
    int beforePoint = 1;
    int point = -1;
    double result = 0.0;
    for (int letterIndex = (word[0] == '-' ? 1 : 0); letterIndex < lenWord; letterIndex++)
        if (word[letterIndex] == '.' || word[letterIndex] == ',')
            beforePoint = 0;
        else {
            if (beforePoint)
                result = result * 10 + (word[letterIndex] - '0');
            else {
                result += pow(10, point) * (word[letterIndex] - '0');
                point--;
            }
        }
    return numMinus * result;
}

int scanNumbers(double numbers[], int countOfNums, int startIndex)
{
    int countNumsNow = 0;
    char word[1000];
    int lenWord = 0;
    int state = OUT;
    char c;
    while ((c = getchar()) != '\n') {

        if (isspace(c)) {
            if (state == IN) {
                double num = strToDouble(word, lenWord);
                if (!isnan(num) && countNumsNow < countOfNums) {
                    numbers[startIndex + countNumsNow++] = num;
                }
            }
            state = OUT;
            lenWord = 0;
        }

        if (isalnum(c) || c == '.' || c == ',' || c == '-') {
            word[lenWord] = c;
            state = IN;
            lenWord++;
        }
    }

    if (state == IN) {
        double num = strToDouble(word, lenWord);
        if (!isnan(num) && countNumsNow < countOfNums) {
            numbers[startIndex + countNumsNow++] = num;
        }
    }

    return countNumsNow;
}

void getConstants(double *a, double *b, double *c)
{
    int countConstInput = 0;
    double input[3];
    while (countConstInput < 3)
        countConstInput += scanNumbers(input, 3 - countConstInput, countConstInput);

    *a = input[0];
    *b = input[1];
    *c = input[2];
}

