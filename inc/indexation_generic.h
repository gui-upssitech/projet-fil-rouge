/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef INDEXATION_GENERIC_H
#define INDEXATION_GENERIC_H

#include "toolbox.h"

typedef enum
{
    TEXT,
    IMAGE,
    AUDIO
} Descriptor_e;

Bool_e automatic_generic_indexation(char* p_list_base_path, char* p_data_path, char* p_base_path, Descriptor_e descriptor_type);

#endif