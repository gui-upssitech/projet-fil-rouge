/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "configurations.h"
#include "indexation_generic.h"
#include "indexation_audio.h"

int main(void)
{
    /* statements */

    /* initializations */

    /* instructions */
    automatic_indexing_by_data(LIST_BASE_AUDIO_PATH, SOUND_BASE_PATH, BASE_AUDIO_DESCRIPTOR_PATH, "", AUDIO);

    return EXIT_SUCCESS;
}