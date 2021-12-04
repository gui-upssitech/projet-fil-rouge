/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#ifndef UNIT_H
#define UNIT_H

#include "indexation_text.h"
#include "indexation_image.h"
#include "indexation_audio.h"
#include "indexation_generic.h"

typedef union
{
    Text_descriptor_s text_descriptor;
    Image_descriptor_s image_descriptor;
    Audio_descriptor_s audio_descriptor;
} Unit_u;

void affect_unit(Unit_u* unit1, Unit_u unit2, Descriptor_e descriptor_type);

#endif