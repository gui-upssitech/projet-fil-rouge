#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comparaison_text.h"

int main(int argc, char *argv[])
{
    /* statements */

    /* initialisations */

    /* instructions */
    /*  
    first argument      :   the command name 
    second argument     :   search type (keyword or text) 
    third argument      :   value (the keyword or the text path) 
    */

    if(argc != 3)
    {
        return EXIT_FAILURE;
    }

    if(strcmp(argv[1], "keyword") == 0)
    {
        if(display_research_by_keyword(argv[2]) == TRUE)
        {
            return EXIT_SUCCESS;
        }
        else
        {
            return EXIT_FAILURE;
        }
    }
    else if(strcmp(argv[1], "text") == 0)
    {

    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}