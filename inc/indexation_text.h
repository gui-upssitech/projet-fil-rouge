/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "toolbox.h"

#ifndef INDEXATION_TEXT_H
#define INDEXATION_TEXT_H

/* descriptor file path constants */
#define LIST_BASE_TEXT_PATH "descriptors/text/list_base_text.txt"
#define BASE_TEXT_DESCRIPTOR_PATH "descriptors/text/base_text_descriptor.txt"

/* data file path constants */
#define TEXT_BASE_PATH "data/texts/"

/* constants for bash script execution */
#define TEXT_DESCRIPTOR_BASE_COMMAND    "/bin/bash src/indexation_text/indexation_text.sh"
#define NB_ARGS 6

// TODO PASS TO CONFIG
#define TEXT_DESCRIPTOR_DEBUG_OUT           "results/debug/"
#define TEXT_DESCRIPTOR_FILTER_LIMIT        "0"
#define TEXT_DESCRIPTOR_FILTER_THRESHOLD    "1"
#define FILTER_VALUE                        "4"
#define DEBUG_MODE                          "0"


/* structure that contains all necessary informations to build the 
text descriptor (...) */
typedef struct
{
    /* unique id of the descriptor based on the hashed file name */
    unsigned long id;

    int provisoire_pour_compiler[4];
    char* descriptor_contents;

} Text_descriptor_s;

Bool_e index_text(char* p_path, Text_descriptor_s* p_descriptor);
Bool_e generate_command(char* filename, char** output, unsigned long desc_id);
Bool_e index_text(char* p_path, Text_descriptor_s* p_descriptor);
Bool_e save_descriptor_text(FILE* p_base_descriptor_text, Text_descriptor_s* p_descriptor);


#endif