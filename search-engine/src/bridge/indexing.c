#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "indexation_generic.h"

int main(int argc, char *argv[])
{
    /* statements */

    /* initialisations */

    /* instructions */
    /*  
    first argument      :   the command name 
    second argument     :   text, image, audio or all
    */

    if(argc != 2)
    {
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "text") == 0)
    {
        if(automatic_indexing_by_data(LIST_BASE_TEXT_PATH, TEXT_BASE_PATH, BASE_TEXT_DESCRIPTOR_PATH, INDEX_TABLE_TEXT_DESCRIPTOR_PATH, TEXT) == FALSE)
        {
            printf("0");
        }
        printf("1");
    }
    else if(strcmp(argv[1], "image") == 0)
    {
        if(automatic_indexing_by_data(LIST_BASE_IMAGE_PATH, NB_BASE_PATH, BASE_IMAGE_DESCRIPTOR_PATH, "", IMAGE) == TRUE)
        {
            if(automatic_indexing_by_data(LIST_BASE_IMAGE_PATH, RGB_BASE_PATH, BASE_IMAGE_DESCRIPTOR_PATH, "", IMAGE) == TRUE)
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
        }
        else
        {
            printf("0");
        }   
    }
    else if(strcmp(argv[1], "audio") == 0)
    {
        if(automatic_indexing_by_data(LIST_BASE_AUDIO_PATH, SOUND_BASE_PATH, BASE_AUDIO_DESCRIPTOR_PATH, "", AUDIO) == FALSE)
        {
            printf("0");
            return FALSE;
        }
        printf("1");
    }
    else if(strcmp(argv[1], "all") == 0)
    {
        if(automatic_indexing() == FALSE)
        {
            printf("0");
        }
        printf("1");
    }
    else
    {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}