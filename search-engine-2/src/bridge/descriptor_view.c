#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "indexation_generic.h"
#include "toolbox.h"

void generic_view_descriptor(char* file_name, char* list_base_path, char* base_descriptor_path)
{
    /* statements */
    FILE* p_file;

    char buffer[MAX_MEMORY_STRING];

    char* p_string;
    size_t len = 0;
    ssize_t read;

    /* open the id file table */
    p_file = fopen(list_base_path, "r");
    if(p_file != NULL) 
    {
        /* find the file in the table */
        if(file_contains_substring(p_file, file_name, &p_string) == TRUE) 
        {
            /* if the file exists, get the id */
            sscanf(p_string, "%*s %s", buffer);
            fclose(p_file);
            free(p_string);

            /* open the descriptor base */
            p_file = fopen(base_descriptor_path, "r");
            if(p_file != NULL)
            {
                /* find the id in the base */
                if(file_contains_substring(p_file, buffer, &p_string) == TRUE)
                {
                    /* if the id exists, print it */
                    printf("%s\n\r", buffer);
                    free(p_string);

                    /* print the descriptor until a blank line */
                    while ((read = getline(&p_string, &len, p_file)) != -1 && p_string[0] != '\r' && p_string[0] != '\n')
                    {
                        printf("%s", p_string);
                    }
                }
            }
        }
    }

    /* free file if used */
    if(p_file != NULL)
    {
        fclose(p_file);
    }

    /* free string if used */
    if(p_string != NULL) 
    {
        free(p_string);
    }
}

int main(int argc, char *argv[])
{
    /* statements */
    

    /* initialisations */

    /* instructions */
    /*  
    first argument      :   the command name 
    second argument     :   the data type (text, image or audio)
    third argument      :   the file name to view his descriptor
    */

    if(argc != 3)
    {
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "text") == 0)
    {
        generic_view_descriptor(argv[2], LIST_BASE_TEXT_PATH, BASE_TEXT_DESCRIPTOR_PATH);
    }
    else if(strcmp(argv[1], "image") == 0)
    {
        strcpy(strrchr(argv[2], '.'), ".txt");
        generic_view_descriptor(argv[2], LIST_BASE_IMAGE_PATH, BASE_IMAGE_DESCRIPTOR_PATH);
    }
    else if(strcmp(argv[1], "audio") == 0)
    {
        strcpy(strrchr(argv[2], '.'), ".bin");
        generic_view_descriptor(argv[2], LIST_BASE_AUDIO_PATH, BASE_AUDIO_DESCRIPTOR_PATH);
    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}