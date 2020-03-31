#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <ctype.h>
#include "../global.h"
#include "../input.h"
#include "../output.h"

int Ui_readInput(const char *leading, const char *format, ...)
{
    va_list inputArg;
    int whileExit = 0;
    va_start(inputArg, format);
    while (!whileExit)
    {
        printf(leading);
        printf("\n");
        printf(TRAILING);
        whileExit = vscanf(format, inputArg);
        while (getchar() != '\n')
            continue;
    }
    va_end(inputArg);
    return whileExit;
}