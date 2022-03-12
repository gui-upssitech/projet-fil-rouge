/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN            
            
Date:       29/11/2021
*/

#ifndef WORD_H
#define WORD_H

#include "toolbox.h"

/**
 * @brief A struct which links a text file id with his number of occurrencies.
 * 
 */
typedef struct
{
    unsigned long origin_id; /**< The text file id. */
    unsigned int num_occurences; /**< The number of occurrencies */
} Word_occurence_s;

/**
 * @brief A struct to represent a word.
 * 
 */
typedef struct
{
    char* word_name; /**< The word name. */
    unsigned int tab_cursor; /**< The cursor position in the t_occurences array. */
    Word_occurence_s* t_occurences; /**< A Wordçoccurences_s pointer which represents an array of Word_occurence_s. */
} Word_s;

/**
 * @brief Init the word.
 * 
 * @param word_name The word name.
 * @param output The adress of the initialized word.
 */
void init_word(char *word_name, Word_s** output);

/**
 * @brief Add an occurrence to the word.
 * 
 * @param word_s The word in which add the occurrence.
 * @param word_occurence_s The occurrence to add.
 * @return Bool_e TRUE if succeed, FALSE else.
 */
Bool_e add_occurence(Word_s** word_s, Word_occurence_s word_occurence_s);

/**
 * @brief Convert a word to string.
 * 
 * @param word The word to convert.
 * @param output The string result conversion.
 * @return Bool_e TRUE if succeed, FALSE else.
 */
Bool_e word_to_string(Word_s word, char** output);


#endif