#ifndef WORD_H
#define WORD_H

#include "toolbox.h"

typedef struct
{
    unsigned long origin_id;
    unsigned int num_occurences;
} Word_occurence_s;

typedef struct
{
    char* word_name;
    unsigned int tab_cursor;
    Word_occurence_s* t_occurences;
} Word_s;


/*TODO METHODS */
void init_word(char *word_name, Word_s** output);
Bool_e add_occurence(Word_s** word_s, Word_occurence_s word_occurence_s);
Bool_e word_to_string(Word_s word, char** output);


#endif