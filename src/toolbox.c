#include <stdio.h>
#include <stdlib.h>

#include "../inc/toolbox.h"

unsigned int get_array_size_from_pointer(char* p_array)
{
    /* statements */
    unsigned int size;
    char c;

    /* initializations */
    size = 0;

    /* instructions */
    while((c = *p_array++) != '\0')
    {
        size++;
    }
    return size;
}

/* source : https://stackoverflow.com/questions/7666509/hash-function-for-string */
unsigned long hash(char* p_string)
{
    /* statements */
    unsigned long hash = 5381;
    int c;

    /* instructions */
    while ((c = *p_string++))
    {
        /* hash * 33 + c */
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

Bool_e read_integer(int* p_value)
{
    /* statements */
    Bool_e return_value;

    /* initializations */

    /* instructions */
    if(scanf("%d", p_value))
    {
        return_value = TRUE;
    }
    else
    {
        return_value = FALSE;
    }
    return return_value;
}