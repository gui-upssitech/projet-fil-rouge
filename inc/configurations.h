/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include "toolbox.h"

typedef struct
{
    unsigned int samples;
    unsigned int levels;
} Audio_indexing_parameters_s;

typedef struct
{
    Audio_indexing_parameters_s audio_indexing_parameters;
} Parameters_s;

extern Parameters_s G_parameters;

Bool_e load_configurations();

#endif