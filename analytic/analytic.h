/**
 * @file analytic.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Header file for setting library variables
 * @version 1.0
 * @date 25-03-2020
 * 
 * This API supports the following features:
 *      * setting divisor
 *      * setting scale
 *      * setting window size
 *      * setting terminal output
 *      * init the data set
 *      * set the data set
 *
 * These functions must be called from the main thread.
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#ifndef ANALYTIC_MAIN_H
#define ANALYTIC_MAIN_H

/**
 * @brief Set the divisor variable
 * 
 * Usually is used to set the divisor to the default value
 * 
 * @param _DIVISOR
 * 
 * @see DEFAULT_DIVISOR
 */
extern void Analytic_setDivisor(float _DIVISOR);

/**
 * @brief Set the scale variable
 * 
 * Usually is used to set the scale to the default value
 * 
 * @param _SCALE 
 * 
 * @see DEFAULT_SCALE
 */
extern void Analytic_setScale(float _SCALE);

/**
 * @brief Set the Windows Size variable
 * 
 * This function sets the variable SDL_WINDOW_SIZE to a variable
 * 
 * @param _SDL_WINDOW_SIZE 
 * 
 * @see SDL_WINDOW_SIZE 
 */
extern void Analytic_setWindowSize(int _SDL_WINDOW_SIZE);

/**
 * @brief Set the TERMINAL_OUTPUT variable
 * 
 * This function sets the variable TERMINAL_OUTPUT to a bool value
 * 
 * @param _TERMINAL_OUTPUT 
 * 
 * @see TERMINAL_OUTPUT
 */
extern void Analytic_setTerminalOutput(bool _TERMINAL_OUTPUT);

/**
 * @brief set a value from the data set
 * 
 * This function sets the data given from the INDEX to a bool value
 * 
 * @param INDEX 
 * @param VALUE 
 * 
 * @see SINGLE
 */
extern void Analytic_setDataSet(int INDEX, bool VALUE);

/**
 * @brief Function to init the data set
 * 
 * This function will set all the data from the set to
 * false
 * 
 * @see SINGLE
 */
extern void Analytic_initDataSet();

#endif