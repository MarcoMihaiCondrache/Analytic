/**
 * @file global.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Header file that defines global variables and macros
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#ifndef ANALYTIC_GLOBAL_H
#define ANALYTIC_GLOBAL_H

#include <SDL.h>
#include <stdbool.h>

/**
 * @brief Default value from which to start scaling
 * 
 */
#define DEFAULT_SCALE 1.0
/**
 * @brief Default value from which to start the calculation of the divisor
 * 
 */
#define DEFAULT_DIVISOR 10

/**
 * @brief White color (FFFFFF with alpha FF)
 * 
 */
static const SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};

/**
 * @brief Black color (000000 with alpha FF)
 * 
 */
static const SDL_Color black = {0x00, 0x00, 0x00, 0xFF};

/**
 * @brief Red color (FF0000 with alpha FF)
 * 
 */
static const SDL_Color red = {0xFF, 0x00, 0x00, 0xFF};

/**
 * @brief Green color (00FF00 with alpha FF)
 * 
 */
static const SDL_Color green = {0x00, 0xFF, 0x00, 0xFF};

/**
 * @brief Blue color (0000FF with alpha FF)
 * 
 */
static const SDL_Color blue = {0x00, 0x00, 0xFF, 0xFF};

/**
 * @brief Purple (variant) color (9D70FF with alpha FF)
 * 
 */
static const SDL_Color purple = {0x9D, 0x70, 0xFF, 0xFF};

/**
 * @brief Grey (variant) color (DBDBDB with alpha 64)
 * 
 */
static const SDL_Color grey = {0xDB, 0xDB, 0xDB, 0x64};

/**
 * @brief Yellow (variant) color (F5F242 with alpha FF)
 * 
 */
static const SDL_Color yellow = {0xF5, 0xF2, 0x42, 0xFF};

/**
 * @brief Enum for the indexes of the data set
 * 
 * @see SINGLE
 */
typedef enum {
    ANALYTIC_POSITION_DATASET,
    ANALYTIC_LINE_DATASET,
    ANALYTIC_CIRCUMFERENCE_DATASET,
    ANALYTIC_PARABOLA_DATASET,
    ANALYTIC_HYPERBOLE_DATASET
} ANALYTIC_DATASET;

/** 
 *  @brief Enum for the parables types
 * 
 *  @see Analytic_Parabola
 */
typedef enum {
    Analytic_ParabolaX,
    Analytic_ParabolaY
} Analytic_ParabolaType;

/** 
 *  @brief Enum for the hyperbole types
 * 
 *  @see Analytic_Hyperbole
 */
typedef enum {
    Analytic_HyperboleX,
    Analytic_HyperboleY,
    Analytic_HyperboleK,
    Analytic_HyperboleHomographic
} Analytic_HyperboleType;

/** 
 *  @brief Enum for the position types
 * 
 *  @see Analytic_Position
 */
typedef enum {
    Analytic_PositionRelative,
    Analytic_PositionAbsolute
} Analytic_PositionType;

/**
 * @brief Straight Line Structure (\f$y = mx + q\f$)
 * 
 */
typedef struct Analytic_Line {
    float m; /**< Straight line coefficient */
    float q; /**< Known term of the line */
} Analytic_Line;

/**
 * @brief Circumference structure (\f$x^2 + y^2 + ax + by + c = 0\f$)
 * 
 */
typedef struct Analytic_Circumference {
    float a; /**< First Coefficient of the equation */
    float b; /**< Second Coefficient of the equation */
    float c; /**< Third Coefficient of the equation */
} Analytic_Circumference;

/**
 * @brief Hyperbole structure
 * 
 * Hyperbole types supported:
 * 
 * * \f$\frac{x^2}{a^2} - \frac{y^2}{b^2} = 1\f$
 * 
 * * \f$\frac{x^2}{a^2} - \frac{y^2}{b^2} = -1\f$
 * 
 * * \f$xy = k\f$
 * 
 * * \f$y = \frac{ax + b}{cx + d}\f$
 * 
 */
typedef struct Analytic_Hyperbole {
    Analytic_HyperboleType type; /**< Type of the hyperbole */
    float a;                     /**< Coefficient of the base equation / homographic function */
    float b;                     /**< Coefficient of the base equation / homographic function */
    float k;                     /**< Coefficient of the equation xy = k */
    float c;                     /**< Coefficient of the homographic function */
    float d;                     /**< Coefficient of the homographic function */
} Analytic_Hyperbole;

/**
 * @brief Parabola structure \f$y = ax^2 + bx + c\f$ or \f$x = ay^2 + by + c\f$
 * 
 */
typedef struct Analytic_Parabola {
    Analytic_ParabolaType type; /**< Type of the parabola */
    float a;                    /**< First Coefficient of the equation */
    float b;                    /**< Second Coefficient of the equation */
    float c;                    /**< Third Coefficient of the equation */
} Analytic_Parabola;

/**
 * @brief Position structure (Contains the coordinates of a point)
 * 
 */
typedef struct Analytic_Position {
    float x; /**< X coordinate */
    float y; /**< Y coordinate */
} Analytic_Position;

/**
 * @brief Structure that defines the data set to render
 * 
 * This structure contains an array of bool values, everyone indicates
 * if a place contains the data to render if not it will not be rendered.
 * 
 */
typedef struct Analytic_Single {
    bool dataSet[4];                      /**< Array that contains the status of the places */
    Analytic_Position position;           /**< Position of the data set (for the tangents) */
    Analytic_Line line;                   /**< Line of the data set (tangets and simple) */
    Analytic_Circumference circumference; /**< Circumference of the data set (tangent and simple) */
    Analytic_Parabola parabola;           /**< Parabola of the data set */
    Analytic_Hyperbole hyperbole;         /**< Hyperbole of the data set */
} Analytic_Single;

/**
 * @brief Variables that contains the scale value
 * 
 */
float SCALE;

/**
 * @brief Variables that contains the divisor value
 * 
 */
int DIVISOR;

/**
 * @brief Defines the Window Size
 * 
 */
int SDL_WINDOW_SIZE;

/**
 * @brief If the program has to show the logs on the screen
 * 
 */
bool TERMINAL_OUTPUT;

/**
 * @brief The data set of the program
 * 
 */
Analytic_Single SINGLE;

#endif