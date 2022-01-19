#include <stdio.h>
#include <stdlib.h>

#include "configurations.h"
#include "console.h"

int main(void)
{
    if(load_configurations() == FALSE)
    {
        fprintf(stderr, "Erreur loading configurations...\n\r");
        return EXIT_FAILURE;
    }

    if(automatic_indexing() == FALSE)
    {
        return EXIT_FAILURE;
    }

    display_main_menu();
    
    return EXIT_SUCCESS;
}