#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "admin.h"
#include "toolbox.h"
#include "indexation_generic.h"
#include "indexation_text.h"
#include "indexation_image.h"
#include "indexation_audio.h"

int main(int argc, char *argv[])
{
    /* statements */

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
    }
    else
    {
        printf("1");
    }

    return EXIT_SUCCESS;
}