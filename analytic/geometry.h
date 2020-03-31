/**
 * @file geometry.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Header file to include functions to draw places
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#ifndef ANALYTIC_GEOMETRY_H
#define ANALYTIC_GEOMETRY_H

/**
 * @brief Function to draw a point
 * 
 * The function converts the relative position into an absolute and
 * draws the point
 * 
 * @param position Relative position of the point
 * @param color Color of the point
 * @param renderer Renderer to which to draw the point
 */
extern void Analytic_createPoint(Analytic_Position position, SDL_Color color, SDL_Renderer *renderer);

/**
 * @brief Function to draw a straight line
 * 
 * This function identifies the type of line based \n
 * on the parameters provided and then draws the line point by point
 * 
 * @param line Contains the line parameters
 * @param renderer Renderer to which to draw the line
 */
extern void Analytic_createLine(Analytic_Line line, SDL_Renderer *renderer);

/**
 * @brief Function to create a Circumference
 * 
 * The function calculates the radius and the coordinates \n
 * of the center and then goes to draw the circumference \n
 * using the algorithm of the intermediate point that allows \n
 * to obtain good performances and also good precision \n
 * 
 * @param circumference Contains the circumference parameters
 * @param renderer Renderer to which to draw the line
 */
extern void Analytic_createCircumference(Analytic_Circumference circumference, SDL_Renderer *renderer);

/**
 * @brief Function to draw an hyperbole
 * 
 * The function identifies the type of hyperbole and then \n
 * proceeds to the drawing, they draw a line between each \n
 * point calculated in order to obtain excellent precision \n
 * without wasting resources. \n
 * 
 * @param hyperbole Contains the hyperbole parameters
 * @param renderer Renderer to which to draw the line
 */
extern void Analytic_createHyperbole(Analytic_Hyperbole hyperbole, SDL_Renderer *renderer);

/**
 * @brief Function to draw a parabola
 * 
 * The function determines the position \n
 * of the parabola and renders point by point. \n
 * Finally, draw a line between each point to give a sense of continuity \n
 * 
 * @param parabola Contains the parabola parameters
 * @param renderer Renderer to which to draw the line
 */
extern void Analytic_createParabola(Analytic_Parabola parabola, SDL_Renderer *renderer);

/**
 * @brief Function to find tangents to a circumference
 * 
 * @param point Starting point for straight lines
 * @param circumference Contains the circumference parameters
 * @param renderer Renderer to which to draw the line
 */
extern void Analytic_createTangents(Analytic_Position point, Analytic_Circumference circumference, SDL_Renderer *renderer);

#endif