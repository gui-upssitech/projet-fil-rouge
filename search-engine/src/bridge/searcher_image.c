#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comparaison_image.h"
#include "console.h"

int main(int argc, char *argv[])
{
    /* statements */

    /* initialisations */

    /* instructions */
    /*  
    first argument      :   the command name 
    second argument     :   search type (color or gray) 
    third argument      :   value (image path) 
    */

    if(argc != 3)
    {
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "color") == 0)
    {
        if(display_image_by_path_research_menu_graphical(argv[2], TRUE) == TRUE)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            return EXIT_FAILURE;
        }
    }
    else if(strcmp(argv[1], "gray") == 0)
    {
        if(display_image_by_path_research_menu_graphical(argv[2], FALSE) == TRUE)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}