#include <fxcg/display.h>
#include <fxcg/keyboard.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
int* primeFactors(int n);
char* primeFactorsAsString(int n);

int main() {
    PrintXY(1, 1, "--Prime Factorization", TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
    char *buffer = (char*) malloc(256);
    int start = 0;
    int cursor = 0;
    buffer[0] = '\0';

    int key;

    DisplayMBString((unsigned char*) buffer, start, cursor, 1, 2);

    while (1) {
        GetKey(&key);

        if (key == KEY_CTRL_EXE) {
            struct display_fill fill;
            fill.x1=0;
            fill.x2=383;
            fill.y1=48+24;
            fill.y2=48+48;
            fill.mode=0;
            Bdisp_AreaClr(&fill,1,0);

            if (strlen(buffer) <= 7) {
                int input = atoi(buffer);
                char bufferTwo[102] = "--";
                strcat(bufferTwo, primeFactorsAsString(input));
                PrintXY(1, 3, bufferTwo, TEXT_MODE_NORMAL, TEXT_COLOR_BLACK);
            } else {
                PrintXY(1, 3, "--Du Hurensohn", TEXT_MODE_NORMAL, TEXT_COLOR_RED);
            }
            buffer[0] = '\0';
            start = 0;
            cursor = 0;
            DisplayMBString((unsigned char*) buffer, start, cursor, 1, 2);
        } else if (key && key < 30000) {
            cursor = EditMBStringChar((unsigned char*) buffer, 256, cursor, key);
            DisplayMBString((unsigned char*) buffer, start, cursor, 1, 2);
        } else {
            EditMBStringCtrl((unsigned char*) buffer, 256, &start, &cursor, &key, 1, 2);
        }
    }
 
    return 0;
}

int* primeFactors(int n)
{
    if (n < 2) {
        static int result[2];
        result[0] = 1;
        result[1] = n;
        return result;
    }

    int size = 0;
    static int factors[33];
    //Max int has 32 factors, plus first spot in array for length of array.

    while (n%2 == 0)
    {
        size++;
        factors[size] = 2;
        n = n/2;
    }
 
    for (int i = 3; i <= n; i = i+2)
    {
        while (n%i == 0)
        {
            size++;
            factors[size] = i;
            n = n/i;
        }
    }
    if (n > 2)
    {
        size++;
        factors[size] = n;
    }

    factors[0] = size;
    return factors;
}

char* primeFactorsAsString(int n) {
    int *factors;

    factors = primeFactors(n);

    if (factors[0] > 25) {
        return "TO BIG";
    }
    static char result[100];
    char buffer[100];

    result[0] = '\0';

    for (int i = 1; i < factors[0]; i++)
    {
        sprintf(buffer, "%dx", factors[i]);
        strcat(result, buffer);
    }
    sprintf(buffer, "%d", factors[factors[0]]);
    strcat(result, buffer);

    return result;
}