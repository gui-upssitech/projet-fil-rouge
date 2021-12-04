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
#include <string.h>

#include "../../inc/configurations.h"
#include "../../inc/indexation_generic.h"
#include "../../inc/indexation_audio.h"

int main(void)
{
    /* statements */

    /* initializations */

    /* instructions */
    automatic_generic_indexation(LIST_BASE_AUDIO_PATH, SOUND_BASE_PATH, BASE_AUDIO_DESCRIPTOR_PATH, AUDIO);

    return EXIT_SUCCESS;
}