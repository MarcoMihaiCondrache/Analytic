/**
 * @file draw.c
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Analytic, a simple program for the graphic representation of the most common
 * geometric places: Straight lines, Circumferences, Hyperbolas and Parables
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

#define NDEBUG
#include <assert.h>
#include <errno.h>
#include <string.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include <analytic/analytic.h>
#include <analytic/global.h>
#include <analytic/scale.h>
#include <analytic/functions.h>
#include <analytic/geometry.h>
#include <analytic/plane.h>

#include <log/log.h>

#include <ui/input.h>
#include <ui/output.h>

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

/**
 * @brief Main method of the program
 * 
 * Main method of the program, controls the windo \n
 * and manages external inputs and events such as the \n
 * control on the mouse wheel \n
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    bool quit;
    FILE *log_file;
    SDL_Event event;
    SDL_Window *window;
    SDL_Renderer *renderer;
init:;
    quit = false;
    log_file = NULL;
    window = NULL;
    renderer = NULL;
    Analytic_setScale(DEFAULT_SCALE);
    Analytic_setDivisor(DEFAULT_DIVISOR);
    Analytic_setWindowSize(800);
    Analytic_setTerminalOutput(true);
    Analytic_initDataSet();

    log_file = fopen("logs.txt", "a");
    log_set_fp(log_file);
    log_set_level(LOG_INFO);
    log_set_quiet(!TERMINAL_OUTPUT);
    log_set_specs(false);
    log_set_date(false);

    static const char *menu1options[] = {"Draw a straight line", "Draw a circumference", "Draw tangents to a circumference passing through a point", "Draw a parabola", "Draw an hyperbole", "Exit"};
    const int place = Ui_handleMenu("What do you want to do?:", "Select an option:", menu1options, 6, true);
    switch (place)
    {
    case 0:
    {
        Analytic_setDataSet(ANALYTIC_LINE_DATASET, true);
        Ui_clear();
        Ui_printWithNewLine("The straight line equation must be in the following form: y = mx + q\n");
        Ui_readInput("Please enter the coefficient m (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.line.m);
        Ui_readInput("Please enter the coefficient q (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.line.q);
        Ui_printWithNewLine("\nThe rendering has been started in a new window...");
        if (SINGLE.line.m == 0 && SINGLE.line.q == 0)
            Ui_showWarningDialog("You are going to draw the vertical axe!");
        break;
    }
    case 1:
    {
        Analytic_setDataSet(ANALYTIC_CIRCUMFERENCE_DATASET, true);
        Ui_clear();
        Ui_printWithNewLine("The circumference equation must be in the following form: x^2 + y^2 + ax + by + c = 0\n");
        Ui_readInput("Please enter the coefficient a (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.circumference.a);
        Ui_readInput("Please enter the coefficient b (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.circumference.b);
        Ui_readInput("Please enter the coefficient c (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.circumference.c);
        Ui_printWithNewLine("\nThe rendering has been started in a new window...");
        if (SINGLE.circumference.a == 0 && SINGLE.circumference.b == 0 && SINGLE.circumference.c == 0)
            Ui_showWarningDialog("You are going to draw a point! (radius = 0)");
        break;
    }
    case 2:
        Analytic_setDataSet(ANALYTIC_POSITION_DATASET, true);
        Analytic_setDataSet(ANALYTIC_CIRCUMFERENCE_DATASET, true);
        Ui_clear();
        Ui_printWithNewLine("We need a point and circumference (x^2 + y^2 + ax + by + c = 0) to find the tagents");
        Ui_readInput("Please enter the x of the point (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.position.x);
        Ui_readInput("Please enter the y of the point (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.position.y);
        Ui_readInput("Please enter the coefficient a (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.circumference.a);
        Ui_readInput("Please enter the coefficient b (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.circumference.b);
        Ui_readInput("Please enter the coefficient c (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.circumference.c);
        Ui_printWithNewLine("\nThe rendering has been started in a new window...");
        if (SINGLE.circumference.a == 0 && SINGLE.circumference.b == 0 && SINGLE.circumference.c == 0)
        {
            Ui_showWarningDialog("You are going to draw a point! (radius = 0)");
        }
        break;
    case 3:
    {
        Analytic_setDataSet(ANALYTIC_PARABOLA_DATASET, true);
        static const char *parabolaTypes[] = {"Equation: y = ax^2 + bx + c", "Equation: x = ay^2 + by + c"};
        int type = Ui_handleMenu("Please select the type of the parabola", "Select an option", parabolaTypes, 2, true);
        SINGLE.parabola.type = type == 0 ? Analytic_ParabolaY : Analytic_ParabolaX;
        Ui_printWithNewLine(type == 0 ? "The parabola equation must be in the following form: y = ax^2 + bx + c\n" : "The parabola equation must be in the following form: x = ay^2 + by + c\n");
        Ui_readInput("Please enter the coefficient a (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.parabola.a);
        Ui_readInput("Please enter the coefficient b (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.parabola.b);
        Ui_readInput("Please enter the coefficient c (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.parabola.c);
        Ui_printWithNewLine("\nThe rendering has been started in a new window...");
        if (SINGLE.parabola.a == 0)
        {
            Ui_showWarningDialog("You are going to draw a line!");
            Analytic_setDataSet(ANALYTIC_PARABOLA_DATASET, false);
            Analytic_setDataSet(ANALYTIC_LINE_DATASET, true);
            if (type == 0)
            {
                SINGLE.line.m = SINGLE.parabola.b;
                SINGLE.line.q = SINGLE.parabola.c;
            }
            else
            {
                SINGLE.line.m = 1 / SINGLE.parabola.b;
                SINGLE.line.q = 1 * SINGLE.parabola.c;
            }
        }
        break;
    }
    case 4:
    {
        Analytic_setDataSet(ANALYTIC_HYPERBOLE_DATASET, true);
        static const char *parabolaTypes[] = {"Equation: (x^2 / a^2) - (y^2 / b^2) = 1", "Equation: (x^2 / a^2) - (y^2 / b^2) = -1", "Equation: xy = k", "Homographic Function: y = (ax + b) / (cx + d)"};
        int type = Ui_handleMenu("Please select the type of the hyperbole", "Select an option", parabolaTypes, 4, true);
        switch (type)
        {
        case 0:
            SINGLE.hyperbole.type = Analytic_HyperboleY;
            Ui_printWithNewLine("The hyperbole equation must be in the following form: (x^2 / a^2) - (y^2 / b^2) = 1\n");
            Ui_readInput("Please enter the coefficient a^2 (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.a);
            Ui_readInput("Please enter the coefficient b^2 (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.b);
            Ui_printWithNewLine("\nThe rendering has been started in a new window...");
            break;
        case 1:
            SINGLE.hyperbole.type = Analytic_HyperboleX;
            Ui_printWithNewLine("The hyperbole equation must be in the following form: (x^2 / a^2) - (y^2 / b^2) = -1\n");
            Ui_readInput("Please enter the coefficient a^2 (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.a);
            Ui_readInput("Please enter the coefficient b^2 (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.b);
            Ui_printWithNewLine("\nThe rendering has been started in a new window...");
            break;
        case 2:
            SINGLE.hyperbole.type = Analytic_HyperboleK;
            Ui_printWithNewLine("The hyperbole equation must be in the following form: xy = k\n");
            Ui_readInput("Please enter the coefficient k (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.k);
            Ui_printWithNewLine("\nThe rendering has been started in a new window...");
            break;
        case 3:
            SINGLE.hyperbole.type = Analytic_HyperboleHomographic;
            Ui_printWithNewLine("We are going to use the function: y = (ax + b) / (cx + d)\n");
            Ui_readInput("Please enter the coefficient a (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.a);
            Ui_readInput("Please enter the coefficient b (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.b);
            Ui_readInput("Please enter the coefficient c (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.c);
            Ui_readInput("Please enter the coefficient d (numbers with a maximum of 6 digits after the comma are accepted)", "%f", &SINGLE.hyperbole.d);
            Ui_printWithNewLine("\nThe rendering has been started in a new window...");
            break;
        }
        break;
    }
    case 5:
        return EXIT_SUCCESS;
        break;
    }
    SDL_Init(SDL_INIT_EVENTS);
    window = SDL_CreateWindow("Analytic Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SDL_WINDOW_SIZE, SDL_WINDOW_SIZE, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    /* DEBUG ASSERT */
    assert(window != NULL);
    assert(renderer != NULL);
    assert(!quit);
    /* DEBUG ASSERT */

    /* USER ERROR */
    if (window == NULL)
        log_error("Window error: %s", SDL_GetError());
    if (renderer == NULL)
        log_error("Renderer error: %s", SDL_GetError());
    /* USER ERROR */

    Analytic_initPlane(renderer);
    Analytic_renderMethod(renderer);

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y == -1)
                    Analytic_scaleIn(renderer);
                else if (event.wheel.y == 1)
                    Analytic_scaleOut(renderer);
                Analytic_setDivisor(Analytic_calculateDivisor());
                break;
            }
        }
    }

    Ui_printWithNewLine("\nQuit interrupt received");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    fclose(log_file);
    goto init;
}