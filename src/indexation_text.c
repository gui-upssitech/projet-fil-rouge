/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ

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

Bool_e generate_command(char *input_path, char **output, unsigned long desc_id)
{
    // creation of desciprtor ID by hash function (tools)
    char desc_id_str[40];
    sprintf(desc_id_str, "%lu", desc_id);

    // ADD ARGUMENTS
    *output = TEXT_DESCRIPTOR_BASE_COMMAND;

    // TODO CHECK ARGS ERROR

    // ARGS : IN_PATH OUT_DIR DESC_ID F_TYPE F_VAL DEBUG
    char *args[NB_ARGS] = {
        input_path,
        TEXT_DESCRIPTOR_DEBUG_OUT,
        desc_id_str,
        TEXT_DESCRIPTOR_FILTER_THRESHOLD,
        FILTER_VALUE,
        DEBUG_MODE};

    for (int i = 0; i < NB_ARGS; i++)
    {
        *output = str_concat(*output, str_concat(" ", args[i]));
    }

    return TRUE;
}

Bool_e index_text(char *p_path, Text_descriptor_s *p_descriptor)
{
    char *command, *descriptor = "";
    unsigned long desc_id = hash(p_path);

    /* Step 1: generate command */
    if (!generate_command(p_path, &command, desc_id))
    {
        fprintf(stderr, "Command generation failed for file '%s'", p_path);
        return FALSE;
    }

    /* Step 2: run command */
    descriptor = run_command(command);
    // TODO check the retunr of run_command !

    p_descriptor->id = desc_id;
    p_descriptor->descriptor_contents = descriptor;

    return TRUE;
}

Bool_e save_descriptor_text(FILE *p_base_descriptor_text, Text_descriptor_s *p_descriptor)
{
    // Try to add the id to the descriptor file
    if(fprintf(p_base_descriptor_text, "%s\n\n", p_descriptor->descriptor_contents) == EOF)
    {
        fprintf(stderr, "Error %d printing id of text descriptor.\n\r", errno);
        return FALSE;
    }

    return TRUE;
}