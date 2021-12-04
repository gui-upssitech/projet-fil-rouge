/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* statements */
    FILE* p_bin_file;
    double data;

    /* initializations */
    p_bin_file = fopen("/home/rxc3445a/Documents/projet-fil-rouge/data/audios/TEST_SON/corpus_fi.bin", "r");

    /* instructions */
    while(!feof(p_bin_file))
    {
        fscanf(p_bin_file, "%lf", &data);
        printf("%lf ", data);
    }

    return EXIT_SUCCESS;
}