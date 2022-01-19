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

#include "console.h"
#include "indexation_text.h"
#include "toolbox.h"

typedef struct
{
    unsigned long id;
    float score;
} Score_text_s;

typedef struct
{
    char* word;
    unsigned int occurences;
    float word_weight;
} Keyword_s;

typedef struct
{    
    unsigned int size_scores;
    unsigned int size;
    Keyword_s* keywords;
    Score_text_s* score_texts;
} Keywords_s;

/* METHODS */

void init_keywords(Keywords_s* keywords);
Bool_e display_research_by_keyword(char *word);
Bool_e find_filename_from_id(unsigned long id, char **filename);
Bool_e display_research_by_text(char *path);


#endif