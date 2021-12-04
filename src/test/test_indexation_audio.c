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
#include <string.h>

int main(void)
{
    /* statements */
    FILE* p_bin_file;
    char bytes[8];

    /* initializations */
    p_bin_file = fopen("/home/rxc3445a/Documents/projet-fil-rouge/data/audios/TEST_SON/corpus_fi.bin", "rb");

    /* instructions */
    while (!feof(p_bin_file))
    {
        fread(bytes, 8, 1, p_bin_file);
        printf("%.8e\n", *((double*) bytes));
    }

    fclose(p_bin_file);

    return EXIT_SUCCESS;
}