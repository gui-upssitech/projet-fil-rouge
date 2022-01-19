/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN


Date:       29/11/2021
*/

#ifndef COMPARAISON_TEXT_H
#define COMPARAISON_TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "indexation_text.h"
#include "toolbox.h"

typedef struct comparaison_text
{
    /* data */
};

/* METHODS */

Bool_e display_research_by_keyword(char* word);
Bool_e find_filename_from_id(unsigned long id, char** filename);


#endif 