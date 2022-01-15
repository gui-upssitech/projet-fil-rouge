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

typedef struct
{
    char name[MAX_MEMORY_STRING];
    double confidence;
    int time_code;
} Result_s;

void compare_histogram(unsigned int size, unsigned int* histogram1, unsigned int* histogram2, double* confidence);

#endif