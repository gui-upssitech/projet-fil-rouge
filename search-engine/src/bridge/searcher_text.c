#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comparaison_text.h"
#include "configurations.h"

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

    load_configurations();

    if(strcmp(argv[1], "keyword") == 0)
    {
        display_research_by_keyword(argv[2]);
    }
    else if(strcmp(argv[1], "text") == 0)
    {
        display_research_by_text(argv[2]);
    }
    else
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}