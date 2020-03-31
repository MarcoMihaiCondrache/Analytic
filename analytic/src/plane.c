#include "../../log/log.h"
#include "../global.h"
#include "../plane.h"
#include "../geometry.h"

void Analytic_setBackground(SDL_Color color, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
}

void Analytic_setAxes(SDL_Color color, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int x = 0;
    for (int y = -(SDL_WINDOW_SIZE / 2); y < SDL_WINDOW_SIZE / 2; y++)
    {
        Analytic_Position position = {x, y};
        if (y % DIVISOR == 0)
        {
            for (x = x - 5; x < 5; x++)
            {
                Analytic_Position position2 = {x, y};
                Analytic_createPoint(position2, red, renderer);
                position2.y = y * -1;
                Analytic_createPoint(position2, red, renderer);
            }
            x -= 5;
        }
        Analytic_createPoint(position, color, renderer);
    }

    int y = 0;
    for (int x = -(SDL_WINDOW_SIZE / 2); x < SDL_WINDOW_SIZE / 2; x++)
    {
        Analytic_Position position = {x, y};
        if (x % DIVISOR == 0)
        {
            for (y = y - 5; y < 5; y++)
            {
                Analytic_Position position2 = {x, y};
                Analytic_createPoint(position2, red, renderer);
                position2.x = x * -1;
                Analytic_createPoint(position2, red, renderer);
            }
            y -= 5;
        }
        Analytic_createPoint(position, color, renderer);
    }

    SDL_RenderDrawLine(renderer, (SDL_WINDOW_SIZE / 2) - 7, 10, SDL_WINDOW_SIZE / 2, 0);
    SDL_RenderDrawLine(renderer, (SDL_WINDOW_SIZE / 2) + 7, 10, SDL_WINDOW_SIZE / 2, 0);
    SDL_RenderDrawLine(renderer, SDL_WINDOW_SIZE - 10, (SDL_WINDOW_SIZE / 2) - 7, SDL_WINDOW_SIZE, SDL_WINDOW_SIZE / 2);
    SDL_RenderDrawLine(renderer, SDL_WINDOW_SIZE - 10, (SDL_WINDOW_SIZE / 2) + 7, SDL_WINDOW_SIZE, SDL_WINDOW_SIZE / 2);
}

void Analytic_initPlane(SDL_Renderer *renderer)
{
    Analytic_setBackground(black, renderer);
    Analytic_setAxes(white, renderer);
}

void Analytic_renderMethod(SDL_Renderer *renderer)
{
    if (SINGLE.dataSet[ANALYTIC_POSITION_DATASET] && SINGLE.dataSet[ANALYTIC_CIRCUMFERENCE_DATASET])
        Analytic_createTangents(SINGLE.position, SINGLE.circumference, renderer);
    if (SINGLE.dataSet[ANALYTIC_LINE_DATASET])
        Analytic_createLine(SINGLE.line, renderer);
    if (SINGLE.dataSet[ANALYTIC_CIRCUMFERENCE_DATASET])
        Analytic_createCircumference(SINGLE.circumference, renderer);
    if (SINGLE.dataSet[ANALYTIC_PARABOLA_DATASET])
        Analytic_createParabola(SINGLE.parabola, renderer);
    if (SINGLE.dataSet[ANALYTIC_HYPERBOLE_DATASET])
        Analytic_createHyperbole(SINGLE.hyperbole, renderer);
    log_debug("Rendering with zoom: %dx", DIVISOR / 10);
    SDL_RenderPresent(renderer);
}