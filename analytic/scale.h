/**
 * @file scale.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Header file of functions to scale/zoom
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#ifndef ANALYTIC_SCALE_H
#define ANALYTIC_SCALE_H

/**
 * @brief Convert an x relative into an x absolute
 * 
 * This function calculates absolute x by adding
 * the x relative to half of SDL_WINDOW SIZE
 * 
 * \f$SDL\_WINDOW\_SIZE : 2 + XRelative\f$
 * 
 * @param x The relative x to convert
 * @return int Returns the absolute x based on SDL_WINDOW_SIZE
 * 
 * @see SDL_WINDOW_SIZE
 */
extern int Analytic_convertXAbsolute(float x);

/**
 * @brief Convert an y relative into an y absolute
 * 
 * This function calculates absolute y by adding
 * the y relative to half of SDL_WINDOW SIZE
 * 
 * \f$SDL\_WINDOW\_SIZE : 2 + YRelative\f$
 * 
 * @param y The relative x to convert
 * @return int Returns the absolute y based on SDL_WINDOW_SIZE
 * 
 * @see SDL_WINDOW_SIZE
 */
extern int Analytic_convertYAbsolute(float y);

/**
 * @brief Calculate the divisor thanks to the scale
 * 
 * This function calculates the divisor by multiplying
 * the default divisor by the scale difference and by 100
 * 
 * \f$Divisor = DefaultDivisor * ScaleDifference * 100\f$
 * 
 * @return int Returns the calculated divisor based on scale
 * 
 * @see SCALE
 * @see DEFAULT_SCALE
 */
extern int Analytic_calculateDivisor();

/**
 * @brief Scale In the view
 * 
 * The function increases the scale and renders the plane again
 * 
 * @param renderer Renderer to which to apply the scale
 * 
 * @see SCALE
 * @see DEFAULT_SCALE
 */
extern void Analytic_scaleIn(SDL_Renderer *renderer);

/**
 * @brief Scale Out the view
 * 
 * The function decreases the scale and renders the plane again
 * 
 * @param renderer Renderer to which to apply the scale
 * 
 * @see SCALE
 * @see DEFAULT_SCALE
 */
extern void Analytic_scaleOut(SDL_Renderer *renderer);

/**
 * @brief Function to check if a relative x is correct
 * 
 * The function checks the bound of the plane
 * 
 * @param x The x to check
 * @return true Returns true if the x is ok
 * @return false Returns false if the x isn't ok
 */
extern bool Analytic_isXRelativeOK(float x);

/**
 * @brief Function to check if a relative y is correct
 * 
 * The function checks the bound of the plane
 * 
 * @param y The y to check
 * @return true Returns true if the y is ok
 * @return false Returns false if the y isn't ok
 */
extern bool Analytic_isYRelativeOK(float y);

#endif