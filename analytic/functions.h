/**
 * @file functions.h
 * @author Marco Mihai Condrache (marcomihaicondrache@gmail.com)
 * @brief Header file for the math functions used by the library
 * @version 1.0
 * @date 25-03-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 * https://github.com/MarcoMihaiCondrache
 */

#ifndef ANALYTIC_FUNCTIONS_H
#define ANALYTIC_FUNCTIONS_H

/**
 * @brief Mathematical function to get y
 * 
 * The function calculates the y with a mathematic formula
 * 
 * \f$y = mx + q\f$
 * 
 * @param line Contains the line parameters
 * @param x Unknown to calculate the y
 * @return int The calculated y
 */
extern int
Analytic_LineFunction(Analytic_Line line, float x);

/**
 * @brief Mathematical function to get y of parables with vertical symmetry axis
 * 
 * The function calculates the y with a mathematic formula
 * 
 * \f$y = ax^2 + bx + c\f$
 * 
 * All the parameters are transformed into their opposites because the sdl plane is inverse\n
 * so the used formula is
 * 
 * \f$y = - ax^2 - bx - c\f$
 * 
 * @param parabola Contains the parabola parameters
 * @param x Unknown to calculate the y
 * @return float The calculated y
 * 
 * @see Analytic_Parabola
 * @see Analytic_ParabolaType
 */
extern float Analytic_ParabolaYFunction(Analytic_Parabola parabola, float x);

/**
 * @brief Mathematical function to get x of parables with horizontal symmetry axis
 * 
 * The function calculates the x with a mathematic formula
 * 
 * \f$x = ay^2 + by + c\f$
 * 
 * But the sdl plane is inverse so the used formula is
 * 
 * \f$x = - (ay^2 + by - c)\f$
 * 
 * @param parabola Contains the parabola parameters
 * @param y Unknown to calculate the x
 * @return float The calculated x
 * 
 * @see Analytic_Parabola
 * @see Analytic_ParabolaType
 */
extern float Analytic_ParabolaXFunction(Analytic_Parabola parabola, float y);

/**
 * @brief Mathematical function to calculate the radius of a circumference
 * 
 * The function calculates the radius with a mathematic formula
 * 
 * \f$r = \sqrt{\frac{a^{2}}{4} + \frac{b^{2}}{4} - c}\f$
 * 
 * @warning The function also checks for a negative radius. \n
 * In this case the program will exit returning a fatal error. \n
 * Before calling this function, check that the \n
 * given circumference is really a circumference!
 * 
 * @param circumference Contains the circumference parameters
 * @return float The calculated radius
 * 
 * @see Analytic_Circumference
 */
extern float Analytic_CircumferenceRadiusFunction(Analytic_Circumference circumference);

/**
 * @brief Mathematical function to calculate the x of the centre of a circumference
 * 
 * The function calculates the x with a mathematic formula
 * 
 * \f$x = -\frac{a}{2}\f$
 * 
 * @param circumference Contains the circumference parameters
 * @return float The calculated x
 * 
 * @see Analytic_Circumference
 */
extern float Analytic_CircumferenceXCentreFunction(Analytic_Circumference circumference);

/**
 * @brief Mathematical function to calculate the y of the centre of a circumference
 * 
 * The function calculates the y with a mathematic formula
 * 
 * \f$y = -\frac{b}{2}\f$
 * 
 * The result is transformed into its opposite because the SDL plan is inverse so
 * 
 * \f$y = \frac{b}{2}\f$
 * 
 * @param circumference Contains the circumference parameters
 * @return float The calculated y
 * 
 * @see Analytic_Circumference
 */
extern float Analytic_CircumferenceYCentreFunction(Analytic_Circumference circumference);

/**
 * @brief Mathematical function to get y of hyperboles with vertical symmetry axis
 * 
 * The function calculates the y with a mathematic formula
 * 
 * \f$y = \pm \sqrt{-b^{2} + \frac{a^{2}}{b^{2}}x^{2}}\f$
 * 
 * The function calculates the second y and the first \n
 * is drawn by exploiting the symmetry property of the \n
 * hyperbole for more precise coordinates\n
 * 
 * \f$y = - \sqrt{-b^{2} + \frac{a^{2}}{b^{2}}x^{2}}\f$
 * 
 * @warning The function also checks that the hyperbole parameters \n
 * are larger and different from zero in order to avoid errors \n
 * during mathematical calculations. If this were the case, \n
 * the function would block the program and return a fatal error
 * 
 * @param hyperbole Contains the hyperbole parameters
 * @param x Unknown to calculate the y
 * @return float The calculated y
 * 
 * @see Analytic_Hyperbole
 * @see Analytic_Analytic_HyperboleType
 */
extern float Analytic_HyperboleYFunction(Analytic_Hyperbole hyperbole, float x);

/**
 * @brief Mathematical function to get y of hyperboles with horizontal symmetry axis
 * 
 * The function calculates the y with a mathematic formula
 * 
 * \f$y = \pm \sqrt{b^{2} + \frac{a^{2}}{b^{2}}x^{2}}\f$
 *
 * The function calculates the second y and the first 
 * is drawn by exploiting the symmetry property of the 
 * hyperbole for more precise coordinates
 *
 * \f$y = - \sqrt{b^{2} + \frac{a^{2}}{b^{2}}x^{2}}\f$
 * 
 * @warning The function also checks that the hyperbole parameters \n
 * are larger and different from zero in order to avoid errors \n
 * during mathematical calculations. If this were the case, \n
 * the function would block the program and return a fatal error
 * 
 * @param hyperbole Contains the hyperbole parameters
 * @param x Unknown to calculate the y
 * @return float The calculated y
 * 
 * @see Analytic_Hyperbole
 * @see Analytic_HyperboleType
 */
extern float Analytic_HyperboleXFunction(Analytic_Hyperbole hyperbole, float x);

/**
 * @brief Mathematical function to get y of equilateral hyperbolas
 * 
 * The function calculates the y with a mathematic formula
 * 
 * \f$xy = k\f$
 * 
 * So to extract the y we use
 * 
 * \f$y = \frac{k}{x}\f$
 * 
 * @warning When x=0 the formula returns NaN;
 * 
 * @param hyperbole Contains the hyperbole parameters
 * @param x Unknown to calculate the y
 * @return float The calculated y
 */
extern float Analytic_HyperboleKFunction(Analytic_Hyperbole hyperbole, float x);

/**
 * @brief Mathematical function to draw hyperbolas
 * 
 * The function calculates the y with a mathematic formula
 * 
 * \f$y = \frac{ax + b}{cx + d}\f$
 * 
 * @warning The function also checks that c is different from 0 and that there is no proportion between the parameters (ad = db).
 * In the case it stops the program and returns a fatal error. So first please check the hyperbola parameters
 * 
 * @param hyperbole Contains the hyperbole parameters
 * @param x Unknown to calculate the y
 * @return float The calculated y
 */
extern float Analytic_HyperboleHomographicFunction(Analytic_Hyperbole hyperbole, float x);

#endif