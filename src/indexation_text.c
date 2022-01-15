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

/*char *to_string(int num)
{
    char *buffer;
    *buffer = (char *)malloc(20 * sizeof(char));
    sprintf(*buffer, "%d", num);
    return *buffer;
}*/

Bool_e generate_command(char *input_path, char *output, unsigned long desc_id)
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
    FILE* p_cmd;
    unsigned int line_size;
    unsigned int current_size;
    char buffer[MAX_MEMORY_STRING];
    char command[MAX_COMMAND_LENGTH];

    /* Step 1: generate command */
    p_descriptor->id = hash(p_path);
    if (!generate_command(p_path, command, p_descriptor->id))
    {
        fprintf(stderr, "Command generation failed for file %s", p_path);
        return FALSE;
    }

    /* Step 2: run command */  
    /* Open the command for reading. */
    p_cmd = popen(command, "r");
    if (p_cmd == NULL)
    {
        fprintf(stderr, "Error: Failed to read stdout");
        return FALSE;
    }

    /* Read the output a line at a time - output it. */
    current_size = 1;
    while (fgets(buffer, sizeof(buffer), p_cmd) != NULL)
    {
        line_size = strlen(buffer);
        p_descriptor->descriptor_contents = realloc(p_descriptor->descriptor_contents, current_size + line_size);
        if(p_descriptor->descriptor_contents == NULL)
        {
            fprintf(stderr, "Error reallocating descriptor content.\n\r");
            return FALSE;
        }
        strcpy(p_descriptor->descriptor_contents + current_size - 1, buffer);
        current_size += line_size;
    }

    if(pclose(p_cmd) == EOF)
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
    if (fprintf(p_base_descriptor_text, "%s", p_descriptor->descriptor_contents) == EOF)
    {
        fprintf(stderr, "Error %d printing id of text descriptor.\n\r", errno);
        return FALSE;
    }

    return TRUE;
}