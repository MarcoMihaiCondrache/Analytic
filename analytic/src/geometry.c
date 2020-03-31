#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../../log/log.h"
#include "../global.h"
#include "../geometry.h"
#include "../functions.h"
#include "../scale.h"

void Analytic_createPoint(Analytic_Position position, SDL_Color color, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, Analytic_convertXAbsolute(position.x), Analytic_convertYAbsolute(position.y));
}

void Analytic_createLine(Analytic_Line line, SDL_Renderer *renderer)
{
    for (float x = (SDL_WINDOW_SIZE / 2) * -1; Analytic_convertXAbsolute(x) <= SDL_WINDOW_SIZE; x += 0.1)
    {
        Analytic_Position position = {x, Analytic_LineFunction(line, x)};
        Analytic_createPoint(position, red, renderer);
    }
}

void Analytic_createParabola(Analytic_Parabola parabola, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, purple.r, purple.g, purple.b, purple.a);
    switch (parabola.type)
    {
    case Analytic_ParabolaY:
        for (float x = (SDL_WINDOW_SIZE / 2) * -1; Analytic_convertXAbsolute(x) <= SDL_WINDOW_SIZE; x += 0.1)
        {
            float x1 = x + 0.1, y = Analytic_ParabolaYFunction(parabola, x), y1 = Analytic_ParabolaYFunction(parabola, x1);
            if (Analytic_isXRelativeOK(x1) && Analytic_isYRelativeOK(y) && Analytic_isYRelativeOK(y1))
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(x * DIVISOR / 10), Analytic_convertYAbsolute(y * DIVISOR / 10), Analytic_convertXAbsolute(x1 * DIVISOR / 10), Analytic_convertYAbsolute(y1 * DIVISOR / 10));
        }
        break;
    case Analytic_ParabolaX:
        parabola.a *= -1;
        for (float y = (SDL_WINDOW_SIZE / 2) * -1; Analytic_convertXAbsolute(y) <= SDL_WINDOW_SIZE; y += 0.1)
        {
            float y1 = y + 0.1, x = Analytic_ParabolaXFunction(parabola, y), x1 = Analytic_ParabolaXFunction(parabola, y1);
            if (Analytic_isYRelativeOK(y1) && Analytic_isXRelativeOK(x) && Analytic_isXRelativeOK(x1))
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(x * DIVISOR / 10), Analytic_convertYAbsolute(y * DIVISOR / 10), Analytic_convertXAbsolute(x1 * DIVISOR / 10), Analytic_convertYAbsolute(y1 * DIVISOR / 10));
        }
        break;
    }
}

void Analytic_createCircumference(Analytic_Circumference circumference, SDL_Renderer *renderer)
{
    float radius = Analytic_CircumferenceRadiusFunction(circumference) * DIVISOR / 10;
    float x_centre = Analytic_CircumferenceXCentreFunction(circumference) * DIVISOR / 10;
    float y_centre = Analytic_CircumferenceYCentreFunction(circumference) * DIVISOR / 10;
    int x = radius, y = 0, err = 0;

    if (!Analytic_isXRelativeOK(x_centre + radius) && !Analytic_isYRelativeOK(y_centre + radius))
        log_debug("The centre of the circumference is out of the render view");

    while (x >= y)
    {
        Analytic_Position position = {x_centre + x, y_centre + y};
        Analytic_createPoint(position, green, renderer);
        position.x = x_centre - x;
        position.y = y_centre + y;
        Analytic_createPoint(position, green, renderer);
        position.x = x_centre + x;
        position.y = y_centre - y;
        Analytic_createPoint(position, green, renderer);
        position.x = x_centre - x;
        position.y = y_centre - y;
        Analytic_createPoint(position, green, renderer);
        position.x = x_centre + y;
        position.y = y_centre + x;
        Analytic_createPoint(position, green, renderer);
        position.x = x_centre - y;
        position.y = y_centre + x;
        Analytic_createPoint(position, green, renderer);
        position.x = x_centre + y;
        position.y = y_centre - x;
        Analytic_createPoint(position, green, renderer);
        position.x = x_centre - y;
        position.y = y_centre - x;
        Analytic_createPoint(position, green, renderer);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }

        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void Analytic_createTangents(Analytic_Position point, Analytic_Circumference circumference, SDL_Renderer *renderer)
{
    float cx0 = Analytic_CircumferenceXCentreFunction(circumference);
    float cy0 = Analytic_CircumferenceYCentreFunction(circumference);
    float cx1 = point.x;
    float cy1 = -point.y;
    float dx = cx0 - cx1;
    float dy = cy0 - cy1;
    double dist = sqrt(dx * dx + dy * dy);
    float r0 = Analytic_CircumferenceRadiusFunction(circumference);
    float r1 = sqrt(pow(dist, 2) - pow(r0, 2));

    if ((float)dist < (float)r0)
    {
        log_fatal("There are no tangent points!");
        exit(EXIT_FAILURE);
    }
    if ((float)dist == (float)r0)
    {
        Analytic_Line tangent1;
        float m = (cy1 - cy0) / (cx1 - cx0);
        float q = (cy1 - (m * cx1));
        tangent1.m = 1 / m;
        tangent1.q = -q;
        Analytic_createLine(tangent1, renderer);
        log_debug("Found a tagent: m = %f and q = %f", m, -q);
        return;
    }
    double a = (r0 * r0 -
                r1 * r1 + dist * dist) /
               (2 * dist);
    double h = sqrt(r0 * r0 - a * a);
    double cx2 = cx0 + a * (cx1 - cx0) / dist;
    double cy2 = cy0 + a * (cy1 - cy0) / dist;
    float x1 = (float)(cx2 + h * (cy1 - cy0) / dist);
    float y1 = (float)(cy2 - h * (cx1 - cx0) / dist);
    float x2 = (float)(cx2 - h * (cy1 - cy0) / dist);
    float y2 = (float)(cy2 + h * (cx1 - cx0) / dist);
    float m1 = (y1 - cy1) / (x1 - cx1);
    float m2 = (y2 - cy1) / (x2 - cx1);
    float q1 = (y1 - (m1 * x1));
    float q2 = (y2 - (m2 * x2));
    Analytic_Line tangent1, tangent2;
    tangent1.m = -m1;
    tangent1.q = -q1;
    tangent2.m = -m2;
    tangent2.q = -q2;
    Analytic_createLine(tangent1, renderer);
    Analytic_createLine(tangent2, renderer);
    log_debug("Found a tagent: m = %f and q = %f", -m1, -q1);
    log_debug("Found a tagent: m = %f and q = %f", -m2, -q2);
}

void Analytic_createHyperbole(Analytic_Hyperbole hyperbole, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, yellow.r, yellow.g, yellow.b, yellow.a);
    switch (hyperbole.type)
    {
    case Analytic_HyperboleY:
        for (float x0 = ((SDL_WINDOW_SIZE / 2) * -1); round(x0) != 0; x0 += 0.1)
        {
            float x1 = x0 + 0.1, y0 = Analytic_HyperboleYFunction(hyperbole, x0), y1 = Analytic_HyperboleYFunction(hyperbole, x1);
            if (isnan(y1))
                y1 = 0;
            if (Analytic_isXRelativeOK(x0) && Analytic_isXRelativeOK(x1) && Analytic_isYRelativeOK(y0) && Analytic_isYRelativeOK(y1))
            {
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(x0 * DIVISOR / 10), Analytic_convertYAbsolute(y0 * DIVISOR / 10), Analytic_convertXAbsolute(x1 * DIVISOR / 10), Analytic_convertYAbsolute(y1 * DIVISOR / 10));
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(-x0 * DIVISOR / 10), Analytic_convertYAbsolute(y0 * DIVISOR / 10), Analytic_convertXAbsolute(-x1 * DIVISOR / 10), Analytic_convertYAbsolute(y1 * DIVISOR / 10));
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(-x0 * DIVISOR / 10), Analytic_convertYAbsolute(-y0 * DIVISOR / 10), Analytic_convertXAbsolute(-x1 * DIVISOR / 10), Analytic_convertYAbsolute(-y1 * DIVISOR / 10));
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(x0 * DIVISOR / 10), Analytic_convertYAbsolute(-y0 * DIVISOR / 10), Analytic_convertXAbsolute(x1 * DIVISOR / 10), Analytic_convertYAbsolute(-y1 * DIVISOR / 10));
            }
        }
        break;
    case Analytic_HyperboleX:
        for (float x0 = ((SDL_WINDOW_SIZE / 2) * -1); floor(x0) != 0; x0 += 0.1)
        {
            float x1 = x0 + 0.1, y0 = Analytic_HyperboleXFunction(hyperbole, x0), y1 = Analytic_HyperboleXFunction(hyperbole, x1);
            if (isnan(y1))
                y1 = 0;
            if (Analytic_isXRelativeOK(x0) && Analytic_isXRelativeOK(x1) && Analytic_isYRelativeOK(y0) && Analytic_isYRelativeOK(y1))
            {
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(x0 * DIVISOR / 10), Analytic_convertYAbsolute(y0 * DIVISOR / 10), Analytic_convertXAbsolute(x1 * DIVISOR / 10), Analytic_convertYAbsolute(y1 * DIVISOR / 10));
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(-x0 * DIVISOR / 10), Analytic_convertYAbsolute(y0 * DIVISOR / 10), Analytic_convertXAbsolute(-x1 * DIVISOR / 10), Analytic_convertYAbsolute(y1 * DIVISOR / 10));
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(-x0 * DIVISOR / 10), Analytic_convertYAbsolute(-y0 * DIVISOR / 10), Analytic_convertXAbsolute(-x1 * DIVISOR / 10), Analytic_convertYAbsolute(-y1 * DIVISOR / 10));
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(x0 * DIVISOR / 10), Analytic_convertYAbsolute(-y0 * DIVISOR / 10), Analytic_convertXAbsolute(x1 * DIVISOR / 10), Analytic_convertYAbsolute(-y1 * DIVISOR / 10));
            }
        }
        break;
    case Analytic_HyperboleK:
        for (float x0 = ((SDL_WINDOW_SIZE / 2) * -1); Analytic_convertXAbsolute(x0) <= SDL_WINDOW_SIZE; x0 += 0.1)
        {
            if ((float)(roundf(x0 * 10) / 10) == (float)-0.1) // PREVENT NAN RESULT
                continue;
            float x1 = x0 + 0.1, y0 = Analytic_HyperboleKFunction(hyperbole, x0), y1 = Analytic_HyperboleKFunction(hyperbole, x1);
            if (Analytic_isXRelativeOK(x0) && Analytic_isXRelativeOK(x1) && Analytic_isYRelativeOK(y0) && Analytic_isYRelativeOK(y1))
            {
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(x0 * DIVISOR / 10), Analytic_convertYAbsolute(y0 * DIVISOR / 10), Analytic_convertXAbsolute(x1 * DIVISOR / 10), Analytic_convertYAbsolute(y1 * DIVISOR / 10));
            }
        }
        break;
    case Analytic_HyperboleHomographic:
    {
        SDL_SetRenderDrawColor(renderer, red.r, red.g, red.b, red.a);
        float firstAxe = (-hyperbole.d) / hyperbole.c;
        float secondAxe = (hyperbole.a / hyperbole.c);
        SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(firstAxe * DIVISOR / 10), SDL_WINDOW_SIZE, Analytic_convertXAbsolute(firstAxe * DIVISOR / 10), 0);
        SDL_RenderDrawLine(renderer, 0, Analytic_convertYAbsolute(secondAxe * DIVISOR / 10), SDL_WINDOW_SIZE, Analytic_convertYAbsolute(secondAxe * DIVISOR / 10));
        SDL_SetRenderDrawColor(renderer, yellow.r, yellow.g, yellow.b, yellow.a);
        for (float x0 = ((SDL_WINDOW_SIZE / 2) * -1); Analytic_convertXAbsolute(x0) <= SDL_WINDOW_SIZE; x0 += 0.1)
        {
            float x1 = x0 + 0.1, y0 = Analytic_HyperboleHomographicFunction(hyperbole, x0), y1 = Analytic_HyperboleHomographicFunction(hyperbole, x1);
            if ((float)(roundf(x1 * 10) / 10) == firstAxe) // PREVENT DRAWING THE AXE
                continue;
            if (Analytic_isXRelativeOK(x0) && Analytic_isXRelativeOK(x1) && Analytic_isYRelativeOK(y0) && Analytic_isYRelativeOK(y1))
            {
                SDL_RenderDrawLine(renderer, Analytic_convertXAbsolute(x0 * DIVISOR / 10), Analytic_convertYAbsolute(y0 * DIVISOR / 10), Analytic_convertXAbsolute(x1 * DIVISOR / 10), Analytic_convertYAbsolute(y1 * DIVISOR / 10));
            }
        }
        break;
    }
    }
}