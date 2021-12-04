/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>

#include "../inc/unit.h"

void affect_unit(Unit_u* unit1, Unit_u unit2, Descriptor_e descriptor_type)
{
    /* instructions */
    switch(descriptor_type)
    {
        case TEXT:
            (*unit1).text_descriptor = unit2.text_descriptor;
            break;

        case IMAGE:
            (*unit1).image_descriptor = unit2.image_descriptor;
            break;

        case AUDIO:
            (*unit1).audio_descriptor = unit2.audio_descriptor;
            break;
    }
}