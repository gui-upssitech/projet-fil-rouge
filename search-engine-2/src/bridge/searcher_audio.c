#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comparaison_audio.h"
#include "console.h"
#include "configurations.h"

int main(int argc, char *argv[])
{
    /* statements */
    Binary_search_tree_p* time_code_forest;
    unsigned int size;
    unsigned int i;

    /* initialisations */

    /* instructions */
    /*  
    first argument      :   the command name 
    second argument     :   search type (audio, useless here but it simplify the Java part) 
    third argument      :   value (the audio path) 
    */

    if(argc != 3)
    {
        return EXIT_FAILURE;
    }

    load_configurations();

    if(strcmp(argv[1], "audio") == 0)
    {
        strcpy(strrchr(argv[2], '.'), ".bin");
        if(compare_audio_files(argv[2], &time_code_forest, &size) == TRUE)
        {
            display_audio_result_menu(time_code_forest, size, argv[2]);
            for(i = 0; i < size; i++)
            {
                free_binary_search_tree(&(time_code_forest[i]));
            }
            free(time_code_forest);
        }
    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}