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
 * @brief 
 * 
 */
typedef struct
{
    unsigned long origin_id;
    unsigned int num_occurences;
} Word_occurence_s;

/**
 * @brief 
 * 
 */
typedef struct
{
    char* word_name;
    unsigned int tab_cursor;
    Word_occurence_s* t_occurences;
} Word_s;

/**
 * @brief 
 * 
 * @param word_name 
 * @param output 
 */
void init_word(char *word_name, Word_s** output);

/**
 * @brief 
 * 
 * @param word_s 
 * @param word_occurence_s 
 * @return Bool_e 
 */
Bool_e add_occurence(Word_s** word_s, Word_occurence_s word_occurence_s);

/**
 * @brief 
 * 
 * @param word 
 * @param output 
 * @return Bool_e 
 */
Bool_e word_to_string(Word_s word, char** output);


#endif