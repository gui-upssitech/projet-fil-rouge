/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "comparaison_generic.h"

Bool_e compare_histogram(unsigned int size, unsigned int* histogram1, unsigned int* histogram2, double* confidence)
{
    /* statements */
    int sum, max1, max2;
    unsigned int i;

    /* initializations */
    sum = 0;
    max1 = 0;
    max2 = 0;

    /* instructions */
    for(i = 0; i < size; i++)
    {
        sum = sum + abs_int((int) histogram1[i] - (int) histogram2[i]);
        max1 += histogram1[i];
        max2 += histogram2[i];
    }
    
    if(max1 != max2)
    {
        fprintf(stderr, "Error comparing histograms (not same size).\n\r");
        return FALSE;
    }
    *confidence = (double) (sum * -100) / (double) (max1 + max2) + 100.0f;
    
    return TRUE;
}