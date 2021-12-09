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

#include "../../inc/indexation_audio.h"
#include "../../inc/indexation_text.h"
#include "../../inc/indexation_image.h"
#include "../../inc/indexation_generic.h"
#include "../../inc/toolbox.h"

int main(int argc, char** argv)  
{
    /* statements */

    /* initializations */

    /* instructions */
    // printf("size descriptor text : %lu\n\r", sizeof(Text_descriptor_s));
    // printf("size descriptor image : %lu\n\r", sizeof(Image_descriptor_s));
    // printf("size descriptor audio : %lu\n\r", sizeof(Audio_descriptor_s));

    if(automatic_generic_indexation(LIST_BASE_IMAGE_PATH, NB_BASE_PATH, BASE_IMAGE_DESCRIPTOR_PATH, IMAGE) == FALSE)
    {
        printf("Failed automatic image indexation.\n\r");
    }

    if(automatic_generic_indexation(LIST_BASE_IMAGE_PATH, RGB_BASE_PATH, BASE_IMAGE_DESCRIPTOR_PATH, IMAGE) == FALSE)
    {
        printf("Failed automatic image indexation.\n\r");
    }
    // if(index_image("/home/rxc3445a/Documents/projet-fil-rouge/data/images/TEST_RGB/test_image_rgb.txt", &image_descriptor) == FALSE)
    // {
    //     printf("error");
    // }   

    return EXIT_SUCCESS;
}