/**
 * @file global.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief UI global file contains global definitions
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

/**
 * @brief Defines the indicator to be printed before a scanf
 * 
 */
#define TRAILING "~ >>> "

/**
 * @brief Defines the command to use to clear the console (The preprocessor result depends on the operating system)
 * 
 */
#if defined(_WIN32) || defined(_WIN64)
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif