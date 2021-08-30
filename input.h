#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#define IN 1
#define OUT 0

int isNumber(char word[], int lenWord);
double strToDouble(char word[], int lenWord);
int scanNumbers(double numbers[], int countOfNums, int startIndex);
void getConstants(double *a, double *b, double *c);


#endif // INPUT_H_INCLUDED
