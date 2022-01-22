/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            
            
Date:       29/11/2021
*/

#include "unit.h"

void affect_unit(Unit_u* unit1, Unit_u* unit2, Descriptor_e descriptor_type)
{
    /* instructions */
    /* COPY unit2 and save the COPY in unit1 */
    switch(descriptor_type)
    {
        case TEXT:
            unit1->text_descriptor.id = unit2->text_descriptor.id;
            unit1->text_descriptor.descriptor_contents = (char*) malloc(MAX_MEMORY_STRING);
            if(unit1->text_descriptor.descriptor_contents == NULL)
            {
                fprintf(stderr, "Error text descriptor memory allocation in during unit affectation.\n\r");
                return;
            }
            strcpy(unit1->text_descriptor.descriptor_contents, unit2->text_descriptor.descriptor_contents);
            break;

        case IMAGE:
            unit1->image_descriptor.id = unit2->image_descriptor.id;
            unit1->image_descriptor.p_histogram = (unsigned int*) malloc(sizeof(unsigned int) * PWRTWO(RGB_CHANNEL_SIZE * G_parameters.image_indexing_parameters.quantification_size));
            if(unit1->image_descriptor.p_histogram == NULL)
            {
                fprintf(stderr, "Error image descriptor memory allocation in during unit affectation.\n\r");
                return;
            }
            memcpy( unit1->image_descriptor.p_histogram, 
                    unit2->image_descriptor.p_histogram, 
                    sizeof(unsigned int) * PWRTWO(RGB_CHANNEL_SIZE * G_parameters.image_indexing_parameters.quantification_size));
            break;

        case AUDIO:
            unit1->audio_descriptor.id = unit2->audio_descriptor.id;
            unit1->audio_descriptor.i_windows = unit2->audio_descriptor.i_windows;
            unit1->audio_descriptor.levels = unit2->audio_descriptor.levels;
            unit1->audio_descriptor.samples = unit2->audio_descriptor.samples;
            unit1->audio_descriptor.p_histogram = (unsigned int*) malloc(unit2->audio_descriptor.levels * unit2->audio_descriptor.i_windows * sizeof(unsigned int));
            if(unit1->audio_descriptor.p_histogram == NULL)
            {
                fprintf(stderr, "Error audio descriptor memory allocation in during unit affectation.\n\r");
                return;
            }

            memcpy( unit1->audio_descriptor.p_histogram, 
                    unit2->audio_descriptor.p_histogram, 
                    unit2->audio_descriptor.levels * unit2->audio_descriptor.i_windows * sizeof(unsigned int));
            break;
    
        default:
            break;
    }
}