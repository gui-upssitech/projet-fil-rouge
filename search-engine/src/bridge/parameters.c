#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"
#include "toolbox.h"

int main(int argc, char *argv[])
{
    /* statements */
    unsigned long hashed_pwd;
    FILE* p_password_file;

    /* initialisations */

    /* instructions */
    /*  
    first argument      :   the command name 
    second argument     :   the parameter to modify
    third argument      :   the new value of the parameter
    */

    if(argc != 3)
    {
        return EXIT_FAILURE;
    }

    if(save_configuration(argv[1], argv[2]) == FALSE)
    {
        printf("0");
        return EXIT_SUCCESS;
    }

    if(load_configurations())
    {
        printf("0");
        return EXIT_SUCCESS;
    }

    if (strcmp(argv[1], "indexing_text_filter_mode") == 0 || 
        strcmp(argv[1], "indexing_text_filter_value") == 0 || 
        strcmp(argv[1], "indexing_text_debug") == 0 ||
        strcmp(argv[1], "indexing_text_number_table_index") == 0)
    {
        fclose(fopen(LIST_BASE_TEXT_PATH, "w"));
        fclose(fopen(BASE_TEXT_DESCRIPTOR_PATH, "w"));
        fclose(fopen(INDEX_TABLE_TEXT_DESCRIPTOR_PATH, "w"));
        if(automatic_indexing() == FALSE)
        {
            printf("0");
            return EXIT_SUCCESS;
        }
    }

    if (strcmp(argv[1], "indexing_image_quantification") == 0)
    {
        fclose(fopen(LIST_BASE_IMAGE_PATH, "w"));
        fclose(fopen(BASE_IMAGE_DESCRIPTOR_PATH, "w"));
        if(automatic_indexing() == FALSE)
        {
            printf("0");
            return EXIT_SUCCESS;
        }
    }

    if (strcmp(argv[1], "indexing_audio_samples") == 0 || 
        strcmp(argv[1], "indexing_audio_interval") == 0)
    {
        fclose(fopen(LIST_BASE_AUDIO_PATH, "w"));
        fclose(fopen(BASE_AUDIO_DESCRIPTOR_PATH, "w"));
        if(automatic_indexing() == FALSE)
        {
            printf("0");
            return EXIT_SUCCESS;
        }
}
    
    printf("1");
    return EXIT_SUCCESS;
}