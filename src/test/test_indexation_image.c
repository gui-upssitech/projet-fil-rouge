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

#include "../../inc/indexation_image.h"
#include "../../inc/indexation_generic.h"
#include "../../inc/toolbox.h"

int main(int argc, char** argv)  
{
    /* statements */

    /* initializations */

    /* instructions */
    if(automatic_generic_indexation(LIST_BASE_IMAGE_PATH, NB_BASE_PATH, BASE_IMAGE_DESCRIPTOR_PATH, IMAGE) == FALSE)
    {
        printf("Failed automatic image indexation.\n\r");
    }

    if(automatic_generic_indexation(LIST_BASE_IMAGE_PATH, RGB_BASE_PATH, BASE_IMAGE_DESCRIPTOR_PATH, IMAGE) == FALSE)
    {
        printf("Failed automatic image indexation.\n\r");
    }
    
    return EXIT_SUCCESS;
}