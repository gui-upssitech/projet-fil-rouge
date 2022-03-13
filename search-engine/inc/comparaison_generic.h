/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
                      
Date:       29/11/2021
*/

#ifndef COMPARAISON_GENERIC_H
#define COMPARAISON_GENERIC_H

#include "toolbox.h"
#include "indexation_generic.h"

/**
 * @brief A structure to save generic data results.
 * 
 */
typedef struct
{
    char name[MAX_MEMORY_STRING]; /**< the name of found file. */
    double confidence; /**< The confidence of the comparison between the found file and the search file by user. */
    int time_code; /**< The time code in seconds in the case of audio data. */
} Result_s;

/**
 * @brief Compare two histograms with a percentage between 0.0 % and 100.0 %.
 * 
 * @param size The size of histograms.
 * @param histogram1 A pointer to the first histogram array.
 * @param histogram2 A pointer to the second histogram array.
 * @param confidence The confidence of the comparison between 0.0 % and 100.0 %.
 */
void compare_histogram(unsigned int size, unsigned int* histogram1, unsigned int* histogram2, double* confidence);

#endif