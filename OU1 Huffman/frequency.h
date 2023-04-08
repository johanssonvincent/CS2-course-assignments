/**
 * @defgroup frequency Frequency
 *
 * @brief Builds a frequency table from a text file.
 *
 * Takes a given text file and creates a frequency table using an array.
 * The index of the array specifies which character it's adding frequency to.
 *
 * @author: Vincent Johansson <dv14vjn>
 * @since:  2019-04-15
 *
 * @{
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * @brief Fills out the frequency table in given array.
 *
 * @param freqArr[] Array where frequency of symbols is counted.
 * @param file Text file used for the frequency table.
 */
void getFrequency(int freqArr[], FILE* file);


/* ---- External function used for debugging - Not part of API ---- */


/**
 * @brief Prints out the values of the frequency table.
 *
 * Prints out the values of the frequency table.
 * Used for debugging.
 *
 * @param freqArr[] Array where frequency of symbols is counted.
 */
void printFrequency(int freqArr[]);
