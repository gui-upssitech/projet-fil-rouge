/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>

#include "../inc/unit.h"
#include "../inc/descriptor.h"

void display_unit(Unit_u unit)
{
    /* statements */
    unsigned int size;

    /* initializations */
    size = sizeof(Unit_u);

    /* instructions */
    switch(size)
    {
        case sizeof(Text_descriptor_s):
            break;

        case sizeof(Image_descriptor_s):
            break;

        case sizeof(Audio_descriptor_s):
            break;
            
        default:
            break;
    }
}

void affect_unit(Unit_u* unit1, Unit_u unit2)
{
    /* instructions */
    *unit1 = unit2;
}