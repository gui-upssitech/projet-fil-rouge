#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "word.h"
#include "configurations.h"

void init_word(char *word_name, Word_s **output)
{
    *output = (Word_s*) malloc(sizeof(Word_s));

    /* Checking if malloc works*/
    if (*output == NULL)
    {
        fprintf(stderr, "Error %d: Failed to allocate memory to init word\n\r", errno);
        return;
    }

    /* Init world name */
    (*output)->word_name = (char*) malloc((strlen(word_name) + 2) * sizeof(char));
    if((*output)->word_name == NULL)
    {
        fprintf(stderr, "Error %d: Failed to allocate memory to init char array of word.\n\r", errno);
        return;
    }

    strcpy((*output)->word_name, word_name);

    /* Init size of occurence */
    (*output)->tab_cursor = 0;

    (*output)->t_occurences = (Word_occurence_s*) malloc(G_parameters.text_indexing_parameters.indexing_text_number_table_index * sizeof(Word_occurence_s));
    if((*output)->t_occurences == NULL)
    {
        fprintf(stderr, "Error %d: Failed to allocate memory to init occurences array of word.\n\r", errno);
        return;
    }
}

Bool_e add_occurence(Word_s **word, Word_occurence_s occurence)
{
    /* Variables */
    unsigned int i, cursor, max_size;

    /* Init variable */
    cursor = (*word)->tab_cursor;
    max_size = G_parameters.text_indexing_parameters.indexing_text_number_table_index;

    /* Checking the occurence tab is not full to simple add */
    if (cursor != max_size)
    {
        if (cursor == 0 || occurence.num_occurences <= (*word)->t_occurences[cursor - 1].num_occurences)
        {
            (*word)->t_occurences[cursor] = occurence;
        }
        else
        {
            /* Research the place to add the new element */
            for (i = 0; i < cursor; i++)
            {
                /* If we found the place, we shift and add the element to the right place*/
                if (occurence.num_occurences > (*word)->t_occurences[i].num_occurences)
                {
                    // Shift
                    memmove((*word)->t_occurences + i + 1, (*word)->t_occurences + i, (cursor - i) * sizeof(Word_occurence_s));

                    // Insert
                    (*word)->t_occurences[i] = occurence;
                    break;
                }
            }
        }
        (*word)->tab_cursor++;
    }
    else /* The tab is full */
    {
        /* Check if last value occurence is lower than the parameter to add or not */
        if ((*word)->t_occurences[max_size - 1].num_occurences < occurence.num_occurences)
        {
            /* Research the place to add the new element */
            for (i = 0; i < max_size; i++)
            {
                /* If we found the place, we shift and add the element to the right place*/
                if (occurence.num_occurences > (*word)->t_occurences[i].num_occurences)
                {
                    // Shift
                    memmove((*word)->t_occurences + i + 1, (*word)->t_occurences + i, (cursor - i - 1) * sizeof(Word_occurence_s));
                    (*word)->t_occurences[i] = occurence;
                    break;
                }
            }
        }
    }

    return TRUE;
}

Bool_e word_to_string(Word_s word, char** output)
{
    unsigned int i;
    char buf[MAX_MEMORY_STRING];

    sprintf(*output, "%s", word.word_name);

    for (i = 0; i < word.tab_cursor; i++)
    {
        sprintf(buf, "\n%lu %u", word.t_occurences[i].origin_id, word.t_occurences[i].num_occurences);
        strcat(*output, buf);
    }

    return TRUE;
}