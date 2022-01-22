/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            

Date:       29/11/2021
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/toolbox.h"
#include "../inc/indexation_generic.h"
#include "../inc/indexation_text.h"

Bool_e generate_command(char *input_path, unsigned long desc_id, char *output)
{
    int result = sprintf(output, "/bin/bash src/indexation_text/indexation_text.sh %s %s %lu %u %u %u",
                         input_path,
                         TEXT_DESCRIPTOR_DEBUG_OUT,
                         desc_id,
                         G_parameters.text_indexing_parameters.indexing_text_filter_mode,
                         G_parameters.text_indexing_parameters.indexing_text_filter_value,
                         G_parameters.text_indexing_parameters.indexing_text_debug);

    return (result != EOF);
}

Bool_e index_text(char *p_path, Text_descriptor_s *p_descriptor)
{
    /* statements */
    FILE *p_cmd;
    unsigned int line_size;
    unsigned int current_size;
    char buffer[MAX_MEMORY_STRING];
    char command[MAX_COMMAND_LENGTH];

    /* Step 1: generate command */
    p_descriptor->id = hash(p_path);
    if (!generate_command(p_path, p_descriptor->id, command))
    {
        fprintf(stderr, "Command generation failed for file %s", p_path);
        return FALSE;
    }

    free(p_path);

    /* Step 2: run command */
    /* Open the command for reading. */
    p_cmd = popen(command, "r");
    if (p_cmd == NULL)
    {
        fprintf(stderr, "Error: Failed to read stdout");
        return FALSE;
    }

    p_descriptor->descriptor_contents = NULL;
    /* Read the output a line at a time - output it. */
    current_size = 1;
    while (fgets(buffer, sizeof(buffer), p_cmd) != NULL)
    {
        /* Resize the string to accomodate new line */
        line_size = strlen(buffer);
        p_descriptor->descriptor_contents = (char *)realloc(p_descriptor->descriptor_contents, current_size + line_size * sizeof(char));

        /* Vérify malloc allocation */
        if (p_descriptor->descriptor_contents == NULL)
        {
            fprintf(stderr, "Error reallocating descriptor content.\n\r");
            return FALSE;
        }

        strcpy(p_descriptor->descriptor_contents + current_size - 1, buffer);
        current_size += line_size;
    }

    /* Closing the command after all indexing  */
    if (pclose(p_cmd) == EOF)
    {
        fprintf(stderr, "Error closing descriptor\n\r");
        return FALSE;
    }

    /* Step 3: Store descriptor contents in the descriptor object */
    return TRUE;
}

Bool_e save_descriptor_text(FILE *p_base_descriptor_text, Text_descriptor_s *p_descriptor)
{
    // Try to add the id to the descriptor file
    if (fprintf(p_base_descriptor_text, "%s\n\n", p_descriptor->descriptor_contents) == EOF)
    {
        fprintf(stderr, "Error %d printing id of text descriptor.\n\r", errno);
        return FALSE;
    }

    return TRUE;
}

Bool_e update_dictionary(Word_Tree_s* p_dictionary, Text_descriptor_s descriptor)
{
    char word[MAX_MEMORY_STRING];
    char* line;

    Word_occurence_s occurence;

    occurence.origin_id = descriptor.id;

    /*Source : https://stackoverflow.com/questions/17983005/c-how-to-read-a-string-line-by-line */
    /* Read line one by one and add the word/occurence to the tree */
    char* buffer = descriptor.descriptor_contents;
    while (buffer)
    {
        char* new_buffer = strchr(buffer, '\n');
        size_t line_len = new_buffer ? (size_t) (new_buffer - buffer) : strlen(buffer);
        line = (char*) malloc(line_len + 1);

        if (line == NULL)
        {
            fprintf(stderr, "Error %d failed to allocate memory.\n\r", errno);
            return FALSE;
        }

        memcpy(line, buffer, line_len);
        line[line_len] = '\0'; /* nul terminate the string to avoid errors */
        
        /* Line treatment - Start by skipping the first line and last two lines */
        if(strchr(line, ' '))
        {
            sscanf(line, "%s %u\n", word, &(occurence.num_occurences));
            if (add_occurence_to_tree(p_dictionary, word, occurence) == FALSE)
            {
                fprintf(stderr, "Error %d failed to add occurence to tree.\n\r", errno);
                return FALSE;
            }
        }
        
        free(line);
        buffer = new_buffer ? (new_buffer + 1) : NULL; /* Remove the line (the +1 skips the \n) */
    }

    return TRUE;
}