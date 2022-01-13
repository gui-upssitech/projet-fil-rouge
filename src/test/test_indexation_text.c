#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../inc/indexation_text.h"
#include "../../inc/indexation_generic.h"

int main() 
{
    double time_spent;

    time_spent = 0.0;

    clock_t begin = clock();

    if(automatic_indexing_by_data(LIST_BASE_TEXT_PATH, TEXT_BASE_PATH, BASE_TEXT_DESCRIPTOR_PATH, TEXT) == FALSE)
    {
        printf("Failed automatic text indexation.\n\r");
    }

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Text indexing finished in %lf seconds\n", time_spent);

    return 0;
}