/**
 * @file plane.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Header file for functions to manage the plane
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#ifndef PLANE_H
#define PLANE_H

/**
 * @brief Function to draw the Axes on the plane
 * 
 * The function draw point by point on defined \n
 * coordinates. Every DIVISOR pixels the function draw e red line \n
 * that is used to classify the unit
 * 
 * @param color The color of the axes
 * @param renderer Renderer to which to draw the axes
 */
extern void Analytic_setAxes(SDL_Color color, SDL_Renderer *renderer);

/**
 * @brief Function to set the background of the plane
 * 
 * The function clears the background and re-renderer the plane
 * 
 * @param color The color or the background
 * @param renderer Renderer to which to apply the background
 */
extern void Analytic_setBackground(SDL_Color color, SDL_Renderer *renderer);

/**
 * @brief Function to init the plane
 * 
 * The function sets the default values for the plane;
 * 
 * @param renderer Renderer to which to init the plane
 */
extern void Analytic_initPlane(SDL_Renderer *renderer);

/**
 * @brief Function to render the places
 * 
 * This function checks the data set and draws the places.
 * 
 * @param renderer Renderer to which to render
 */
extern void Analytic_renderMethod(SDL_Renderer *renderer);

#endif