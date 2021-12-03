/*
Authors:    Constant ROUX,
            Julian TRANI,
            Peter PIRIOU--DEZY,
            Guillaume ROUSSIN
            
Date:       29/11/2021
*/

#include <stdio.h>
#include <stdlib.h>

#include "../../inc/descriptor.h"
#include "../../inc/indexation_image.h"
#include "../../inc/toolbox.h"

int main(int argc, char** argv)  
{
    /* statements */

    /* initializations */

    /* instructions */
    if(automatic_image_indexation() == FALSE)
    {
        printf("Failed automatic image indexation.\n\r");
    }
    
    return EXIT_SUCCESS;
}