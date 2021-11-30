#include <stdio.h>
#include <stdlib.h>

#include "../inc/display.h"
#include "../inc/toolbox.h"

void print_plate_console()
{
    /* declarations */
    unsigned int i;

    /* instructions */
    printf("%s", CORNER);
    for(i = 0; i < MAX_CHAR_PER_LINE - 2; i++)
    {
        printf("%s", PLATE);
    }
    printf("%s\n\r", CORNER);
}

void print_blank_console(unsigned int blank_size)
{
    /* declarations */
    int i;

    /* instructions */
    for(i = 0; i < blank_size; i++)
    {
        printf("%s", SPACE);
    }
}

void display_text_console(char* p_text)
{
    /* statements */
    unsigned int long size, blank_size;
    Bool_e even;

    /* initializations */
    even = TRUE;

    /* instructions */
    size = get_array_size_from_pointer(p_text);
    if((MAX_CHAR_PER_LINE - size - 2) % 2 == 1)
    {
        even = FALSE;
    }
    blank_size = (MAX_CHAR_PER_LINE - size - 2) / 2;
    printf("%s", WALL);
    print_blank_console(blank_size);
    printf("%s", p_text);
    print_blank_console(even == TRUE ? blank_size : blank_size + 1);
    printf("%s\n\r", WALL);
}

void main_menu()
{
}

void user_menu(){}

void admin_menu(){}