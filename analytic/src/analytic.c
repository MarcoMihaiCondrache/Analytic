#include "../global.h"

void Analytic_initDataSet()
{
    for (int i = 0; i < 5; i++)
    {
        SINGLE.dataSet[i] = false;
    }
}

void Analytic_setDataSet(int INDEX, bool VALUE)
{
    SINGLE.dataSet[INDEX] = VALUE;
}

void Analytic_setDivisor(float _DIVISOR)
{
    DIVISOR = _DIVISOR;
}

void Analytic_setScale(float _SCALE)
{
    SCALE = _SCALE;
}

void Analytic_setWindowSize(int _SDL_WINDOW_SIZE)
{
    SDL_WINDOW_SIZE = _SDL_WINDOW_SIZE;
}

void Analytic_setTerminalOutput(bool _TERMINAL_OUTPUT)
{
    TERMINAL_OUTPUT = _TERMINAL_OUTPUT;
}