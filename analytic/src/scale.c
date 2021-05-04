#include "../../log/log.h"
#include "../global.h"
#include "../scale.h"
#include "../plane.h"

int Analytic_convertXAbsolute(float XRelative) {
    return (((SDL_WINDOW_SIZE / 2) + XRelative));
}

int Analytic_convertYAbsolute(float YRelative) {
    return (((SDL_WINDOW_SIZE / 2) + YRelative));
}

bool Analytic_isXRelativeOK(float x) {
    if (Analytic_convertXAbsolute(x) >= 0 && Analytic_convertXAbsolute(x) <= SDL_WINDOW_SIZE)
        return true;
    return false;
}

bool Analytic_isYRelativeOK(float y) {
    if (Analytic_convertYAbsolute(y) >= 0 && Analytic_convertYAbsolute(y) <= SDL_WINDOW_SIZE)
        return true;
    return false;
}

void Analytic_scaleIn(SDL_Renderer *renderer) {
    SCALE += 0.01;
    SDL_RenderSetScale(renderer, SCALE, SCALE);
    Analytic_initPlane(renderer);
    Analytic_renderMethod(renderer);
    if (TERMINAL_OUTPUT) {
        log_debug("Scale Factor: %.1f +", SCALE);
    }
}

void Analytic_scaleOut(SDL_Renderer *renderer) {
    if (SCALE > DEFAULT_SCALE) {
        SCALE -= 0.01;
        SDL_RenderSetScale(renderer, SCALE, SCALE);
        Analytic_initPlane(renderer);
        Analytic_renderMethod(renderer);
        if (TERMINAL_OUTPUT) {
            log_debug("Scale Factor: %.1f -", SCALE);
        }
    }
}

int Analytic_calculateDivisor() {
    if (SCALE != DEFAULT_SCALE)
        return round(DEFAULT_DIVISOR * round((SCALE - DEFAULT_SCALE) * 100));
    else
        return DEFAULT_DIVISOR;
}