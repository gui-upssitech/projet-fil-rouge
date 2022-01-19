/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN            
            
Date:       29/11/2021
*/

#ifndef UNIT_H
#define UNIT_H

#include <stdio.h>
#include <stdlib.h>

#include "indexation_text.h"
#include "indexation_image.h"
#include "indexation_audio.h"

/**
 * @brief An enum which represents all types of data possible.
 * 
 */
typedef enum
{
    TEXT,
    IMAGE,
    AUDIO
} Descriptor_e;

/**
 * @brief An union to generically manipulate data descriptors.
 * 
 */
typedef union
{
    Text_descriptor_s text_descriptor;
    Image_descriptor_s image_descriptor;
    Audio_descriptor_s audio_descriptor;
} Unit_u;

/**
 * @brief Affect a unit to an other unit.
 * 
 * @param unit1 The unit output.
 * @param unit2 The unit input.
 * @param descriptor_type The type of units.
 */
void affect_unit(Unit_u* unit1, Unit_u unit2, Descriptor_e descriptor_type);

#endif