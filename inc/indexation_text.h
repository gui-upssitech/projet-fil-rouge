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

#define TEXT_DESCRIPTOR_BASE_COMMAND    "/bin/bash src/indexation_text/indexation_text.sh"
#define TEXT_DESCRIPTOR_INPUT_DIR       "data/texts/"
#define TEXT_DESCRIPTOR_OUTPUT_DIR      "results/debug/"

#define TEXT_DESCRIPTOR_FILTER_LIMIT "0"
#define TEXT_DESCRIPTOR_FILTER_THRESHOLD "1"


/* structure that contains all necessary informations to build the 
text descriptor (...) */
typedef struct
{
    /* unique id of the descriptor based on the hashed file name */
    unsigned long id;

    int provisoire_pour_compiler[4];

} Text_descriptor_s;

Bool_e generate_descriptor(char* filename);
Bool_e generate_command(char* filename, char** output);

#endif