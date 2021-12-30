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

// TODO ADD CONFIG FILE WITH MERGE
#define FILTER_VALUE "10"
#define DEBUG_MODE "1"
#define NB_ARGS 6 // number of arguments needed to the indexation_text.sh script

/*char *to_string(int num)
{
    char **buffer = (char *)malloc(20 * sizeof(char));
    sprintf(*buffer, "%d", num);
    return *buffer;
}*/

Bool_e generate_descriptor(char *filename)
{
    char* command = "";
    Bool_e result = generate_command(filename, &command);

    // Check if generate_command works
    if (!result){
        fprintf(stderr, "ERREUR Commande mal générée !");
        return FALSE;
    }

    printf("Command to run : %s\n", command);

    printf("command output :\n%s\n", run_command(command));

    return TRUE;
}

Bool_e generate_command(char* filename, char** output) {
    // creation of desciprtor ID by hash function (tools)
    unsigned long desc_id = hash(filename);
    char desc_id_str[40];
    sprintf(desc_id_str, "%ld", desc_id);

    // Get input path
    char* input_path = str_concat(TEXT_DESCRIPTOR_INPUT_DIR, filename);

    // ADD ARGUMENTS
    *output = TEXT_DESCRIPTOR_BASE_COMMAND;

    // TODO CHECK ARGS ERROR

    // ARGS : IN_PATH OUT_DIR DESC_ID F_TYPE F_VAL DEBUG
    char *args[NB_ARGS] = {
        input_path, 
        TEXT_DESCRIPTOR_OUTPUT_DIR, 
        desc_id_str, 
        TEXT_DESCRIPTOR_FILTER_THRESHOLD, 
        FILTER_VALUE,
        DEBUG_MODE
    };

    for (int i = 0; i < NB_ARGS; i++)
    {
        *output = str_concat(*output, str_concat(" ", args[i]));
    }

    return TRUE;
}