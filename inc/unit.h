/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            
Date:       29/11/2021
*/

#ifndef UNIT_H
#define UNIT_H

#include "descriptor.h"

typedef union
{
    Text_descriptor_s text_descriptor;
    Image_descriptor_s image_descriptor;
    Audio_descriptor_s audio_descriptor;
} Unit_u;

void display_unit(Unit_u unit);
void affect_unit(Unit_u* unit1, Unit_u unit2);

#endif