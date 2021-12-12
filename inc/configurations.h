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
    unsigned int quantification_size;
} Image_indexing_parameters_s;

typedef struct
{
    unsigned int samples;
    unsigned int levels;
} Audio_indexing_parameters_s;

typedef struct
{
    unsigned int step;
    double threshold;
} Audio_comparison_parameters_s;

typedef struct
{
    Image_indexing_parameters_s image_indexing_parameters;
    Audio_indexing_parameters_s audio_indexing_parameters;
    Audio_comparison_parameters_s audio_comparison_parameters;
} Parameters_s;

extern Parameters_s G_parameters;

Bool_e load_configurations();

#endif