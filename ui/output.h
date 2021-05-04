/**
 * @file output.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Header file for ui output functions
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#ifndef UI_OUTPUT_H
#define UI_OUTPUT_H

/**
 * @brief Function to display a warning dialog
 * 
 * This function uses the SDL library to display a simple
 * warning dialog with a "OK" button and a custom message.
 * 
 * @param msg The message for the user
 */
extern void Ui_showWarningDialog(const char *msg);

/**
 * @brief Function to print a message and adding a new line
 * 
 * This function use the standard IO library print a message
 * and to add a new line after it.
 * 
 * @param msg The format of the message
 * @param ... The arguments to apply to the format
 */
extern void Ui_printWithNewLine(const char *msg, ...);

/**
 * @brief Function to clear the console
 * 
 * This function uses the clear command defined in the global file
 * and with a system call clears the console
 * 
 */
extern void Ui_clear();

/**
 * @brief Function to handle a menu
 * 
 * This function shows the available options on the screen and \n
 * through a call Ui_readInput puts the selection on hold. If \n
 * the selected element does not exist, the function re-proposes \n
 * the menu and this is where the clear parameter acts. If true, \n
 * the function deletes the old text of the console and re-proposes \n
 * it following the wrong selection \n
 * 
 * @param leadingMsg Text to print before the menu
 * @param selectionMsg Text to print before the input request (after the menu)
 * @param items Items of the menu
 * @param itemsCount The number of the items
 * @param clear Bool that defines if the menu has to clear every time the console
 * @return int The selected item
 * 
 * @see CLEAR
 * @see Ui_readInput
 */
extern int
Ui_handleMenu(const char *leadingMsg, const char *selectionMsg, const char *items[], int itemsCount, bool clear);

#endif