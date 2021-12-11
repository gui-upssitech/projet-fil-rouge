/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN,
            Nelson SANCHEZ
            
Date:       29/11/2021
*/

#include "unit.h"

void affect_unit(Unit_u* unit1, Unit_u unit2, Descriptor_e descriptor_type)
{
    /* instructions */
    switch(descriptor_type)
    {
        case TEXT:
            unit1->text_descriptor.id = unit2.text_descriptor.id;
            break;

        case IMAGE:
            unit1->image_descriptor.id = unit2.image_descriptor.id;
            unit1->image_descriptor.p_histogram = unit2.image_descriptor.p_histogram;
            break;

        case AUDIO:
            unit1->audio_descriptor.id = unit2.audio_descriptor.id;
            unit1->audio_descriptor.i_windows = unit2.audio_descriptor.i_windows;
            unit1->audio_descriptor.levels = unit2.audio_descriptor.levels;
            unit1->audio_descriptor.samples = unit2.audio_descriptor.samples;
            unit1->audio_descriptor.p_histogram = unit2.audio_descriptor.p_histogram;
            break;
    }
}