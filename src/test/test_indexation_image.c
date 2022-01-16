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
#include <time.h>

#include "../../inc/indexation_image.h"
#include "../../inc/indexation_generic.h"
#include "../../inc/toolbox.h"

int main()  
{
    /* statements */
    // Image_descriptor_s image_descriptor;
    double time_spent;

    /* initializations */
    time_spent = 0.0;

    /* instructions */
    // printf("size descriptor text : %lu\n\r", sizeof(Text_descriptor_s));
    // printf("size descriptor image : %lu\n\r", sizeof(Image_descriptor_s));
    // printf("size descriptor audio : %lu\n\r", sizeof(Audio_descriptor_s));

    clock_t begin = clock();

    if(automatic_indexing_by_data(LIST_BASE_IMAGE_PATH, NB_BASE_PATH, BASE_IMAGE_DESCRIPTOR_PATH, "", IMAGE) == FALSE)
    {
        printf("Failed automatic image indexation.\n\r");
    }

    if(automatic_indexing_by_data(LIST_BASE_IMAGE_PATH, RGB_BASE_PATH, BASE_IMAGE_DESCRIPTOR_PATH, "", IMAGE) == FALSE)
    {
        printf("Failed automatic image indexation.\n\r");
    }

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("The elapsed time is %f seconds\n", time_spent);

    // if(index_image("/home/rxc3445a/Documents/projet-fil-rouge/data/images/TEST_RGB/test_image_rgb.txt", &image_descriptor) == FALSE)
    // {
    //     printf("error");
    // }   

    return EXIT_SUCCESS;
}