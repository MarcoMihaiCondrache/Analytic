/**
 * @file input.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Header file for ui input functions
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#ifndef UI_INPUT_H
#define UI_INPUT_H

/**
 * @brief Function to read an user input
 * 
 * This function use the standard IO library to create
 * something more modern and sample. It prints a text that can be for example
 * what the user have to enter. After this there is the TRAILING, the string printed
 * on the same line of the scanf.
 * 
 * @param LEANDING Text to print before the input request
 * @param FORMAT The format of the input to read
 * @param ... Parameters to use in the format string
 * 
 * @return int The operation result
 * 
 * @see TRAILING
 */
extern int Ui_readInput(const char *LEANDING, const char *FORMAT, ...);

#endif