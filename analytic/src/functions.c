#include "../../log/log.h"
#include "../global.h"
#include "../functions.h"

int Analytic_LineFunction(Analytic_Line line, float x)
{
    return round(-1 * line.m * x + (-1 * line.q * DIVISOR / 10));
}

float Analytic_ParabolaYFunction(Analytic_Parabola parabola, float x)
{
    return (-(parabola.a * x * x) - (parabola.b * x) - (parabola.c));
}

float Analytic_ParabolaXFunction(Analytic_Parabola parabola, float y)
{
    return -((parabola.a * y * y) + (parabola.b * y) - (parabola.c));
}

float Analytic_CircumferenceRadiusFunction(Analytic_Circumference circumference)
{
    float r2 = (pow(circumference.a, 2) / 4) + (pow(circumference.b, 2) / 4) - circumference.c;
    if (r2 < 0)
    {
        log_fatal("This is not a circumference! (negative radius)");
        exit(EXIT_FAILURE);
    }
    return sqrt(r2);
}

float Analytic_CircumferenceXCentreFunction(Analytic_Circumference circumference)
{
    return -(circumference.a / 2);
}

float Analytic_CircumferenceYCentreFunction(Analytic_Circumference circumference)
{
    return circumference.b / 2;
}

float Analytic_HyperboleYFunction(Analytic_Hyperbole hyperbole, float x)
{
    if (hyperbole.a <= 0 || hyperbole.b <= 0)
    {
        log_fatal("This is not a hyperbole! (domain error or division by zero)");
        exit(EXIT_FAILURE);
    }
    return -sqrt(-((hyperbole.a * hyperbole.b) - (hyperbole.b * x * x)) / hyperbole.a);
}

float Analytic_HyperboleXFunction(Analytic_Hyperbole hyperbole, float x)
{
    if (hyperbole.a <= 0 || hyperbole.b <= 0)
    {
        printf("\n");
        log_fatal("This is not a hyperbole! (domain error or division by zero)");
        exit(EXIT_FAILURE);
    }
    return -sqrt(((hyperbole.a * hyperbole.b) + (hyperbole.b * x * x)) / hyperbole.a);
}
float Analytic_HyperboleKFunction(Analytic_Hyperbole hyperbole, float x)
{
    return hyperbole.k / -x;
}

float Analytic_HyperboleHomographicFunction(Analytic_Hyperbole hyperbole, float x)
{
    if (hyperbole.c == 0 || hyperbole.a * hyperbole.d == hyperbole.c * hyperbole.b)
    {
        printf("\n");
        log_fatal("This is not a hyperbole! c = 0 or ad = cb");
        exit(EXIT_FAILURE);
    }
    return (hyperbole.a * x + hyperbole.b) / (hyperbole.c * x + hyperbole.d);
}