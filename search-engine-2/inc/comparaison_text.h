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
#include "project.h"

/**
 * @brief A struct which associates a score to a text id.
 * 
 */
typedef struct
{
    unsigned long id; /**< the text id. */
    float score; /**< The score of the text. */
} Score_text_s;

/**
 * @brief A struct to represent a keyword in an indexing text. 
 * 
 */
typedef struct
{
    char* word; /**< The word name. */
    unsigned int occurences; /**< The number of occurencies of the word in the text */
    float word_weight; /**< The weight of the word in the text. */
} Keyword_s;


/**
 * @brief A struct to represents all keywords of a text.
 * 
 */
typedef struct
{    
    unsigned int size_scores; /**< The number of texts with a score. */
    unsigned int size; /**< The number of keywords. */
    Keyword_s* keywords; /**< A Keyword_s pointer which represents an array of keywords. */
    Score_text_s* score_texts; /**< A Score_text_s pointer which represents an array of text scores. */
} Keywords_s;

/**
 * @brief Init the keywords array.
 * 
 * @param keywords A pointer which represents the keywords array.
 */
void init_keywords(Keywords_s* keywords);

/**
 * @brief Display the research by keyword result menu.
 * 
 * @param word The word to search.
 * @return Bool_e TRUE if succeed, FALSE else.
 */
Bool_e display_research_by_keyword(char *word);

/**
 * @brief Find a filename with his id.
 * 
 * @param id The id of the file.
 * @param filename The found filename string.
 * @return Bool_e TRUE if succeed, FALSE else.
 */
Bool_e find_filename_from_id(unsigned long id, char **filename);

/**
 * @brief Display the research by text menu result.
 * 
 * @param path The path of the file to search.
 * @return Bool_e TRUE if succeed, FALSE else.
 */
Bool_e display_research_by_text(char *path);


#endif