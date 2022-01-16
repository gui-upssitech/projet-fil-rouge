#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "word.h"
#include "configurations.h"

void init_word(char *word_name, Word_s** output)
{
    *output = (Word_s*) malloc(sizeof(Word_s));

    if(*output == NULL)
    {
        fprintf(stderr, "Error %d: Failed to allocate memory to init word\n\r", errno);
        return;
    }

    (*output)->word_name = (char *)malloc(strlen(word_name) * sizeof(char));
    strcpy((*output)->word_name, word_name);

    (*output)->t_occurences = (Word_occurence_s *)malloc(
        G_parameters.text_indexing_parameters.indexing_text_number_table_index * sizeof(Word_occurence_s));
}

Bool_e add_occurence(Word_s *word_s, Word_occurence_s word_occurence_s)
{

    /* ADD OCCURENCE TO THE RIGHT PLACE IF OCCURENC TO LITTLE THEN DONT ADD */
    // TODO 
    return TRUE;    
}

Bool_e word_to_string(Word_s word, char* output) {
    // TODO
}